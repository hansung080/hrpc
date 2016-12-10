#ifndef __TESTSERVER_TESTIOCP_H__
#define __TESTSERVER_TESTIOCP_H__

class TestIOCP : public IOCP {
private:
	TestSession* mListenSession;             // Server Socket阑 包府 
	TestSession* mTestSessions[MAX_SESSION]; // Client Socket阑 包府

public:
	TestIOCP(VOID);
	virtual ~TestIOCP(VOID);

	BOOL begin(VOID);
	BOOL end(VOID);

protected:
	virtual VOID onIORead(VOID* object, DWORD readLength);
	virtual VOID onIOWrote(VOID* object, DWORD wroteLength);
	virtual VOID onIOConnected(VOID* object);
	virtual VOID onIODisconnected(VOID* object);
};

#endif // __TESTSERVER_TESTIOCP_H__