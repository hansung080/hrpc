#include "stdafx.h"
#include "ConnectedSessionManager.h"

ConnectedSessionManager::ConnectedSessionManager(VOID){
}

ConnectedSessionManager::~ConnectedSessionManager(VOID){
}

BOOL ConnectedSessionManager::begin(SOCKET listenSocket){
	ThreadSync sync;

	if(!listenSocket){
		return FALSE;
	}

	for(DWORD i = 0; i < MAX_USER; i++){
		ConnectedSession* connectedSession = new ConnectedSession();
		mConnectedSessions.push_back(connectedSession);
	}

	for(DWORD i = 0; i < mConnectedSessions.size(); i++){
		if(!mConnectedSessions[i]->begin()){
			end();
			return FALSE;
		}

		if(!mConnectedSessions[i]->accept(listenSocket)){
			end();
			return FALSE;
		}
	}

	return TRUE;
}

BOOL ConnectedSessionManager::end(VOID){
	ThreadSync sync;

	for(DWORD i = 0; i < mConnectedSessions.size(); i++){
		mConnectedSessions[i]->end();
		delete mConnectedSessions[i];
	}

	mConnectedSessions.clear();

	return TRUE;
}

VOID ConnectedSessionManager::writeAll(DWORD protocol, BYTE* data, DWORD length){
	ThreadSync sync;

	for(DWORD i = 0; i < mConnectedSessions.size(); i++){
		if(mConnectedSessions[i]->getConnected()){
			mConnectedSessions[i]->writePacket(protocol, data, length);
		}
	}
}