#include "stdafx.h"
#include "Service.h"

Service* gSelf = NULL;

VOID WINAPI runCallback(DWORD argc, LPTSTR* argv){
	gSelf->runCallback(argc, argv);
}

VOID WINAPI ctrlHandlerCallback(DWORD opCode){
	gSelf->ctrlHandlerCallback(opCode);
}

Service::Service(VOID){
	gSelf = this;
	memset(mServiceName, 0, sizeof(mServiceName));
}

Service::~Service(VOID){
}

BOOL Service::install(LPCTSTR serviceName){
	TCHAR serviceFileName[MAX_PATH] = {0, };
	SC_HANDLE serviceControlManager = NULL;
	SC_HANDLE serviceHandle = NULL;

	if(! serviceName){
		return FALSE;
	}

	serviceFileName[0] = '"';
	GetModuleFileName(NULL, serviceFileName + 1, MAX_PATH - 1);
	_tcscat(serviceFileName, _T("\""));

	serviceControlManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if(!serviceControlManager){
		return FALSE;
	}

	serviceHandle = CreateService(serviceControlManager
								 ,serviceName
								 ,serviceName
								 ,SERVICE_ALL_ACCESS
								 ,SERVICE_WIN32_OWN_PROCESS
								 ,SERVICE_DEMAND_START
								 ,SERVICE_ERROR_NORMAL
								 ,serviceFileName
								 ,NULL
								 ,NULL
								 ,NULL
								 ,NULL
								 ,NULL);
	if(!serviceHandle){
		CloseServiceHandle(serviceControlManager);
		return FALSE;
	}

	CloseServiceHandle(serviceHandle);
	CloseServiceHandle(serviceControlManager);

	return TRUE;
}

BOOL Service::uninstall(LPCTSTR serviceName){
	SC_HANDLE serviceControlManager = NULL;
	SC_HANDLE serviceHandle = NULL;

	if(!serviceName){
		return FALSE;
	}

	serviceControlManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if(!serviceControlManager){
		return FALSE;
	}

	serviceHandle = OpenService(serviceControlManager, serviceName, DELETE);
	if(!serviceHandle){
		CloseServiceHandle(serviceControlManager);
		return FALSE;
	}

	if(!DeleteService(serviceHandle)){
		CloseServiceHandle(serviceHandle);
		CloseServiceHandle(serviceControlManager);
		return FALSE;
	}

	CloseServiceHandle(serviceHandle);
	CloseServiceHandle(serviceControlManager);

	return TRUE;
}

BOOL Service::begin(LPTSTR serviceName){
	if(!serviceName){
		return FALSE;
	}

	SERVICE_TABLE_ENTRY dispatchTable[] = {
		 {serviceName, ::runCallback}
		,{NULL, NULL}
	};

	_tcscpy(mServiceName, serviceName);

	onStarted();

	if(!StartServiceCtrlDispatcher(dispatchTable)){
		_tprintf(_T("## Debug Console Mode ##\n"));
		getchar();
	}

	return TRUE;
}

BOOL Service::end(VOID){
	onStopped();
	return TRUE;
}

VOID Service::runCallback(DWORD argc, LPTSTR* argv){
	DWORD status;

	mServiceStatus.dwServiceType             = SERVICE_WIN32;
	mServiceStatus.dwCurrentState            = SERVICE_START_PENDING;
	mServiceStatus.dwControlsAccepted        = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE;
	mServiceStatus.dwWin32ExitCode           = 0;
	mServiceStatus.dwServiceSpecificExitCode = 0;
	mServiceStatus.dwCheckPoint              = 0;
	mServiceStatus.dwWaitHint                = 0;

	mServiceStatusHandle = RegisterServiceCtrlHandler(mServiceName, ::ctrlHandlerCallback);
	if(mServiceStatusHandle == (SERVICE_STATUS_HANDLE)0){
		return;
	}

	status = NO_ERROR;

	mServiceStatus.dwCurrentState = SERVICE_RUNNING;
	mServiceStatus.dwCheckPoint   = 0;
	mServiceStatus.dwWaitHint     = 0;

	if(!SetServiceStatus(mServiceStatusHandle, &mServiceStatus)){
		return;
	}
}

VOID Service::ctrlHandlerCallback(DWORD opCode){
	switch(opCode){
	case SERVICE_CONTROL_PAUSE:
		mServiceStatus.dwCurrentState = SERVICE_PAUSED;
		break;

	case SERVICE_CONTROL_CONTINUE:
		mServiceStatus.dwCurrentState = SERVICE_RUNNING;
		break;

	case SERVICE_CONTROL_STOP:
		mServiceStatus.dwWin32ExitCode = 0;
		mServiceStatus.dwCurrentState  = SERVICE_STOPPED;
		mServiceStatus.dwCheckPoint    = 0;
		mServiceStatus.dwWaitHint      = 0;
		break;

	case SERVICE_CONTROL_INTERROGATE:
		break;
	}

	if(!SetServiceStatus(mServiceStatusHandle, &mServiceStatus)){
		return;
	}
}
