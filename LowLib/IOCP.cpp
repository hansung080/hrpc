#include "stdafx.h"
#include "Constant.h"
#include "IOCP.h"

DWORD WINAPI workerThreadCallback(LPVOID param){
	IOCP* self = (IOCP*)param;
	self->workerThreadCallback();
	return 0;
}

IOCP::IOCP(VOID){
	mIOCPHandle = NULL;
	mWorkerThreadCount = 0;
	mStartUpEventHandle = NULL;
}

IOCP::~IOCP(VOID){
}

BOOL IOCP::begin(VOID){
	mIOCPHandle = NULL;

	SYSTEM_INFO  systemInfo;
	GetSystemInfo(&systemInfo);
	mWorkerThreadCount = systemInfo.dwNumberOfProcessors * Constant::IOCP_WORKER_THREAD_COUNT_PER_PROCESSOR;

	// IOCP를 생성
	mIOCPHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if(!mIOCPHandle){
		return FALSE;
	}

	mStartUpEventHandle = CreateEvent(0, FALSE, FALSE, 0);
	if(mStartUpEventHandle == NULL){
		end();
		return FALSE;
	}

	for(DWORD i = 0; i < mWorkerThreadCount; i++){
		HANDLE workerThread = CreateThread(NULL, 0, ::workerThreadCallback, this, 0, NULL);
		mWorkerThreadVector.push_back(workerThread);
		WaitForSingleObject(mStartUpEventHandle, INFINITE);
	}

	return TRUE;
}

BOOL IOCP::end(VOID){
	for(DWORD i = 0; i < mWorkerThreadVector.size(); i++){
		PostQueuedCompletionStatus(mIOCPHandle, 0, 0, NULL);
	}

	for(DWORD i = 0; i < mWorkerThreadVector.size(); i++){
		WaitForSingleObject(mWorkerThreadVector[i], INFINITE);
		CloseHandle(mWorkerThreadVector[i]);
	}

	if(mIOCPHandle){
		CloseHandle(mIOCPHandle);
	}

	mWorkerThreadVector.clear();

	if(mStartUpEventHandle){
		CloseHandle(mStartUpEventHandle);
	}

	return TRUE;
}

BOOL IOCP::registerSocketToIOCP(SOCKET socket, ULONG_PTR completionKey){
	if(!socket || !completionKey){
		return FALSE;
	}

	// Socket을 IOCP에 등록
	mIOCPHandle = CreateIoCompletionPort((HANDLE)socket, mIOCPHandle, completionKey, 0);
	if (!mIOCPHandle){
		return FALSE;
	}

	return TRUE;
}

VOID IOCP::workerThreadCallback(VOID){
	BOOL successed = FALSE;
	DWORD numberOfBytesTransferred = 0;
	VOID* completionKey = NULL;
	OVERLAPPED* overlapped = NULL;
	OVERLAPPED_EX* overlappedEx = NULL;
	VOID* object = NULL;
	
	while(TRUE){
		SetEvent(mStartUpEventHandle);

		successed = GetQueuedCompletionStatus(mIOCPHandle, &numberOfBytesTransferred, (LPDWORD)&completionKey, &overlapped, INFINITE);

		if(!completionKey){
			return;
		}

		overlappedEx = (OVERLAPPED_EX*)overlapped;
		object = overlappedEx->object;

		if(!successed || (successed && numberOfBytesTransferred == 0)){
			if(overlappedEx->ioType == IO_ACCEPT){
				onIOConnected(object);
			}else{
				onIODisconnected(object);
			}

			continue;
		}
	
		switch(overlappedEx->ioType){
		case IO_READ:
			onIORead(object, numberOfBytesTransferred);
			break;

		case IO_WRITE:
			onIOWrote(object, numberOfBytesTransferred);
			break;
		}
	}
}