// TestServer.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.

#include "stdafx.h"
#include "TestSession.h"
#include "TestIOCP.h"

int _tmain(int argc, _TCHAR* argv[]){
	
	// Winsock DLL 2.2 버전을 로드합니다.
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	TestIOCP iocp;

	iocp.begin();

	_tprintf(_T("Test Server started at port %d\n"), TestConstant::DEFAULT_PORT);

	// 메인 스레드를 대기 상태로 만들기 위함.
	getchar();

	iocp.end();

	WSACleanup();

	return 0;
}
