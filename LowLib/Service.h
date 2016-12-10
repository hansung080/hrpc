#ifndef __LOWLIB_SERVICE_H__
#define __LOWLIB_SERVICE_H__

class Service {
private:
	SERVICE_STATUS mServiceStatus;
	SERVICE_STATUS_HANDLE mServiceStatusHandle;
	TCHAR mServiceName[MAX_PATH];

protected:
	virtual VOID onStarted(VOID) = 0;
	virtual VOID onStopped(VOID) = 0;

public:
	Service(VOID);
	virtual ~Service(VOID);

	BOOL install(LPCTSTR serviceName);
	BOOL uninstall(LPCTSTR serviceName);

	BOOL begin(LPTSTR serviceName);
	BOOL end(VOID);

	VOID runCallback(DWORD argc, LPTSTR* argv);
	VOID ctrlHandlerCallback(DWORD opCode);
};

#endif // __LOWLIB_SERVICE_H__