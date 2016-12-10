// Client.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
#include "stdafx.h"
#include "TestClientSession.h"
#include "MainClient.h"

int _tmain(int argc, _TCHAR* argv[]){
	// Winsock DLL 2.2 버전 로드
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	TestClientSession* clientSession = new TestClientSession();
	MainClient* mainClient = new MainClient(clientSession);

	mainClient->start();

	delete clientSession;
	delete mainClient;

	WSACleanup();

	return 0;
}