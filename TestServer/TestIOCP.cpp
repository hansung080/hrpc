#include "stdafx.h"
#include "TestSession.h"
#include "TestIOCP.h"

TestIOCP::TestIOCP(VOID){
	mListenSession = NULL;
	memset(mTestSessions, 0, sizeof(mTestSessions));
}

TestIOCP::~TestIOCP(VOID){
}

BOOL TestIOCP::begin(VOID){
	mListenSession = new TestSession();

	if(!IOCP::begin()){
		return FALSE;
	}

	if(!mListenSession->begin()){
		return FALSE;
	}
	
	if(!mListenSession->bindTCP()){
		return FALSE;
	}

	if(!mListenSession->listen(TestConstant::DEFAULT_PORT, MAX_SESSION)){
		return FALSE;
	}

	if(!IOCP::registerSocketToIOCP(mListenSession->getSocket(), reinterpret_cast<ULONG_PTR>(mListenSession))){
		return FALSE;
	}

	// Client Socket을 관리 할 TestSession을 미리 생성해 둠 (성능상의 이익을 위해서)
	for(USHORT i = 0; i < MAX_SESSION; i++){
		mTestSessions[i] = new TestSession();

		if(!mTestSessions[i]->initialize(mListenSession->getSocket())){
			for(USHORT j = 0; j <= i; j++){
				mTestSessions[j]->end();
				delete mTestSessions[j];
			}

			return FALSE;
		}
	}

	return TRUE;
}

BOOL TestIOCP::end(VOID){
	mListenSession->end();

	for(USHORT i = 0; i < MAX_SESSION; i++){
		mTestSessions[i]->end();
		delete mTestSessions[i];
	}

	delete mListenSession;

	return IOCP::end();
}

VOID TestIOCP::onIORead(VOID* object, DWORD readLength){
	_tprintf(_T("onIORead : 0x%x\n"), object);

	DWORD protocol = 0;
	BYTE data[MAX_BUFFER_LENGTH] = { 0, };
	DWORD dataLength = 0;

	TestSession* session = reinterpret_cast<TestSession*>(object);

	if(!session->readPacketForIOCP(readLength)){
		return;
	}

	// 루프 처리를 하는 이유는 Nagle 알고리즘에 의해서 2개 이상의 패킷이 합쳐져서 오거나,
	// 1개의 패킷이 완전히 오지 못한 경우, 패킷을 연속적으로 처리하기 위함입니다.
	while(session->parsePacket(protocol, data, dataLength)){
		// 프로토콜 처리부
	}
}

VOID TestIOCP::onIOWrote(VOID* object, DWORD wroteLength){
	_tprintf(_T("onIOWrote : 0x%x\n"), object);

	TestSession* session = reinterpret_cast<TestSession*>(object);

	session->writeComplete();
}

VOID TestIOCP::onIOConnected(VOID* object){
	_tprintf(_T("onIOConnected : 0x%x\n"), object);

	TestSession* session = reinterpret_cast<TestSession*>(object);

	if(!IOCP::registerSocketToIOCP(session->getSocket(), reinterpret_cast<ULONG_PTR>(session))){
		return;
	}

	if(!session->procIOConnected()){
		return;
	}
}

VOID TestIOCP::onIODisconnected(VOID* object){
	_tprintf(_T("onIODisconnected : 0x%x\n"), object);

	TestSession* session = reinterpret_cast<TestSession*>(object);

	if(!session->procIODisconnected(mListenSession->getSocket())){
		return;
	}
}
