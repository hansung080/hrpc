#include "stdafx.h"
#include "Constant.h"
#include "CriticalSection.h"
#include "MultiThreadSync.h"
#include "NetworkInfo.h"
#include "CircularQueue.h"
#include "NetworkSession.h"

DWORD WINAPI reliableUDPThreadCallback(LPVOID param){
	NetworkSession* self = (NetworkSession*)param;
	self->reliableUDPThreadCallback();
	return 0;
}

NetworkSession::NetworkSession(VOID){
	memset(&mAcceptOverlapped, 0, sizeof(mAcceptOverlapped));
	memset(&mReadOverlapped, 0, sizeof(mReadOverlapped));
	memset(&mWriteOverlapped, 0, sizeof(mWriteOverlapped));
	memset(mReadBuffer, 0, sizeof(mReadBuffer));
	memset(&mUDPRemoteInfo, 0, sizeof(mUDPRemoteInfo));

	mSocket = NULL;

	mReliableUDPThreadHandle = NULL;
	mReliableUDPThreadStartUpEvent = NULL;
	mReliableUDPThreadDestroyEvent = NULL;
	mReliableUDPThreadWakeUpEvent = NULL;
	mReliableUDPWriteCompleteEvent = NULL;

	mIsReliableUDPSending = FALSE;

	mAcceptOverlapped.ioType = IO_ACCEPT;
	mReadOverlapped.ioType = IO_READ;
	mWriteOverlapped.ioType = IO_WRITE;

	mAcceptOverlapped.object = this;
	mReadOverlapped.object = this;
	mWriteOverlapped.object = this;
}

NetworkSession::~NetworkSession(VOID){
}

BOOL NetworkSession::begin(VOID){
	ThreadSync sync;

	if(mSocket){
		return FALSE;
	}

	memset(mReadBuffer, 0, sizeof(mReadBuffer));
	memset(&mUDPRemoteInfo, 0, sizeof(mUDPRemoteInfo));

	mSocket = NULL;

	mReliableUDPThreadHandle = NULL;
	mReliableUDPThreadStartUpEvent = NULL;
	mReliableUDPThreadDestroyEvent = NULL;
	mReliableUDPThreadWakeUpEvent = NULL;
	mReliableUDPWriteCompleteEvent = NULL;

	mIsReliableUDPSending = FALSE;

	return TRUE;
}

BOOL NetworkSession::end(VOID){
	ThreadSync sync;

	if(!mSocket){
		return FALSE;
	}

	closesocket(mSocket);
	mSocket = NULL;

	if(mReliableUDPThreadHandle){
		SetEvent(mReliableUDPThreadDestroyEvent);
		WaitForSingleObject(mReliableUDPThreadHandle, INFINITE);
		CloseHandle(mReliableUDPThreadHandle);
	}

	if(mReliableUDPThreadStartUpEvent){
		CloseHandle(mReliableUDPThreadStartUpEvent);
	}

	if(mReliableUDPThreadDestroyEvent){
		CloseHandle(mReliableUDPThreadDestroyEvent);
	}

	if(mReliableUDPThreadWakeUpEvent){
		CloseHandle(mReliableUDPThreadWakeUpEvent);
	}

	if(mReliableUDPWriteCompleteEvent){
		CloseHandle(mReliableUDPWriteCompleteEvent);
	}

	mReliableWriteQueue.end();

	return TRUE;
}

BOOL NetworkSession::bindTCP(VOID){
	ThreadSync sync;

	if(mSocket){
		return FALSE;
	}

	mSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if(mSocket == INVALID_SOCKET){
		return FALSE;
	}

	//BOOL noDelay = TRUE;
	//setsockopt(mSocket, IPPROTO_TCP, TCP_NODELAY, (const char FAR*)&noDelay, sizeof(noDelay));
	
	return TRUE;
}

