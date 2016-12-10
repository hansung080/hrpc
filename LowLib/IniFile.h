#ifndef __LOWLIB_INIFILE_H__
#define __LOWLIB_INIFILE_H__

class IniFile {
private:
	TCHAR mFileName[MAX_PATH];

public:
	IniFile(VOID);
	~IniFile(VOID);

	BOOL open(LPCTSTR fileName);
	BOOL close(VOID);

	BOOL setValue(LPCTSTR keyName, LPCTSTR valueName, LPCTSTR value);
	BOOL setValue(LPCTSTR keyName, LPCTSTR valueName, DWORD value);
	BOOL setValue(LPCTSTR keyName, LPCTSTR valueName, FLOAT value);

	BOOL getValue(LPCTSTR keyName, LPCTSTR valueName, LPTSTR value, LPDWORD bufferLength);
	BOOL getValue(LPCTSTR keyName, LPCTSTR valueName, LPDWORD value);
	BOOL getValue(LPCTSTR keyName, LPCTSTR valueName, FLOAT* value);
};

#endif // __LOWLIB_INIFILE_H__