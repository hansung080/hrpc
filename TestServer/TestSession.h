#ifndef __TESTSERVER_TESTSESSION_H__
#define __TESTSERVER_TESTSESSION_H__

class TestSession : public PacketSession {
public:
	TestSession(VOID);
	virtual ~TestSession(VOID);

	BOOL initialize(SOCKET listenSocket);
	BOOL procIOConnected(VOID);
	BOOL procIODisconnected(SOCKET listenSocket);
};

#endif // __TESTSERVER_TESTSESSION_H__