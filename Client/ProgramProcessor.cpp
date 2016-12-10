#include "stdafx.h"
#include "ProgramProcessor.h"

ProgramProcessor::ProgramProcessor(ClientSession* clientSession) : Processor(clientSession) {
}

ProgramProcessor::~ProgramProcessor(VOID){
}

VOID ProgramProcessor::insert(VOID){
	TCHAR command[32] = {0, };
	BYTE writeData[MAX_BUFFER_LENGTH] = {0, };

	WCHAR program_name[32] = {0, };
	DWORD cost = 0;
	WCHAR comment[32] = {0, };

	// program_name
	_tprintf(_T("Enter program name :"));
	memset(command, 0, sizeof(command));
	_getts(command);
	_tcsncpy(program_name, command, sizeof(TCHAR) * _tcslen(command));

	// cost
	_tprintf(_T("Enter cost :"));
	memset(command, 0, sizeof(command));
	_getts(command);
	cost = _ttoi(command);

	// comment
	_tprintf(_T("Enter comment :"));
	memset(command, 0, sizeof(command));
	_getts(command);
	_tcsncpy(comment, command, sizeof(TCHAR) * _tcslen(command));

	clientSession->writePacket(PT_INS_PROGRAM
		                      ,writeData
		                      ,WRITE_PT_INS_PROGRAM(writeData
		                      ,program_name
		                      ,cost
		                      ,comment));

	_tprintf(_T("Press any key..."));
	getchar();
}

VOID ProgramProcessor::select(VOID){
	TCHAR command[32] = {0, };
	BYTE writeData[MAX_BUFFER_LENGTH] = {0, };
	DWORD protocol = 0;
	BYTE data[MAX_BUFFER_LENGTH] = {0, }; // data -> readData
	DWORD dataLength = 0;

	WCHAR program_name[32] = { 0, };

	// program_name
	_tprintf(_T("Enter program name :"));
	memset(command, 0, sizeof(command));
	_getts(command);
	_tcsncpy(program_name, command, sizeof(TCHAR) * _tcslen(command));

	clientSession->writePacket(PT_SEL_PROGRAM
		                      ,writeData
		                      ,WRITE_PT_SEL_PROGRAM(writeData
		                                           ,program_name));

	while(TRUE){
		if(!clientSession->readPacket(protocol, data, dataLength)){
			if(protocol == PT_SEL_PROGRAM_RESULT){
				break;
			}
		}
	}

	READ_DATA(PT_SEL_PROGRAM_RESULT);

	_tprintf(_T("Select Result : program name = [%s], cost = [%d], comment = [%s]\n")
		    ,readData.program_name
		    ,readData.cost
		    ,readData.comment);

	_tprintf(_T("Press any key..."));
	getchar();
}