BOOL NetworkSession::bindUDP(USHORT port){
	ThreadSync sync;

	if(port <= 0){
		return FALSE;
	}

	if(mSocket){
		return FALSE;
	}

	mSocket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if(mSocket == INVALID_SOCKET){
		return FALSE;
	}

	SOCKADDR_IN localAddressInfo;
	localAddressInfo.sin_family = AF_INET;
	localAddressInfo.sin_port = htons(port);
	localAddressInfo.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	if(::bind(mSocket, (LPSOCKADDR)&localAddressInfo, sizeof(SOCKADDR_IN)) == SOCKET_ERROR){
		end();
		return FALSE;
	}

	mReliableUDPThreadStartUpEvent = CreateEvent(0, FALSE, FALSE, 0);
	if(mReliableUDPThreadStartUpEvent = NULL){
		end();
		return FALSE;
	}

	mReliableUDPThreadDestroyEvent = CreateEvent(0, FALSE, FALSE, 0);
	if(mReliableUDPThreadDestroyEvent = NULL){
		end();
		return FALSE;
	}

	mReliableUDPThreadWakeUpEvent = CreateEvent(0, FALSE, FALSE, 0);
	if(mReliableUDPThreadWakeUpEvent = NULL){
		end();
		return FALSE;
	}

	mReliableUDPWriteCompleteEvent = CreateEvent(0, FALSE, FALSE, 0);
	if(mReliableUDPWriteCompleteEvent = NULL){
		end();
		return FALSE;
	}

	if(!mReliableWriteQueue.begin()){
		end();
		return FALSE;
	}

	DWORD reliableUDPThreadID = 0;
	mReliableUDPThreadHandle = CreateThread(NULL, 0, ::reliableUDPThreadCallback, this, 0, &reliableUDPThreadID);
	WaitForSingleObject(mReliableUDPThreadStartUpEvent, INFINITE);

	return TRUE;
}

BOOL NetworkSession::listen(USHORT port, INT backLog){
	ThreadSync sync;

	if(port <= 0 || backLog <= 0){
		return FALSE;
	}

	if(!mSocket){
		return FALSE;
	}

	SOCKADDR_IN localAddressInfo;
	localAddressInfo.sin_family = AF_INET;
	localAddressInfo.sin_port = htons(port);
	localAddressInfo.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	if(::bind(mSocket, (LPSOCKADDR)&localAddressInfo, sizeof(SOCKADDR_IN)) == SOCKET_ERROR){
		end();
		return FALSE;
	}
	
	if(::listen(mSocket, backLog) == SOCKET_ERROR){
		end();
		return FALSE;
	}

	LINGER linger;
	linger.l_onoff = 1;
	linger.l_linger = 0;

	if(setsockopt(mSocket, SOL_SOCKET, SO_LINGER, (char*)&linger, sizeof(LINGER)) == SOCKET_ERROR){
		end();
		return FALSE;
	}

	return TRUE;
}

BOOL NetworkSession::accept(SOCKET listenSocket){
	ThreadSync sync;

	if(!listenSocket){
		return FALSE;
	}

	if(mSocket){
		return FALSE;
	}

	mSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if(mSocket == INVALID_SOCKET){
		end();
		return FALSE;
	}

	//BOOL noDelay = TRUE;
	//setsockopt(mSocket, IPPROTO_TCP, TCP_NODELAY, (const char FAR*)&noDelay, sizeof(noDelay));

	if(!AcceptEx(listenSocket, mSocket, mReadBuffer, 0, sizeof(sockaddr_in) + 16, sizeof(sockaddr_in) + 16, NULL, &mAcceptOverlapped.overlapped)){
		INT lastError = WSAGetLastError();
		if(lastError != ERROR_IO_PENDING && lastError != WSAEWOULDBLOCK){
			end();
			return FALSE;
		}
	}

	return TRUE;
}

BOOL NetworkSession::connet(LPSTR address, USHORT port){
	ThreadSync sync;

	if(!address || port <= 0){
		return FALSE;
	}

	if(!mSocket){
		return FALSE;
	}

	SOCKADDR_IN remoteAddressInfo;
	remoteAddressInfo.sin_family = AF_INET;
	remoteAddressInfo.sin_port = htons(port);
	remoteAddressInfo.sin_addr.S_un.S_addr = inet_addr(address);

	if(WSAConnect(mSocket, (LPSOCKADDR)&remoteAddressInfo, sizeof(SOCKADDR_IN),	NULL, NULL, NULL, NULL) == SOCKET_ERROR){
		if(WSAGetLastError() != WSAEWOULDBLOCK){
			end();
			return FALSE;
		}
	}

	return TRUE;
}

