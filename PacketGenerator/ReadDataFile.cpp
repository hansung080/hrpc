#include "stdafx.h"
#include "ProtocolInfo.h"
#include "File.h"
#include "ReadDataFile.h"

ReadDataFile::ReadDataFile(VOID){
}

ReadDataFile::~ReadDataFile(VOID){
}

BOOL ReadDataFile::write(VOID* buffer, DWORD protocolPos){
	PROTOCOL* protocols = reinterpret_cast<PROTOCOL*>(buffer);

	_ftprintf(mFile, _T("#pragma once\n\n"));

	for(DWORD i = 0; i < protocolPos; i++){
		_ftprintf(mFile, _T("inline VOID READ_%s(BYTE* buffer, S_%s& param) {\n"), protocols[i].name, protocols[i].name);
		_ftprintf(mFile, _T("\tSmartPointer<Stream> stream;\n"));
		_ftprintf(mFile, _T("\tstream->setBuffer(buffer);\n\n"));

		for(DWORD j = 0; j < protocols[i].paramCount; j++){
			if(_tcscmp(protocols[i].params[j].type, _T("INT")) == 0){
				_ftprintf(mFile, _T("\tstream->readINT(&param.%s);\n"), protocols[i].params[j].name);

			}else if(_tcscmp(protocols[i].params[j].type, _T("DWORD")) == 0){
				_ftprintf(mFile, _T("\tstream->readDWORD(&param.%s);\n"), protocols[i].params[j].name);

			}else if(_tcscmp(protocols[i].params[j].type, _T("DWORD_PTR")) == 0){
				_ftprintf(mFile, _T("\tstream->readDWORD_PTR(&param.%s);\n"), protocols[i].params[j].name);

			}else if(_tcscmp(protocols[i].params[j].type, _T("BYTE")) == 0){
				if(protocols[i].params[j].length == 0){
					_ftprintf(mFile, _T("\tstream->readBYTE(&param.%s);\n"), protocols[i].params[j].name);

				}else{
					_ftprintf(mFile, _T("\tstream->readBYTEs(param.%s, %d);\n"), protocols[i].params[j].name, protocols[i].params[j].length);
				}

			}else if(_tcscmp(protocols[i].params[j].type, _T("FLOAT")) == 0){
				_ftprintf(mFile, _T("\tstream->readFLOAT(&param.%s);\n"), protocols[i].params[j].name);

			}else if(_tcscmp(protocols[i].params[j].type, _T("INT64")) == 0){
				_ftprintf(mFile, _T("\tstream->readINT64(&param.%s);\n"), protocols[i].params[j].name);

			}else if(_tcscmp(protocols[i].params[j].type, _T("USHORT")) == 0){
				_ftprintf(mFile, _T("\tstream->readUSHORT(&param.%s);\n"), protocols[i].params[j].name);

			}else if(_tcscmp(protocols[i].params[j].type, _T("SHORT")) == 0){
				_ftprintf(mFile, _T("\tstream->readSHORT(&param.%s);\n"), protocols[i].params[j].name);

			}else if(_tcscmp(protocols[i].params[j].type, _T("BOOL")) == 0){
				_ftprintf(mFile, _T("\tstream->readBOOL(&param.%s);\n"), protocols[i].params[j].name);

			}else if(_tcscmp(protocols[i].params[j].type, _T("WCHAR")) == 0){
				if(protocols[i].params[j].length == 0){
					_ftprintf(mFile, _T("\tstream->readWCHAR(&param.%s);\n"), protocols[i].params[j].name);

				}else{
					_ftprintf(mFile, _T("\tstream->readWCHARs(param.%s, %d);\n"), protocols[i].params[j].name, protocols[i].params[j].length);
				}

			}else{
				_ftprintf(mFile, _T("\tstream->readBYTEs((BYTE*)param.%s, sizeof(%s) * %d);\n"), protocols[i].params[j].name, protocols[i].params[j].type, protocols[i].params[j].length);
			}
		}

		_ftprintf(mFile, _T("}\n\n"));
	}

	return TRUE;
}