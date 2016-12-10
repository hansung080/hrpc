#include "stdafx.h"
#include "UserProcessor.h"

UserProcessor::UserProcessor(ClientSession* clientSession) : Processor(clientSession) {
}

UserProcessor::~UserProcessor(VOID){
}

VOID UserProcessor::insert(VOID){
	TCHAR command[32] = {0, };
	BYTE writeData[MAX_BUFFER_LENGTH] = {0, };

	WCHAR user_id[32] = {0, };
	WCHAR user_name[32] = {0, };
	DWORD age = 0;
	BYTE sex = 0;
	WCHAR address[32] = {0, };

	// user_id
	_tprintf(_T("Enter user id :"));
	memset(command, 0, sizeof(command));
	_getts(command);
	_tcsncpy(user_id, command, sizeof(TCHAR) * _tcslen(command));

	// user_name
	_tprintf(_T("Enter user name :"));
	memset(command, 0, sizeof(command));
	_getts(command);
	_tcsncpy(user_name, command, sizeof(TCHAR) * _tcslen(command));

	// age
	_tprintf(_T("Enter age :"));
	memset(command, 0, sizeof(command));
	_getts(command);
	age = _ttoi(command);

	// sex
	_tprintf(_T("Enter sex :"));
	memset(command, 0, sizeof(command));
	_getts(command);
	sex = _ttoi(command);

	// address
	_tprintf(_T("Enter address :"));
	memset(command, 0, sizeof(command));
	_getts(command);
	_tcsncpy(address, command, sizeof(TCHAR) * _tcslen(command));

	clientSession->writePacket(PT_INS_USER
		                      ,writeData
		                      ,WRITE_PT_INS_USER(writeData
		                                        ,user_id
		                                        ,user_name
		                                        ,age
		                                        ,sex
		                                        ,address));

	_tprintf(_T("Press any key..."));
	getchar();
}

VOID UserProcessor::select(VOID){
	TCHAR command[32] = {0, };
	BYTE writeData[MAX_BUFFER_LENGTH] = {0, };
	DWORD protocol = 0;
	BYTE data[MAX_BUFFER_LENGTH] = {0, }; // data -> readData
	DWORD dataLength = 0;
	
	WCHAR user_id[32] = {0, };

	// user_id
	_tprintf(_T("Enter user id :"));
	memset(command, 0, sizeof(command));
	_getts(command);
	_tcsncpy(user_id, command, sizeof(TCHAR) * _tcslen(command));

	clientSession->writePacket(PT_SEL_USER
		                      ,writeData
		                      ,WRITE_PT_SEL_USER(writeData
		                                        ,user_id));

	while(TRUE){
		if(!clientSession->readPacket(protocol, data, dataLength)){
			if(protocol == PT_SEL_USER_RESULT){
				break;
			}
		}
	}

	READ_DATA(PT_SEL_USER_RESULT);

	_tprintf(_T("Select Result : user id = [%s], user name = [%s], age = [%d], sex = [%d], address = [%s]\n")
		    ,readData.user_id
		    ,readData.user_name
		    ,readData.age
		    ,readData.sex
		    ,readData.address);

	_tprintf(_T("Press any key..."));
	getchar();
}