BOOL NetworkSession::initReadForIOCP(VOID){
	ThreadSync sync;

	if(!mSocket){
		return FALSE;
	}

	WSABUF wsaBuf;
	DWORD readBytes = 0;
	DWORD readFlag = 0;

	wsaBuf.buf = (CHAR*)mReadBuffer;
	wsaBuf.len = MAX_BUFFER_LENGTH;

	if(WSARecv(mSocket, &wsaBuf, 1, &readBytes, &readFlag, &mReadOverlapped.overlapped, NULL) == SOCKET_ERROR){
		INT lastError = WSAGetLastError();
		if(lastError != WSA_IO_PENDING && lastError != WSAEWOULDBLOCK){
			end();
			return FALSE;
		}
	}

	return TRUE;
}

BOOL NetworkSession::readForIOCP(BYTE* data, DWORD dataLength){
	ThreadSync sync;

	if(!mSocket){
		return FALSE;
	}

	if(!data || dataLength <= 0){
		return FALSE;
	}

	memcpy(data, mReadBuffer, dataLength);

	return TRUE;
}

BOOL NetworkSession::readForEventSelect(BYTE* data, DWORD& dataLength){
	ThreadSync sync;

	if(!mSocket){
		return FALSE;
	}

	if(!data){
		return FALSE;
	}

	WSABUF wsaBuf;
	DWORD readBytes = 0;
	DWORD readFlag = 0;

	wsaBuf.buf = (CHAR*)mReadBuffer;
	wsaBuf.len = MAX_BUFFER_LENGTH;

	if(WSARecv(mSocket, &wsaBuf, 1, &readBytes, &readFlag, &mReadOverlapped.overlapped, NULL) == SOCKET_ERROR){
		INT lastError = WSAGetLastError();
		if(lastError != WSA_IO_PENDING && lastError != WSAEWOULDBLOCK){
			end();
			return FALSE;
		}
	}

	memcpy(data, mReadBuffer, readBytes);
	dataLength = readBytes;

	return TRUE;
}

BOOL NetworkSession::write(BYTE* data, DWORD dataLength){
	ThreadSync sync;

	if(!mSocket){
		return FALSE;
	}

	if(!data || dataLength <= 0){
		return FALSE;
	}

	WSABUF wsaBuf;
	DWORD writeBytes = 0;
	DWORD writeFlag = 0;

	wsaBuf.buf = (CHAR*)data;
	wsaBuf.len = dataLength;

	if(WSASend(mSocket, &wsaBuf, 1, &writeBytes, writeFlag, &mWriteOverlapped.overlapped, NULL) == SOCKET_ERROR){
		INT lastError = WSAGetLastError();
		if(lastError != WSA_IO_PENDING && lastError != WSAEWOULDBLOCK){
			end();
			return FALSE;
		}
	}

	return TRUE;
}

BOOL NetworkSession::initReadFromForIOCP(VOID){
	ThreadSync sync;

	if(!mSocket){
		return FALSE;
	}

	WSABUF wsaBuf;
	DWORD readBytes = 0;
	DWORD readFlag = 0;
	INT udpRemoteInfoLength = sizeof(mUDPRemoteInfo);

	wsaBuf.buf = (CHAR*)mReadBuffer;
	wsaBuf.len = MAX_BUFFER_LENGTH;

	if(WSARecvFrom(mSocket, &wsaBuf, 1, &readBytes, &readFlag, (LPSOCKADDR)&mUDPRemoteInfo, &udpRemoteInfoLength, &mReadOverlapped.overlapped, NULL) == SOCKET_ERROR){
		INT lastError = WSAGetLastError();
		if(lastError != WSA_IO_PENDING && lastError != WSAEWOULDBLOCK){
			end();
			return FALSE;
		}
	}

	return TRUE;
}

BOOL NetworkSession::readFromForIOCP(LPSTR remoteAddress, USHORT& remotePort, BYTE* data, DWORD& dataLength){
	ThreadSync sync;

	if(!mSocket){
		return FALSE;
	}

	if(!data || dataLength <= 0){
		return FALSE;
	}

	memcpy(data, mReadBuffer, dataLength);
	strcpy(remoteAddress, inet_ntoa(mUDPRemoteInfo.sin_addr));
	remotePort = ntohs(mUDPRemoteInfo.sin_port);

	USHORT ack = 0;
	memcpy(&ack, mReadBuffer, sizeof(USHORT));

	// 수신한 데이터가 ACK 데이터일 경우, 
	// 내가 송신한 데이터를 상대방이 문제없이 수신했다는 의미이므로 Write Complete Event를 발생시킨다.
	if(ack == Constant::RELIABLE_UDP_ACK){
		SetEvent(mReliableUDPWriteCompleteEvent);
		return FALSE;

	// 수신한 데이터가 일반 데이터일 경우,
	// 상대방이 송신한 데이터를 내가 문제없이 수신했다는 의미로 ACK 데이터를 송신한다.
	}else{
		ack = Constant::RELIABLE_UDP_ACK;
		writeTo2(remoteAddress, remotePort, (BYTE*)&ack, sizeof(USHORT));
	}

	return TRUE;
}

