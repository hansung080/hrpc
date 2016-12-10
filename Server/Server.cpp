// Server.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[]){
	// 현재 스레드에서 COM library 초기화
	CoInitialize(NULL);

	// Winsock DLL 2.2 버전 로드
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	if(!MiniDump::begin()){
		return 1;
	}

	ServerIOCP serverIOCP;
	if(serverIOCP.begin()){
		_tprintf(_T("Server started at port <%d>\n"), ServerConstant::DEFAULT_PORT);
		getchar(); // 메인 스레드를 대기 상태로 만들기 위함.
		serverIOCP.end();
	}

	MiniDump::end();
	WSACleanup();
	CoUninitialize();

	return 0;
}
