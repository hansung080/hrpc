#ifndef __LOWLIB_REGISTRY_H__
#define __LOWLIB_REGISTRY_H__

class Registry {
private:
	HKEY mRootKey;
	BOOL mIsOpen;

public:
	Registry(VOID);
	~Registry(VOID);

	// rootKey -> HKEY_CLASSES_ROOT, HKEY_CURRENT_CONFIG, HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE, HKEY_USERS
	BOOL open(HKEY rootKey, LPCTSTR subKey);
	BOOL close(VOID);

	BOOL createKey(HKEY rootKey, LPCTSTR subKey);
	BOOL deleteKey(HKEY rootKey, LPCTSTR subKey);

	BOOL setValue(LPCTSTR valueName, LPCTSTR value);
	BOOL setValue(LPCTSTR valueName, DWORD value);
	BOOL setValueForMultiSz(LPCTSTR valueName, LPCTSTR value, DWORD byteLength);

	BOOL getValue(LPCTSTR valueName, LPCTSTR value, LPDWORD bufferLength);
	BOOL getValue(LPCTSTR valueName, LPDWORD value);

	BOOL deleteValue(LPCTSTR valueName);
};

#endif // __LOWLIB_REGISTRY_H__