BOOL NetworkSession::readFromForEventSelect(LPSTR remoteAddress, USHORT& remotePort, BYTE* data, DWORD& dataLength){
	ThreadSync sync;

	if(!mSocket){
		return FALSE;
	}

	if(!data){
		return FALSE;
	}

	WSABUF wsaBuf;
	DWORD readBytes = 0;
	DWORD readFlag = 0;
	INT udpRemoteInfoLength = sizeof(mUDPRemoteInfo);

	wsaBuf.buf = (CHAR*)mReadBuffer;
	wsaBuf.len = MAX_BUFFER_LENGTH;

	if(WSARecvFrom(mSocket, &wsaBuf, 1, &readBytes, &readFlag, (LPSOCKADDR)&mUDPRemoteInfo, &udpRemoteInfoLength, &mReadOverlapped.overlapped, NULL) == SOCKET_ERROR){
		INT lastError = WSAGetLastError();
		if(lastError != WSA_IO_PENDING && lastError != WSAEWOULDBLOCK){
			end();
			return FALSE;
		}
	}

	memcpy(data, mReadBuffer, readBytes);
	dataLength = readBytes;
	strcpy(remoteAddress, inet_ntoa(mUDPRemoteInfo.sin_addr));
	remotePort = ntohs(mUDPRemoteInfo.sin_port);

	USHORT ack = 0;
	memcpy(&ack, mReadBuffer, sizeof(USHORT));

	// 수신한 데이터가 ACK 데이터일 경우, 
	// 내가 송신한 데이터를 상대방이 문제없이 수신했다는 의미이므로 Write Complete Event를 발생시킨다.
	if(ack == Constant::RELIABLE_UDP_ACK){
		SetEvent(mReliableUDPWriteCompleteEvent);
		return FALSE;

	// 수신한 데이터가 일반 데이터일 경우,
	// 상대방이 송신한 데이터를 내가 문제없이 수신했다는 의미로 ACK 데이터를 송신한다.
	}else{
		ack = Constant::RELIABLE_UDP_ACK;
		writeTo2(remoteAddress, remotePort, (BYTE*)&ack, sizeof(SHORT));
	}
	
	return TRUE;
}

BOOL NetworkSession::writeTo(LPCSTR remoteAddress, USHORT remotePort, BYTE* data, DWORD dataLength){
	ThreadSync sync;

	if(!mSocket){
		return FALSE;
	}

	if(!remoteAddress || remotePort <= 0 || !data || dataLength <= 0){
		return FALSE;
	}

	NETWORK_INFO network;
	network.set(data, dataLength, remoteAddress, remotePort);
	if(!mReliableWriteQueue.enq(network)){
		return FALSE;
	}

	if(!mIsReliableUDPSending){
		mIsReliableUDPSending = TRUE;
		SetEvent(mReliableUDPThreadWakeUpEvent);
	}

	return TRUE;
}

BOOL NetworkSession::writeTo2(LPCSTR remoteAddress, USHORT remotePort, BYTE* data, DWORD dataLength){
	ThreadSync sync;

	if(!mSocket){
		return FALSE;
	}

	if(!remoteAddress || remotePort <= 0 || !data || dataLength <= 0){
		return FALSE;
	}

	WSABUF wsaBuf;
	DWORD writeBytes = 0;
	DWORD writeFlag = 0;
	SOCKADDR_IN udpRemoteInfo;
	INT udpRemoteInfoLength = sizeof(udpRemoteInfo);

	wsaBuf.buf = (CHAR*)data;
	wsaBuf.len = dataLength;

	udpRemoteInfo.sin_family = AF_INET;
	udpRemoteInfo.sin_port = htons(remotePort);
	udpRemoteInfo.sin_addr.S_un.S_addr = inet_addr(remoteAddress);

	if(WSASendTo(mSocket, &wsaBuf, 1, &writeBytes, writeFlag, (LPSOCKADDR)&udpRemoteInfo, udpRemoteInfoLength, &mWriteOverlapped.overlapped, NULL) == SOCKET_ERROR){
		INT lastError = WSAGetLastError();
		if(lastError != WSA_IO_PENDING && lastError != WSAEWOULDBLOCK){
			end();
			return FALSE;
		}
	}

	return TRUE;
}

