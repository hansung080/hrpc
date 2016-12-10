#include "stdafx.h"
#include "ComputerProcessor.h"

ComputerProcessor::ComputerProcessor(ClientSession* clientSession) : Processor(clientSession) {
}

ComputerProcessor::~ComputerProcessor(VOID){
}

VOID ComputerProcessor::insert(VOID){
	TCHAR command[32] = {0, };
	BYTE writeData[MAX_BUFFER_LENGTH] = {0, };

	WCHAR computer_name[32] = {0, };
	WCHAR ip_address[32] = {0, };
	BYTE cpu_type = 0;
	DWORD ram = 0;
	DWORD hdd = 0;

	// computer_name
	_tprintf(_T("Enter computer name :"));
	memset(command, 0, sizeof(command));
	_getts(command);
	_tcsncpy(computer_name, command, sizeof(TCHAR) * _tcslen(command));

	// ip_address
	_tprintf(_T("Enter ip address :"));
	memset(command, 0, sizeof(command));
	_getts(command);
	_tcsncpy(ip_address, command, sizeof(TCHAR) * _tcslen(command));

	// cpu_type
	_tprintf(_T("Enter cpu type :"));
	memset(command, 0, sizeof(command));
	_getts(command);
	cpu_type = _ttoi(command);

	// ram
	_tprintf(_T("Enter ram :"));
	memset(command, 0, sizeof(command));
	_getts(command);
	ram = _ttoi(command);

	// hdd
	_tprintf(_T("Enter hdd :"));
	memset(command, 0, sizeof(command));
	_getts(command);
	hdd = _ttoi(command);

	clientSession->writePacket(PT_INS_COMPUTER
		                      ,writeData
		                      ,WRITE_PT_INS_COMPUTER(writeData
		                                            ,computer_name
		                                            ,ip_address
		                                            ,cpu_type
		                                            ,ram
		                                            ,hdd));

	_tprintf(_T("Press any key..."));
	getchar();
}

VOID ComputerProcessor::select(VOID){
	TCHAR command[32] = {0, };
	BYTE writeData[MAX_BUFFER_LENGTH] = {0, };
	DWORD protocol = 0;
	BYTE data[MAX_BUFFER_LENGTH] = {0, }; // data -> readData
	DWORD dataLength = 0;

	WCHAR computer_name[32] = {0, };

	// computer_name
	_tprintf(_T("Enter computer name :"));
	memset(command, 0, sizeof(command));
	_getts(command);
	_tcsncpy(computer_name, command, sizeof(TCHAR) * _tcslen(command));

	clientSession->writePacket(PT_SEL_COMPUTER
		                      ,writeData
		                      ,WRITE_PT_SEL_COMPUTER(writeData
		                                            ,computer_name));

	while(TRUE){
		if(!clientSession->readPacket(protocol, data, dataLength)){
			if(protocol == PT_SEL_COMPUTER_RESULT){
				break;
			}
		}
	}

	READ_DATA(PT_SEL_COMPUTER_RESULT);

	_tprintf(_T("Select Result : computer name = [%s], ip address = [%s], cpu type = [%d], ram = [%d], hdd = [%d]\n")
		    ,readData.computer_name
		    ,readData.ip_address
		    ,readData.cpu_type
		    ,readData.ram
		    ,readData.hdd);

	_tprintf(_T("Press any key..."));
	getchar();
}