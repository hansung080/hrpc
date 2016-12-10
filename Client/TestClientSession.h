#ifndef __CLIENT_TESTCLIENTSESSION_H__
#define __CLIENT_TESTCLIENTSESSION_H__

class TestClientSession : public ClientSession {
public:
	TestClientSession(VOID);
	virtual ~TestClientSession(VOID);

protected:
	virtual VOID onIOWrote(VOID);
	virtual VOID onIOConnected(VOID);
	virtual VOID onIODisconnected(VOID);
};

#endif // __CLIENT_TESTCLIENTSESSION_H__