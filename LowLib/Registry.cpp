#include "stdafx.h"
#include "Registry.h"

Registry::Registry(VOID){
	mRootKey = NULL;
	mIsOpen = FALSE;
}

Registry::~Registry(VOID){
}

BOOL Registry::open(HKEY rootKey, LPCTSTR subKey){
	if(!subKey){
		return FALSE;
	}

	if(mIsOpen){
		return FALSE;
	}

	if(RegOpenKey(rootKey, subKey, &mRootKey) != ERROR_SUCCESS){
		return FALSE;
	}

	mIsOpen = TRUE;

	return TRUE;
}

BOOL Registry::close(VOID){
	if(RegCloseKey(mRootKey) != ERROR_SUCCESS){
		return FALSE;
	}

	mIsOpen = FALSE;

	return TRUE;
}

BOOL Registry::createKey(HKEY rootKey, LPCTSTR subKey){
	if(!subKey){
		return FALSE;
	}

	if(mIsOpen){
		return FALSE;
	}

	if(RegCreateKey(rootKey, subKey, &mRootKey) != ERROR_SUCCESS){
		return FALSE;
	}

	mIsOpen = TRUE;

	return TRUE;
}

BOOL Registry::deleteKey(HKEY rootKey, LPCTSTR subKey){
	if(!subKey){
		return FALSE;
	}

	if(RegDeleteKey(rootKey, subKey) != ERROR_SUCCESS){
		return FALSE;
	}

	return TRUE;
}

BOOL Registry::setValue(LPCTSTR valueName, LPCTSTR value){
	if(!valueName || !value){
		return FALSE;
	}

	if(!mIsOpen){
		return FALSE;
	}

	if(RegSetValueEx(mRootKey, valueName, 0, REG_SZ, (BYTE*)value, (DWORD)_tcslen(value) * sizeof(TCHAR)) != ERROR_SUCCESS){
		return FALSE;
	}

	return TRUE;
}

BOOL Registry::setValue(LPCTSTR valueName, DWORD value){
	if(!valueName){
		return FALSE;
	}

	if(!mIsOpen){
		return FALSE;
	}

	if(RegSetValueEx(mRootKey, valueName, 0, REG_DWORD, (BYTE*)&value, sizeof(DWORD)) != ERROR_SUCCESS){
		return FALSE;
	}

	return TRUE;
}

BOOL Registry::setValueForMultiSz(LPCTSTR valueName, LPCTSTR value, DWORD byteLength){
	if(!valueName || !value){
		return FALSE;
	}

	if(!mIsOpen){
		return FALSE;
	}

	if(RegSetValueEx(mRootKey, valueName, 0, REG_MULTI_SZ, (BYTE*)value, byteLength) != ERROR_SUCCESS){
		return FALSE;
	}

	return TRUE;
}

BOOL Registry::getValue(LPCTSTR valueName, LPCTSTR value, LPDWORD bufferLength){
	DWORD valueType = 0;

	if(!valueName || !value || !bufferLength){
		return FALSE;
	}

	if(!mIsOpen){
		return FALSE;
	}

	if(RegQueryValueEx(mRootKey, valueName, 0, &valueType, (BYTE*)value, bufferLength) != ERROR_SUCCESS){
		return FALSE;
	}

	return TRUE;
}

BOOL Registry::getValue(LPCTSTR valueName, LPDWORD value){
	DWORD valueType = 0;
	DWORD bufferLength = sizeof(DWORD);

	if(!valueName || !value){
		return FALSE;
	}

	if(!mIsOpen){
		return FALSE;
	}

	if(RegQueryValueEx(mRootKey, valueName, 0, &valueType, (BYTE*)value, &bufferLength) != ERROR_SUCCESS){
		return FALSE;
	}

	return TRUE;
}

BOOL Registry::deleteValue(LPCTSTR valueName){
	if(!valueName){
		return FALSE;
	}

	if(!mIsOpen){
		return FALSE;
	}

	if(RegDeleteValue(mRootKey, valueName) != ERROR_SUCCESS){
		return FALSE;
	}

	return TRUE;
}
