#include "stdafx.h"
#include "ConnectedSession.h"
#include "ConnectedSessionManager.h"
#include "ServerIOCP.h"

#define READ_DATA(PROTOCOL)\
			S_##PROTOCOL readData;\
			READ_##PROTOCOL(data, readData);

VOID ServerIOCP::PROC_PT_INS_USER(ConnectedSession* connectedSession, DWORD protocol, BYTE* data, DWORD dataLength){
	READ_DATA(PT_INS_USER);

	USER* user = new USER();
	user->set(readData.user_id
		     ,readData.user_name
			 ,readData.age
			 ,readData.sex
			 ,readData.address);

	mUsers.insert(std::make_pair(user->user_id, user));
}

VOID ServerIOCP::PROC_PT_SEL_USER(ConnectedSession* connectedSession, DWORD protocol, BYTE* data, DWORD dataLength){
	READ_DATA(PT_SEL_USER);
	BYTE writeData[MAX_BUFFER_LENGTH] = {0, };

	std::map<std::wstring, USER*>::iterator iter = mUsers.find(readData.user_id);

	// 해당 데이터가 존재할 경우
	if(iter != mUsers.end()){
		connectedSession->writePacket(PT_SEL_USER_RESULT
								     ,writeData
									 ,WRITE_PT_SEL_USER_RESULT(writeData
															  ,iter->second->user_id
															  ,iter->second->user_name
															  ,iter->second->age
															  ,iter->second->sex
															  ,iter->second->address));
	
	// 해당 데이터가 존재하지 않을 경우
	}else{
		USER user;
		memset(&user, 0, sizeof(USER));

		connectedSession->writePacket(PT_SEL_USER_RESULT
									 ,writeData
									 ,WRITE_PT_SEL_USER_RESULT(writeData
															  ,user.user_id
															  ,user.user_name
															  ,user.age
															  ,user.sex
															  ,user.address));
	}
}

VOID ServerIOCP::PROC_PT_INS_COMPUTER(ConnectedSession* connectedSession, DWORD protocol, BYTE* data, DWORD dataLength){
	READ_DATA(PT_INS_COMPUTER);

	COMPUTER* computer = new COMPUTER();
	computer->set(readData.computer_name, readData.ip_address, readData.cpu_type, readData.ram, readData.hdd);

	mComputers.insert(std::make_pair(computer->computer_name, computer));
}

VOID ServerIOCP::PROC_PT_SEL_COMPUTER(ConnectedSession* connectedSession, DWORD protocol, BYTE* data, DWORD dataLength){
	READ_DATA(PT_SEL_COMPUTER);
	BYTE writeData[MAX_BUFFER_LENGTH] = {0, };

	std::map<std::wstring, COMPUTER*>::iterator iter = mComputers.find(readData.computer_name);

	// 해당 데이터가 존재할 경우
	if(iter != mComputers.end()){
		connectedSession->writePacket(PT_SEL_COMPUTER_RESULT
									 ,writeData
									 ,WRITE_PT_SEL_COMPUTER_RESULT(writeData
																  ,iter->second->computer_name
																  ,iter->second->ip_address
																  ,iter->second->cpu_type
																  ,iter->second->ram
																  ,iter->second->hdd));
	
	// 해당 데이터가 존재하지 않을 경우
	}else{
		COMPUTER computer;
		memset(&computer, 0, sizeof(COMPUTER));

		connectedSession->writePacket(PT_SEL_COMPUTER_RESULT
			                         ,writeData
			                         ,WRITE_PT_SEL_COMPUTER_RESULT(writeData
									                              ,computer.computer_name
									                              ,computer.ip_address
									                              ,computer.cpu_type
									                              ,computer.ram
									                              ,computer.hdd));
	}
}

VOID ServerIOCP::PROC_PT_INS_PROGRAM(ConnectedSession* connectedSession, DWORD protocol, BYTE* data, DWORD dataLength){
	READ_DATA(PT_INS_PROGRAM);

	PROGRAM* program = new PROGRAM();
	program->set(readData.program_name, readData.cost, readData.comment);

	mPrograms.insert(std::make_pair(program->program_name, program));
}

VOID ServerIOCP::PROC_PT_SEL_PROGRAM(ConnectedSession* connectedSession, DWORD protocol, BYTE* data, DWORD dataLength){
	READ_DATA(PT_SEL_PROGRAM);
	BYTE writeData[MAX_BUFFER_LENGTH] = {0, };

	std::map<std::wstring, PROGRAM*>::iterator iter = mPrograms.find(readData.program_name);

	// 해당 데이터가 존재할 경우
	if(iter != mPrograms.end()){
		connectedSession->writePacket(PT_SEL_PROGRAM_RESULT
									 ,writeData
									 ,WRITE_PT_SEL_PROGRAM_RESULT(writeData
									                             ,iter->second->program_name
									                             ,iter->second->cost
									                             ,iter->second->comment));
	
	// 해당 데이터가 존재하지 않을 경우
	}else{
		PROGRAM program;
		memset(&program, 0, sizeof(PROGRAM));

		connectedSession->writePacket(PT_SEL_PROGRAM_RESULT
			                         ,writeData
			                         ,WRITE_PT_SEL_PROGRAM_RESULT(writeData
			                                                     ,program.program_name
			                                                     ,program.cost
			                                                     ,program.comment));
	}
}