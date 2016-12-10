#ifndef __LOWLIB_LOG_H__
#define __LOWLIB_LOG_H__

class Log {
private:
	Log(VOID){}
	~Log(VOID){}

public:
	static BOOL writeLog(LPTSTR format, ...){
		SYSTEMTIME systemTime;
		TCHAR currentDate[32] = {0, };
		TCHAR currentFileName[MAX_PATH] = {0, };
		FILE* file = NULL;
		TCHAR debugLog[MAX_BUFFER_LENGTH] = {0, };
		va_list ap;
		TCHAR log[MAX_BUFFER_LENGTH] = {0, };

		va_start(ap, format);
		_vstprintf(log, format, ap);
		va_end(ap);

		GetLocalTime(&systemTime);
		_sntprintf(currentDate, 32, _T("%d-%d-%d %d:%d:%d"), systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute, systemTime.wSecond);
		_sntprintf(currentFileName, MAX_PATH, _T("LOG_%d-%d-%d_%d.log"), systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour);

		file = _tfopen(currentFileName, _T("a"));
		if(!file){
			return FALSE;
		}

		_ftprintf(file, _T("[%s] %s\n"), currentDate, log);
		_sntprintf(debugLog, MAX_BUFFER_LENGTH, _T("[%s] %s\n"), currentDate, log);

		fflush(file);
		fclose(file);

		OutputDebugString(debugLog);
		_tprintf(_T("%s"), debugLog);

		return TRUE;
	}

	static BOOL writeLogNoDate(LPTSTR format, ...){
		SYSTEMTIME systemTime;
		TCHAR currentFileName[MAX_PATH] = { 0, };
		FILE* file = NULL;
		TCHAR debugLog[MAX_BUFFER_LENGTH] = { 0, };
		va_list ap;
		TCHAR log[MAX_BUFFER_LENGTH] = { 0, };

		va_start(ap, format);
		_vstprintf(log, format, ap);
		va_end(ap);

		GetLocalTime(&systemTime);
		_sntprintf(currentFileName, MAX_PATH, _T("LOG_%d-%d-%d_%d.log"), systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour);

		file = _tfopen(currentFileName, _T("a"));
		if (!file){
			return FALSE;
		}

		_ftprintf(file, _T("%s\n"), log);
		_sntprintf(debugLog, MAX_BUFFER_LENGTH, _T("%s\n"), log);

		fflush(file);
		fclose(file);

		OutputDebugString(debugLog);
		_tprintf(_T("%s"), debugLog);

		return TRUE;
	}
};

#endif // __LOWLIB_LOG_H__