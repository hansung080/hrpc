#include "stdafx.h"
#include "IniFile.h"

IniFile::IniFile(VOID){
	memset(mFileName, 0, sizeof(mFileName));
}

IniFile::~IniFile(VOID){
}

BOOL IniFile::open(LPCTSTR fileName){
	if(!fileName){
		return FALSE;
	}

	_tcsncpy(mFileName, fileName, MAX_PATH);

	return TRUE;
}

BOOL IniFile::close(VOID){
	return TRUE;
}

BOOL IniFile::setValue(LPCTSTR keyName, LPCTSTR valueName, LPCTSTR value){
	if(!keyName || !valueName || !value){
		return FALSE;
	}

	WritePrivateProfileString(keyName, valueName, value, mFileName);

	return TRUE;
}

BOOL IniFile::setValue(LPCTSTR keyName, LPCTSTR valueName, DWORD value){
	if(!keyName || !valueName){
		return FALSE;
	}

	TCHAR tValue[16] = {0, };
	_itot(value, tValue, 10);

	WritePrivateProfileString(keyName, valueName, tValue, mFileName);

	return TRUE;
}

BOOL IniFile::setValue(LPCTSTR keyName, LPCTSTR valueName, FLOAT value){
	if(!keyName || !valueName){
		return FALSE;
	}

	TCHAR tValue[16] = {0, };
	_stprintf(tValue, _T("%f"), value);

	WritePrivateProfileString(keyName, valueName, tValue, mFileName);
}

BOOL IniFile::getValue(LPCTSTR keyName, LPCTSTR valueName, LPTSTR value, LPDWORD bufferLength){
	if(!keyName || !valueName || !value || !bufferLength){
		return FALSE;
	}

	*bufferLength = GetPrivateProfileString(keyName, valueName, _T(""), value, *bufferLength, mFileName);

	return TRUE;
}

BOOL IniFile::getValue(LPCTSTR keyName, LPCTSTR valueName, LPDWORD value){
	if(!keyName || !valueName || !value){
		return FALSE;
	}

	*value = GetPrivateProfileInt(keyName, valueName, 0, mFileName);

	return TRUE;
}

BOOL IniFile::getValue(LPCTSTR keyName, LPCTSTR valueName, FLOAT* value){
	if(!keyName || !valueName || !value){
		return FALSE;
	}

	TCHAR tValue[16] = { 0, };

	GetPrivateProfileString(keyName, valueName, _T(""), tValue, 16, mFileName);

	*value = (FLOAT)_tstof(tValue);

	return TRUE;
}
