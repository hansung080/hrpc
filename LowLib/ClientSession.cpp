#include "stdafx.h"
#include "CriticalSection.h"
#include "MultiThreadSync.h"
#include "NetworkInfo.h"
#include "PacketInfo.h"
#include "ClientInfo.h"
#include "CircularQueue.h"
#include "NetworkSession.h"
#include "PacketSession.h"
#include "EventSelect.h"
#include "ClientSession.h"

ClientSession::ClientSession(VOID){
	mIsUDP = NULL;
}

ClientSession::~ClientSession(VOID){
}

BOOL ClientSession::beginTCP(LPSTR remoteAddress, USHORT remotePort){
	if(!remoteAddress || remotePort <= 0){
		return FALSE;
	}

	if(!mSession.begin()){
		end();
		return FALSE;
	}

	if(!mSession.bindTCP()){
		end();
		return FALSE;
	}

	if(!EventSelect::begin(mSession.getSocket())){
		end();
		return FALSE;
	}

	if(!mSession.connet(remoteAddress, remotePort)){
		end();
		return FALSE;
	}

	mIsUDP = FALSE;

	return TRUE;
}

BOOL ClientSession::beginUDP(USHORT remotePort){
#ifdef _EXTERNAL_RELEASE_
	if(remotePort <= 0){
		return FALSE;
	}
#endif // _EXTERNAL_RELEASE_

	if(!mSession.begin()){
		end();
		return FALSE;
	}

	if(!mSession.bindUDP(remotePort)){
		end();
		return FALSE;
	}

	if(!EventSelect::begin(mSession.getSocket())){
		end();
		return FALSE;
	}

	mIsUDP = TRUE;

	return TRUE;
}

BOOL ClientSession::end(VOID){
	if(!mSession.end()){
		return FALSE;
	}

	if(!EventSelect::end()){
		return FALSE;
	}

	return TRUE;
}

BOOL ClientSession::readPacket(DWORD& protocol, BYTE* data, DWORD& dataLength){
	CLIENT_INFO client;

	if(!mReadPacketQueue.deq(client)){
		return FALSE;
	}

	client.get(protocol, data, dataLength);
	
	return TRUE;
}

BOOL ClientSession::readFromPacket(LPSTR remoteAddress, USHORT& remotePort, DWORD& protocol, BYTE* data, DWORD& dataLength){
	CLIENT_INFO client;

	if(!mReadPacketQueue.deq(client)){
		return FALSE;
	}

	client.get(protocol, data, dataLength, remoteAddress, remotePort);

	return TRUE;
}

BOOL ClientSession::writePacket(DWORD protocol, const BYTE* data, DWORD dataLength){
	if(!mSession.writePacket(protocol, data, dataLength)){
		return FALSE;
	}

	if(!mSession.writeComplete()){
		return FALSE;
	}

	return TRUE;
}

BOOL ClientSession::writeToPacket(LPCSTR remoteAddress, USHORT remotePort, DWORD protocol, const BYTE* data, DWORD dataLength){
	if(!mSession.writeToPacket(remoteAddress, remotePort, protocol, data, dataLength)){
		return FALSE;
	}

	if(!mSession.writeComplete()){
		return FALSE;
	}

	return TRUE;
}

BOOL ClientSession::getLocalIP(WCHAR* ip){
	return mSession.getLocalIP(ip);
}

USHORT ClientSession::getLocalPort(VOID){
	return mSession.getLocalPort();
}

VOID ClientSession::onIORead(VOID){
	DWORD protocol = 0;
	BYTE data[MAX_BUFFER_LENGTH] = {0, };
	DWORD dataLength = 0;

	// UDP의 경우
	if(mIsUDP){
		CHAR remoteAddress[IP_ADDRESS_LENGTH] = {0, };
		USHORT remotePort = 0;

		if(mSession.readFromPacketForEventSelect(remoteAddress, remotePort)){
			while(mSession.parseFromPacket(remoteAddress, remotePort, protocol, data, dataLength)){
				CLIENT_INFO client;
				client.set(protocol, data, dataLength, remoteAddress, remotePort);
				mReadPacketQueue.enq(client);
			}
		}
	
	// TCP의 경우
	}else{
		if(mSession.readPacketForEventSelect()){
			while(mSession.parsePacket(protocol, data, dataLength)){
				CLIENT_INFO client;
				client.set(protocol, data, dataLength);
				mReadPacketQueue.enq(client);
			}
		}
	}
}
