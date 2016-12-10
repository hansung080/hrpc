#include "stdafx.h"
#include "MainClient.h"

MainClient::MainClient(ClientSession* clientSession) : clientSession(clientSession) {
}

MainClient::~MainClient(VOID){
}

BOOL MainClient::begin(VOID){
	if(!clientSession->beginTCP(SERVER_ADDRESS, ClientConstant::SERVER_PORT)){
		_tprintf(_T("TCP connection failed to server <%s:%d>."), _T(SERVER_ADDRESS), ClientConstant::SERVER_PORT);
		return FALSE;
	}
	
	userProcessor = new UserProcessor(clientSession);
	computerProcessor = new ComputerProcessor(clientSession);
	programProcessor = new ProgramProcessor(clientSession);

	return TRUE;
}

BOOL MainClient::end(VOID){
	delete userProcessor;
	delete computerProcessor;
	delete programProcessor;

	clientSession->end();

	return TRUE;
}

VOID MainClient::start(VOID){
	if(!begin()){
		return;
	}
	
	while(TRUE){
		system("cls");

		TCHAR command[32] = {0, };

		_tprintf(_T("Enter command (user/computer/program) :"));
		memset(command, 0, sizeof(command));
		_getts(command);

		if(_tcscmp(_tcslwr(command), _T("user")) == 0){
			_tprintf(_T("Enter command (ins/sel) :"));
			memset(command, 0, sizeof(command));
			_getts(command);

			if(_tcscmp(_tcslwr(command), _T("ins")) == 0){
				userProcessor->insert();

			}else if(_tcscmp(_tcslwr(command), _T("sel")) == 0){
				userProcessor->select();

			}else if(_tcscmp(_tcslwr(command), _T("q")) == 0 || _tcscmp(_tcslwr(command), _T("quit")) == 0){
				_tprintf(_T("Exit~!!\n"));
				break;

			}else{
				continue;
			}

		}else if(_tcscmp(_tcslwr(command), _T("computer")) == 0){
			_tprintf(_T("Enter command (ins/sel) :"));
			memset(command, 0, sizeof(command));
			_getts(command);

			if(_tcscmp(_tcslwr(command), _T("ins")) == 0){
				computerProcessor->insert();

			}else if(_tcscmp(_tcslwr(command), _T("sel")) == 0){
				computerProcessor->select();

			}else if(_tcscmp(_tcslwr(command), _T("q")) == 0 || _tcscmp(_tcslwr(command), _T("quit")) == 0){
				_tprintf(_T("Exit~!!\n"));
				break;

			}else{
				continue;
			}

		}else if(_tcscmp(_tcslwr(command), _T("program")) == 0){
			_tprintf(_T("Enter command (ins/sel) :"));
			memset(command, 0, sizeof(command));
			_getts(command);

			if(_tcscmp(_tcslwr(command), _T("ins")) == 0){
				programProcessor->insert();

			}else if(_tcscmp(_tcslwr(command), _T("sel")) == 0){
				programProcessor->select();

			}else if(_tcscmp(_tcslwr(command), _T("q")) == 0 || _tcscmp(_tcslwr(command), _T("quit")) == 0){
				_tprintf(_T("Exit~!!\n"));
				break;

			}else{
				continue;
			}

		}else if(_tcscmp(_tcslwr(command), _T("q")) == 0 || _tcscmp(_tcslwr(command), _T("quit")) == 0){
			_tprintf(_T("Exit~!!\n"));
			break;

		}else{
			continue;
		}
	} // end of while

	end();
}