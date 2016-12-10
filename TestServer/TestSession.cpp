#include "stdafx.h"
#include "TestSession.h"

TestSession::TestSession(VOID){
}

TestSession::~TestSession(VOID){
}

BOOL TestSession::initialize(SOCKET listenSocket){
	if(!PacketSession::begin()){
		return FALSE;
	}

	if(!NetworkSession::accept(listenSocket)){
		return FALSE;
	}

	return TRUE;
}

BOOL TestSession::procIOConnected(VOID){
	if(!NetworkSession::initReadForIOCP()){
		return FALSE;
	}

	BYTE data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	return PacketSession::writePacket(0, data, sizeof(data));
}

BOOL TestSession::procIODisconnected(SOCKET listenSocket){
	return initialize(listenSocket);
}
