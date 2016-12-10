#include "stdafx.h"
#include "ProtocolInfo.h"
#include "File.h"
#include "StructureFile.h"

StructureFile::StructureFile(VOID){
}

StructureFile::~StructureFile(VOID){
}

BOOL StructureFile::write(VOID* buffer, DWORD protocolPos){
	PROTOCOL* protocols = reinterpret_cast<PROTOCOL*>(buffer);

	_ftprintf(mFile, _T("#pragma once\n\n"));
	_ftprintf(mFile, _T("#pragma pack(push, 1)\n\n"));

	for(DWORD i = 0; i < protocolPos; i++){
		_ftprintf(mFile, _T("typedef struct _S_%s {\n"), protocols[i].name);

		for(DWORD j = 0; j < protocols[i].paramCount; j++){
			if(protocols[i].params[j].length == 0){
				_ftprintf(mFile, _T("\t%s %s;\n"), protocols[i].params[j].type, protocols[i].params[j].name);
			}else{
				_ftprintf(mFile, _T("\t%s %s[%d];\n"), protocols[i].params[j].type, protocols[i].params[j].name, protocols[i].params[j].length);
			}
		}

		_ftprintf(mFile, _T("} S_%s;\n\n"), protocols[i].name);
	}

	_ftprintf(mFile, _T("#pragma pack(pop)\n\n"));

	return TRUE;
}