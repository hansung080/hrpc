#include "stdafx.h"
#include "EventSelect.h"

DWORD WINAPI selectThreadCallback(LPVOID param){
	EventSelect* self = (EventSelect*)param;
	self->selectThreadCallback();
	return 0;
}

EventSelect::EventSelect(VOID){
	mSelectEventHandle = NULL;
	mSelectThreadHandle = NULL;
	mStartUpEventHandle = NULL;
	mDestroyEventHandle = NULL;

	mSocket = NULL;
}

EventSelect::~EventSelect(VOID){
}

BOOL EventSelect::begin(SOCKET socket){
	if(!socket){
		return FALSE;
	}

	if(mSocket){
		return FALSE;
	}

	mSocket = socket;

	mSelectEventHandle = WSACreateEvent();
	if(mSelectEventHandle == WSA_INVALID_EVENT){
		end();
		return FALSE;
	}

	mStartUpEventHandle = CreateEvent(0, FALSE, FALSE, 0);
	if(mStartUpEventHandle == NULL){
		end();
		return FALSE;
	}

	mDestroyEventHandle = CreateEvent(0, FALSE, FALSE, 0);
	if(mDestroyEventHandle == NULL){
		end();
		return FALSE;
	}

	DWORD result = WSAEventSelect(socket, mSelectEventHandle, FD_CONNECT | FD_READ | FD_WRITE | FD_CLOSE);
	if(result == SOCKET_ERROR){
		end();
		return FALSE;
	}

	DWORD selectThreadID = 0;
	mSelectThreadHandle = CreateThread(NULL, 0, ::selectThreadCallback, this, 0, &selectThreadID);
	if(!mSelectThreadHandle){
		end();
		return FALSE;
	}

	WaitForSingleObject(mStartUpEventHandle, INFINITE);

	return TRUE;
}

BOOL EventSelect::end(VOID){
	if(!mSocket){
		return FALSE;
	}

	if(mSelectThreadHandle){
		SetEvent(mDestroyEventHandle);
		WaitForSingleObject(mSelectThreadHandle, INFINITE);
		CloseHandle(mSelectThreadHandle);
	}

	if(mSelectEventHandle){
		CloseHandle(mSelectEventHandle);
	}

	if(mStartUpEventHandle){
		CloseHandle(mStartUpEventHandle);
	}

	if(mDestroyEventHandle){
		CloseHandle(mDestroyEventHandle);
	}

	return TRUE;
}

VOID EventSelect::selectThreadCallback(VOID){
	WSANETWORKEVENTS networkEvents;
	DWORD eventID = 0;
	DWORD result = 0;
	HANDLE threadEvents[2] = {mDestroyEventHandle, mSelectEventHandle};

	while(TRUE){
		SetEvent(mStartUpEventHandle);
		eventID = WaitForMultipleObjects(2, threadEvents, FALSE, INFINITE);
		switch(eventID){
		case WAIT_OBJECT_0: // mDestroyEventHandle
			return;

		case WAIT_OBJECT_0 + 1: // mSelectEventHandle
			eventID = WSAEnumNetworkEvents(mSocket, mSelectEventHandle, &networkEvents);
			if(eventID == SOCKET_ERROR){
				return;
			}

			if(networkEvents.lNetworkEvents & FD_CONNECT){
				onIOConnected();
				if(networkEvents.iErrorCode[FD_CONNECT_BIT]){
					return;
				}
			}else if (networkEvents.lNetworkEvents & FD_WRITE){
				onIOWrote();

			}else if (networkEvents.lNetworkEvents & FD_READ){
				onIORead();

			}else if (networkEvents.lNetworkEvents & FD_CLOSE){
				onIODisconnected();
				return;
			}

			break;
			
		default:
			return;
		}
	}
}