SOCKET NetworkSession::getSocket(VOID){
	ThreadSync sync;

	return mSocket;
}

BOOL NetworkSession::getLocalIP(WCHAR* ip){
	ThreadSync sync;

	if(!mSocket){
		return FALSE;
	}

	CHAR name[256] = {0, };

	gethostname(name, sizeof(name));

	PHOSTENT host = gethostbyname(name);
	if(host){
		if(MultiByteToWideChar(CP_ACP, 0, inet_ntoa(*(struct in_addr*)*host->h_addr_list), -1, ip, 32) > 0){
			return TRUE;
		}
	}

	return FALSE;
}

USHORT NetworkSession::getLocalPort(VOID){
	ThreadSync sync;

	if(!mSocket){
		return Constant::RESULT_FAIL;
	}

	SOCKADDR_IN localAddressInfo;
	INT localAddressInfoLength = sizeof(localAddressInfo);

	memset(&localAddressInfo, 0, sizeof(localAddressInfo));

	if(getsockname(mSocket, (LPSOCKADDR)&localAddressInfo, &localAddressInfoLength) != SOCKET_ERROR){
		return ntohs(localAddressInfo.sin_port);
	}

	return Constant::RESULT_FAIL;
}

BOOL NetworkSession::getRemoteAddressAfterAccept(LPTSTR remoteAddress, USHORT& remotePort){
	ThreadSync sync;

	if(!remoteAddress){
		return FALSE;
	}

	SOCKADDR_IN* localAddressInfo = NULL;
	INT localAddressInfoLength = 0;
	SOCKADDR_IN* remoteAddressInfo = NULL;
	INT remoteAddressInfoLength = 0;

	GetAcceptExSockaddrs(mReadBuffer, 0, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, (SOCKADDR**)&localAddressInfo, &localAddressInfoLength, (SOCKADDR**)&remoteAddress, &remoteAddressInfoLength);
	
	CHAR tempRemoteAddress[32] = {0, };
	strcpy(tempRemoteAddress, inet_ntoa(remoteAddressInfo->sin_addr));
	MultiByteToWideChar(CP_ACP, 0, tempRemoteAddress, -1, remoteAddress, 32);
	remotePort = ntohs(remoteAddressInfo->sin_port);

	return TRUE;
}

VOID NetworkSession::reliableUDPThreadCallback(VOID){
	DWORD eventID = 0;
	HANDLE threadEvents[2] = {mReliableUDPThreadDestroyEvent, mReliableUDPThreadWakeUpEvent};
	NETWORK_INFO network;
	BOOL nextData = TRUE; // TRUE:NEXT_DATA, FALSE:RETRY
	INT retryCount = 0;

	while(TRUE){
		SetEvent(mReliableUDPThreadStartUpEvent);

		eventID = WaitForMultipleObjects(2, threadEvents, FALSE, INFINITE);
		switch(eventID){
		case WAIT_OBJECT_0: // mReliableUDPThreadDestroyEvent
			return;

		case WAIT_OBJECT_0 + 1: // mReliableUDPThreadWakeUpEvent
			while(TRUE){
				if(nextData){
					network.init();
					if(!mReliableWriteQueue.deq(network)){
						break;
					}
				}

				if(!writeTo2(network.remoteAddress, network.remotePort, network.data, network.dataLength)){
					return;
				}

				DWORD result = WaitForSingleObject(mReliableUDPWriteCompleteEvent, 10);
				if(result == WAIT_OBJECT_0 || retryCount == Constant::RELIABLE_UDP_RETRY_COUNT){ // mReliableUDPWriteCompleteEvent OR RELIABLE_UDP_RETRY_COUNT
					nextData = TRUE;
					retryCount = 0;
				}else{
					nextData = FALSE;
					retryCount++;
				}
			}

			mIsReliableUDPSending = FALSE;
			break;
		}
	}
}
