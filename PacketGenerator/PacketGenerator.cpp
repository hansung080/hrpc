// PacketGenerator.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.

#include "stdafx.h"
#include "ProtocolInfo.h"
#include "File.h"
#include "ProtocolFile.h"
#include "StructureFile.h"
#include "ReadDataFile.h"
#include "WriteDataFile.h"

static VOID getFileNames(_TCHAR* argv[]
						,TCHAR* protocolFileName
						,TCHAR* structureFileName
						,TCHAR* readDataFileName
						,TCHAR* writeDataFileName){
	TCHAR inputFileName[MAX_PATH] = {0, };
	TCHAR outputFileNamePrefix[MAX_PATH] = {0, };

	_tcsncpy(inputFileName, argv[1], _tcslen(argv[1]));
	_tcsncpy(outputFileNamePrefix, argv[2], _tcslen(argv[2]));
	
	if(_tcsstr(inputFileName, _T(".h"))){
		_sntprintf(protocolFileName, MAX_PATH, _T("%s\\%s"), FILE_PATH, inputFileName);
	}else{
		_sntprintf(protocolFileName, MAX_PATH, _T("%s\\%s.h"), FILE_PATH, inputFileName);
	}

	_sntprintf(structureFileName, MAX_PATH, _T("%s\\%s_Structure.h"), FILE_PATH, outputFileNamePrefix);
	_sntprintf(readDataFileName, MAX_PATH, _T("%s\\%s_ReadData.h"), FILE_PATH, outputFileNamePrefix);
	_sntprintf(writeDataFileName, MAX_PATH, _T("%s\\%s_WriteData.h"), FILE_PATH, outputFileNamePrefix);
}

static VOID createObjects(PROTOCOL** protocols
						 ,ProtocolFile** protocolFile
						 ,StructureFile** structureFile
						 ,ReadDataFile** readDataFile
						 ,WriteDataFile** writeDataFile){
	*protocols = new PROTOCOL[MAX_PROTOCOL_COUNT];
	*protocolFile = new ProtocolFile();
	*structureFile = new StructureFile();
	*readDataFile = new ReadDataFile();
	*writeDataFile = new WriteDataFile();

	memset(*protocols, 0, sizeof(PROTOCOL)* MAX_PROTOCOL_COUNT);
}

static VOID destroyObjects(PROTOCOL* protocols
						  ,ProtocolFile* protocolFile
						  ,StructureFile* structureFile
						  ,ReadDataFile* readDataFile
						  ,WriteDataFile* writeDataFile){
	delete[] protocols;
	delete protocolFile;
	delete structureFile;
	delete readDataFile;
	delete writeDataFile;
}

static BOOL openFiles(ProtocolFile* protocolFile
					 ,StructureFile* structureFile
					 ,ReadDataFile* readDataFile
					 ,WriteDataFile* writeDataFile
					 ,const TCHAR* protocolFileName
					 ,const TCHAR* structureFileName
					 ,const TCHAR* readDataFileName
					 ,const TCHAR* writeDataFileName){
	if(!protocolFile->open(protocolFileName, FILE_READ)){
		return FALSE;
	}

	if(!structureFile->open(structureFileName, FILE_WRITE)){
		return FALSE;
	}

	if(!readDataFile->open(readDataFileName, FILE_WRITE)){
		return FALSE;
	}
	
	if(!writeDataFile->open(writeDataFileName, FILE_WRITE)){
		return FALSE;
	}

	return TRUE;
}

static VOID closeFiles(ProtocolFile* protocolFile
					  ,StructureFile* structureFile
			          ,ReadDataFile* readDataFile
					  ,WriteDataFile* writeDataFile){
	protocolFile->close();
	structureFile->close();
	readDataFile->close();
	writeDataFile->close();
}

int _tmain(int argc, _TCHAR* argv[]){
	if(argc != 3){
		_ftprintf(stderr, _T("Usage : PacketGenerator <InputFileName> <OutputFileNamePrefix>\n"));
		return 1;
	}
	
	TCHAR protocolFileName[MAX_PATH] = {0, };
	TCHAR structureFileName[MAX_PATH] = {0, };
	TCHAR readDataFileName[MAX_PATH] = {0, };
	TCHAR writeDataFileName[MAX_PATH] = {0, };
	PROTOCOL* protocols = NULL;
	DWORD protocolPos = 0;
	ProtocolFile* protocolFile = NULL;
	StructureFile* structureFile = NULL;
	ReadDataFile* readDataFile = NULL;
	WriteDataFile* writeDataFile = NULL;

	/* Pre-Process */
	getFileNames(argv
				,protocolFileName
				,structureFileName
				,readDataFileName
				,writeDataFileName);
	
	createObjects(&protocols
				 ,&protocolFile
				 ,&structureFile
				 ,&readDataFile
				 ,&writeDataFile);

	if(!openFiles(protocolFile
				 ,structureFile
				 ,readDataFile
				 ,writeDataFile
				 ,protocolFileName
				 ,structureFileName
				 ,readDataFileName
				 ,writeDataFileName)){
		return 1;
	}

	/* Main-Process */
	protocolFile->read(protocols, protocolPos);
	structureFile->write(protocols, protocolPos);
	readDataFile->write(protocols, protocolPos);
	writeDataFile->write(protocols, protocolPos);
	
	/* Post-Process */
	closeFiles(protocolFile
		      ,structureFile
		      ,readDataFile
		      ,writeDataFile);

	destroyObjects(protocols
				  ,protocolFile
				  ,structureFile
				  ,readDataFile
				  ,writeDataFile);

	return 0;
}
