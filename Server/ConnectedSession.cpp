#include "stdafx.h"
#include "ConnectedSession.h"

ConnectedSession::ConnectedSession(VOID){
	mConnected = FALSE;
}

ConnectedSession::~ConnectedSession(VOID){
}

BOOL ConnectedSession::restart(SOCKET listenSocket){
	ThreadSync sync;

	PacketSession::end();

	return PacketSession::begin() && NetworkSession::accept(listenSocket);
}

VOID ConnectedSession::setConnected(BOOL connected){
	ThreadSync sync;

	mConnected = connected;
}

BOOL ConnectedSession::getConnected(VOID){
	ThreadSync sync;

	return mConnected;
}