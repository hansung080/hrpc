#include "stdafx.h"
#include "ProtocolInfo.h"
#include "File.h"
#include "WriteDataFile.h"

WriteDataFile::WriteDataFile(VOID){
}

WriteDataFile::~WriteDataFile(VOID){
}

BOOL WriteDataFile::write(VOID* buffer, DWORD protocolPos){
	PROTOCOL* protocols = reinterpret_cast<PROTOCOL*>(buffer);

	_ftprintf(mFile, _T("#pragma once\n\n"));

	// First Loop
	for(DWORD i = 0; i < protocolPos; i++){
		_ftprintf(mFile, _T("inline DWORD WRITE_%s(BYTE* buffer, S_%s& param) {\n"), protocols[i].name, protocols[i].name);
		_ftprintf(mFile, _T("\tSmartPointer<Stream> stream;\n"));
		_ftprintf(mFile, _T("\tstream->setBuffer(buffer);\n\n"));

		for(DWORD j = 0; j < protocols[i].paramCount; j++){
			if(_tcscmp(protocols[i].params[j].type, _T("INT")) == 0){
				_ftprintf(mFile, _T("\tstream->writeINT(param.%s);\n"), protocols[i].params[j].name);

			}else if(_tcscmp(protocols[i].params[j].type, _T("DWORD")) == 0){
				_ftprintf(mFile, _T("\tstream->writeDWORD(param.%s);\n"), protocols[i].params[j].name);

			}else if(_tcscmp(protocols[i].params[j].type, _T("DWORD_PTR")) == 0){
				_ftprintf(mFile, _T("\tstream->writeDWORD_PTR(param.%s);\n"), protocols[i].params[j].name);

			}else if(_tcscmp(protocols[i].params[j].type, _T("BYTE")) == 0){
				if(protocols[i].params[j].length == 0){
					_ftprintf(mFile, _T("\tstream->writeBYTE(param.%s);\n"), protocols[i].params[j].name);

				}else{
					_ftprintf(mFile, _T("\tstream->writeBYTEs(param.%s, %d);\n"), protocols[i].params[j].name, protocols[i].params[j].length);
				}

			}else if(_tcscmp(protocols[i].params[j].type, _T("FLOAT")) == 0){
				_ftprintf(mFile, _T("\tstream->writeFLOAT(param.%s);\n"), protocols[i].params[j].name);

			}else if(_tcscmp(protocols[i].params[j].type, _T("INT64")) == 0){
				_ftprintf(mFile, _T("\tstream->writeINT64(param.%s);\n"), protocols[i].params[j].name);

			}else if(_tcscmp(protocols[i].params[j].type, _T("USHORT")) == 0){
				_ftprintf(mFile, _T("\tstream->writeUSHORT(param.%s);\n"), protocols[i].params[j].name);

			}else if(_tcscmp(protocols[i].params[j].type, _T("SHORT")) == 0){
				_ftprintf(mFile, _T("\tstream->writeSHORT(param.%s);\n"), protocols[i].params[j].name);

			}else if(_tcscmp(protocols[i].params[j].type, _T("BOOL")) == 0){
				_ftprintf(mFile, _T("\tstream->writeBOOL(param.%s);\n"), protocols[i].params[j].name);

			}else if(_tcscmp(protocols[i].params[j].type, _T("WCHAR")) == 0){
				if(protocols[i].params[j].length == 0){
					_ftprintf(mFile, _T("\tstream->writeWCHAR(param.%s);\n"), protocols[i].params[j].name);

				}else{
					_ftprintf(mFile, _T("\tstream->writeWCHARs(param.%s, %d);\n"), protocols[i].params[j].name, protocols[i].params[j].length);
				}

			}else{
				_ftprintf(mFile, _T("\tstream->writeBYTEs((BYTE*)param.%s, sizeof(%s) * %d);\n"), protocols[i].params[j].name, protocols[i].params[j].type, protocols[i].params[j].length);
			}
		}

		_ftprintf(mFile, _T("\n\treturn stream->getLength();\n}\n\n"));
	}

	// Second Loop
	for(DWORD i = 0; i < protocolPos; i++){
		_ftprintf(mFile, _T("inline DWORD WRITE_%s(BYTE *buffer"), protocols[i].name);

		for(DWORD j = 0; j < protocols[i].paramCount; j++){
			if(protocols[i].params[j].length > 0){
				_ftprintf(mFile, _T(", %s* %s"), protocols[i].params[j].type, _tcslwr(protocols[i].params[j].name));

			}else{
				_ftprintf(mFile, _T(", %s %s"), protocols[i].params[j].type, _tcslwr(protocols[i].params[j].name));
			}
		}

		_ftprintf(mFile, _T(") {\n"));
		_ftprintf(mFile, _T("\tSmartPointer<Stream> stream;\n"));
		_ftprintf(mFile, _T("\tstream->setBuffer(buffer);\n\n"));

		for(DWORD j = 0; j < protocols[i].paramCount; j++){
			if(_tcscmp(protocols[i].params[j].type, _T("INT")) == 0){
				_ftprintf(mFile, _T("\tstream->writeINT(%s);\n"), _tcslwr(protocols[i].params[j].name));

			}else if(_tcscmp(protocols[i].params[j].type, _T("DWORD")) == 0){
				_ftprintf(mFile, _T("\tstream->writeDWORD(%s);\n"), _tcslwr(protocols[i].params[j].name));

			}else if(_tcscmp(protocols[i].params[j].type, _T("DWORD_PTR")) == 0){
				_ftprintf(mFile, _T("\tstream->writeDWORD_PTR(%s);\n"), _tcslwr(protocols[i].params[j].name));

			}else if(_tcscmp(protocols[i].params[j].type, _T("BYTE")) == 0){
				if (protocols[i].params[j].length == 0){
					_ftprintf(mFile, _T("\tstream->writeBYTE(%s);\n"), _tcslwr(protocols[i].params[j].name));

				}else{
					_ftprintf(mFile, _T("\tstream->writeBYTEs(%s, %d);\n"), _tcslwr(protocols[i].params[j].name), protocols[i].params[j].length);
				}

			}else if(_tcscmp(protocols[i].params[j].type, _T("FLOAT")) == 0){
				_ftprintf(mFile, _T("\tstream->writeFLOAT(%s);\n"), _tcslwr(protocols[i].params[j].name));

			}else if(_tcscmp(protocols[i].params[j].type, _T("INT64")) == 0){
				_ftprintf(mFile, _T("\tstream->writeINT64(%s);\n"), _tcslwr(protocols[i].params[j].name));

			}else if(_tcscmp(protocols[i].params[j].type, _T("USHORT")) == 0){
				_ftprintf(mFile, _T("\tstream->writeUSHORT(%s);\n"), _tcslwr(protocols[i].params[j].name));

			}else if(_tcscmp(protocols[i].params[j].type, _T("SHORT")) == 0){
				_ftprintf(mFile, _T("\tstream->writeSHORT(%s);\n"), _tcslwr(protocols[i].params[j].name));

			}else if(_tcscmp(protocols[i].params[j].type, _T("BOOL")) == 0){
				_ftprintf(mFile, _T("\tstream->writeBOOL(%s);\n"), _tcslwr(protocols[i].params[j].name));

			}else if(_tcscmp(protocols[i].params[j].type, _T("WCHAR")) == 0){
				if (protocols[i].params[j].length == 0){
					_ftprintf(mFile, _T("\tstream->writeWCHAR(%s);\n"), _tcslwr(protocols[i].params[j].name));

				}else{
					_ftprintf(mFile, _T("\tWCHAR _%s[%d] = {0, };\n"), _tcslwr(protocols[i].params[j].name), protocols[i].params[j].length);
					_ftprintf(mFile, _T("\t_tcsncpy(_%s, %s, %d);\n"), _tcslwr(protocols[i].params[j].name), _tcslwr(protocols[i].params[j].name), protocols[i].params[j].length);
					_ftprintf(mFile, _T("\tstream->writeWCHARs(_%s, %d);\n"), _tcslwr(protocols[i].params[j].name), protocols[i].params[j].length);
				}

			}else{
				_ftprintf(mFile, _T("\tstream->writeBYTEs((BYTE*)%s, sizeof(%s) * %d);\n"), _tcslwr(protocols[i].params[j].name), protocols[i].params[j].type, protocols[i].params[j].length);
			}
		}

		_ftprintf(mFile, _T("\n\treturn stream->getLength();\n}\n\n"));
	}

	return TRUE;
}