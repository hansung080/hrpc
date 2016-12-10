#include "stdafx.h"
#include "ServerIOCP.h"

DWORD WINAPI keepThreadCallback(LPVOID param){
	ServerIOCP* self = (ServerIOCP*)param;
	self->keepThreadCallback();
	return 0;
}

ServerIOCP::ServerIOCP(VOID){
	mListenSession = NULL;
	mKeepThread = NULL;
	mKeepThreadDestroyEvent = NULL;
}

ServerIOCP::~ServerIOCP(VOID){
}

BOOL ServerIOCP::begin(VOID){
	if(!IOCP::begin()){
		return FALSE;
	}

	mListenSession = new NetworkSession();

	if(!mListenSession->begin()){
		ServerIOCP::end();
		return FALSE;
	}

	if(!mListenSession->bindTCP()){
		ServerIOCP::end();
		return FALSE;
	}

	if(!mListenSession->listen(ServerConstant::DEFAULT_PORT, MAX_USER)){
		ServerIOCP::end();
		return FALSE;
	}

	if(!IOCP::registerSocketToIOCP(mListenSession->getSocket(), reinterpret_cast<ULONG_PTR>(mListenSession))){
		ServerIOCP::end();
		return FALSE;
	}

	if(!mConnectedSessionManager.begin(mListenSession->getSocket())){
		ServerIOCP::end();
		return FALSE;
	}

	mKeepThreadDestroyEvent = CreateEvent(0, FALSE, FALSE, 0);
	if(!mKeepThreadDestroyEvent){
		ServerIOCP::end();
		return FALSE;
	}

	mKeepThread = CreateThread(NULL, 0, ::keepThreadCallback, this, 0, NULL);
	if(!mKeepThread){
		ServerIOCP::end();
		return FALSE;
	}

	return TRUE;
}

BOOL ServerIOCP::end(VOID){
	std::map<std::wstring, USER*>::iterator iterUser;
	for(iterUser = mUsers.begin(); iterUser != mUsers.end(); iterUser++){
		delete iterUser->second;
	}
	mUsers.clear();

	std::map<std::wstring, COMPUTER*>::iterator iterComputer;
	for(iterComputer = mComputers.begin(); iterComputer != mComputers.end(); iterComputer++){
		delete iterComputer->second;
	}
	mComputers.clear();

	std::map<std::wstring, PROGRAM*>::iterator iterProgram;
	for(iterProgram = mPrograms.begin(); iterProgram != mPrograms.end(); iterProgram++){
		delete iterProgram->second;
	}
	mPrograms.clear();

	if(mKeepThread){
		SetEvent(mKeepThreadDestroyEvent);
		WaitForSingleObject(mKeepThread, INFINITE);
		CloseHandle(mKeepThread);
		mKeepThread = NULL;
	}

	if(mKeepThreadDestroyEvent){
		CloseHandle(mKeepThreadDestroyEvent);
		mKeepThreadDestroyEvent = NULL;
	}

	IOCP::end();

	mConnectedSessionManager.end();

	if(mListenSession){
		mListenSession->end();
		delete mListenSession;
	}

	return TRUE;
}

VOID ServerIOCP::keepThreadCallback(VOID){
	DWORD keepAlive = ServerConstant::KEEP_ALIVE_DATA;
	DWORD result;

	while(TRUE){
		result = WaitForSingleObject(mKeepThreadDestroyEvent, ServerConstant::KEEP_ALIVE_INTERVAL);
		if(result == WAIT_OBJECT_0){
			return;
		}

		mConnectedSessionManager.writeAll(ServerConstant::KEEP_ALIVE_PROTOCOL, (BYTE*)&keepAlive, sizeof(DWORD));
	}
}

VOID ServerIOCP::onIORead(VOID* object, DWORD readLength){
	ConnectedSession* connectedSession = reinterpret_cast<ConnectedSession*>(object);

	DWORD protocol = 0;
	BYTE data[MAX_BUFFER_LENGTH] = {0, };
	DWORD dataLength = 0;

	if(connectedSession->readPacketForIOCP(readLength)){
		// 루프 처리를 하는 이유는 Nagle 알고리즘에 의해서 2개 이상의 패킷이 합쳐져서 오거나,
		// 1개의 패킷이 완전히 오지 못한 경우, 패킷을 연속적으로 처리하기 위함입니다.
		while(connectedSession->parsePacket(protocol, data, dataLength)){
			// 프로토콜 처리부
			switch(protocol){
			case PT_INS_USER:
				PROC_PT_INS_USER(connectedSession, protocol, data, dataLength);
				break;

			case PT_SEL_USER:
				PROC_PT_SEL_USER(connectedSession, protocol, data, dataLength);
				break;

			case PT_INS_COMPUTER:
				PROC_PT_INS_COMPUTER(connectedSession, protocol, data, dataLength);
				break;

			case PT_SEL_COMPUTER:
				PROC_PT_SEL_COMPUTER(connectedSession, protocol, data, dataLength);
				break;

			case PT_INS_PROGRAM:
				PROC_PT_INS_PROGRAM(connectedSession, protocol, data, dataLength);
				break;

			case PT_SEL_PROGRAM:
				PROC_PT_SEL_PROGRAM(connectedSession, protocol, data, dataLength);
				break;
			}
		}
	}

	if(!connectedSession->initReadForIOCP()){
		connectedSession->restart(mListenSession->getSocket());
	}
}

VOID ServerIOCP::onIOWrote(VOID* object, DWORD wroteLength){
}

VOID ServerIOCP::onIOConnected(VOID* object){
	ConnectedSession* connectedSession = reinterpret_cast<ConnectedSession*>(object);

	//======================================================================
	// Print log
	//----------------------------------------------------------------------
	WCHAR localIP[32] = { 0, };
	USHORT localPort = 0;
	connectedSession->getLocalIP(localIP);
	localPort = connectedSession->getLocalPort();
	_tprintf(_T("Client <%s:%d> is connected.\n"), localIP, localPort);
	//======================================================================

	if(!IOCP::registerSocketToIOCP(connectedSession->getSocket(), reinterpret_cast<ULONG_PTR>(connectedSession))){
		return;
	}

	if(!connectedSession->initReadForIOCP()){
		connectedSession->restart(mListenSession->getSocket());
		return;
	}

	connectedSession->setConnected(TRUE);
}

VOID ServerIOCP::onIODisconnected(VOID* object){
	ConnectedSession* connectedSession = reinterpret_cast<ConnectedSession*>(object);

	//======================================================================
	// Print log
	//----------------------------------------------------------------------
	WCHAR localIP[32] = { 0, };
	USHORT localPort = 0;
	connectedSession->getLocalIP(localIP);
	localPort = connectedSession->getLocalPort();
	_tprintf(_T("Client <%s:%d> is disconnected.\n"), localIP, localPort);
	//======================================================================

	connectedSession->restart(mListenSession->getSocket());

	connectedSession->setConnected(FALSE);
}
