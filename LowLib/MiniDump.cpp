#include "stdafx.h"
#include "MiniDump.h"

typedef BOOL(WINAPI *MINIDUMPWRITEDUMP)(HANDLE process
									   ,DWORD pid
									   ,HANDLE file
									   ,MINIDUMP_TYPE dumpType
									   ,CONST PMINIDUMP_EXCEPTION_INFORMATION exceptionParam
									   ,CONST PMINIDUMP_USER_STREAM_INFORMATION userStreamParam
									   ,CONST PMINIDUMP_CALLBACK_INFORMATION callbackParam);

LPTOP_LEVEL_EXCEPTION_FILTER previousExceptionFilter = NULL;

LONG WINAPI unhandledExceptionFilter(struct _EXCEPTION_POINTERS* exceptionInfo){
	HMODULE dllHandle = NULL;

	dllHandle = LoadLibrary(_T("dbghelp.dll"));
	if(dllHandle){
		MINIDUMPWRITEDUMP dump = (MINIDUMPWRITEDUMP)GetProcAddress(dllHandle, "MiniDumpWriteDump");
		if(dump){
			TCHAR dumpPath[MAX_PATH] = {0, };
			SYSTEMTIME systemTime;

			GetLocalTime(&systemTime);
			_sntprintf(dumpPath, MAX_PATH, _T("%d-%d-%d_%d_%d_%d.dmp"), systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute, systemTime.wSecond);

			HANDLE fileHandle = CreateFile(dumpPath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if(fileHandle != INVALID_HANDLE_VALUE){
				_MINIDUMP_EXCEPTION_INFORMATION miniDumpExceptionInfo;

				miniDumpExceptionInfo.ThreadId = GetCurrentThreadId();
				miniDumpExceptionInfo.ExceptionPointers = exceptionInfo;
				miniDumpExceptionInfo.ClientPointers = NULL;

				// dump is MiniDumpWriteDump in dbghelp.dll
				BOOL success = dump(GetCurrentProcess()
								   ,GetCurrentProcessId()
								   ,fileHandle
								   ,MiniDumpNormal
								   ,&miniDumpExceptionInfo
								   ,NULL
								   ,NULL);
				if(success){
					CloseHandle(fileHandle);
					return EXCEPTION_EXECUTE_HANDLER;
				}
			}

			CloseHandle(fileHandle);
		}
	}

	return EXCEPTION_CONTINUE_SEARCH;
}

BOOL MiniDump::begin(VOID){
	SetErrorMode(SEM_FAILCRITICALERRORS);

	previousExceptionFilter = SetUnhandledExceptionFilter(unhandledExceptionFilter);

	return TRUE;
}

BOOL MiniDump::end(VOID){
	SetUnhandledExceptionFilter(previousExceptionFilter);

	return TRUE;
}
