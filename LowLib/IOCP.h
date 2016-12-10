#ifndef __LOWLIB_IOCP_H__
#define __LOWLIB_IOCP_H__

class IOCP {
private:
	HANDLE mIOCPHandle;
	DWORD mWorkerThreadCount;
	std::vector<HANDLE> mWorkerThreadVector;
	HANDLE mStartUpEventHandle;

public:
	IOCP(VOID);
	virtual ~IOCP(VOID);

	BOOL begin(VOID);
	BOOL end(VOID);

	BOOL registerSocketToIOCP(SOCKET socket, ULONG_PTR completionKey);
	VOID workerThreadCallback(VOID);

protected:
	virtual VOID onIORead(VOID* object, DWORD readLength) = 0;
	virtual VOID onIOWrote(VOID* object, DWORD wroteLength) = 0;
	virtual VOID onIOConnected(VOID* object) = 0;
	virtual VOID onIODisconnected(VOID* object) = 0;
};

#endif // __LOWLIB_IOCP_H__