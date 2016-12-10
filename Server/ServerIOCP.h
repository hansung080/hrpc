#ifndef __SERVER_SERVERIOCP_H__
#define __SERVER_SERVERIOCP_H__

class ServerIOCP : public IOCP {
private:
	NetworkSession* mListenSession;
	ConnectedSessionManager mConnectedSessionManager;

	HANDLE mKeepThread;
	HANDLE mKeepThreadDestroyEvent;
	
	std::map<std::wstring, USER*> mUsers;
	std::map<std::wstring, COMPUTER*> mComputers;
	std::map<std::wstring, PROGRAM*> mPrograms;

public:
	ServerIOCP(VOID);
	virtual ~ServerIOCP(VOID);

	BOOL begin(VOID);
	BOOL end(VOID);

	VOID keepThreadCallback(VOID);

protected:
	virtual VOID onIORead(VOID* object, DWORD readLength);
	virtual VOID onIOWrote(VOID* object, DWORD wroteLength);
	virtual VOID onIOConnected(VOID* object);
	virtual VOID onIODisconnected(VOID* object);

private:
	VOID PROC_PT_INS_USER(ConnectedSession* connectedSession, DWORD protocol, BYTE* data, DWORD dataLength);
	VOID PROC_PT_SEL_USER(ConnectedSession* connectedSession, DWORD protocol, BYTE* data, DWORD dataLength);
	VOID PROC_PT_INS_COMPUTER(ConnectedSession* connectedSession, DWORD protocol, BYTE* data, DWORD dataLength);
	VOID PROC_PT_SEL_COMPUTER(ConnectedSession* connectedSession, DWORD protocol, BYTE* data, DWORD dataLength);
	VOID PROC_PT_INS_PROGRAM(ConnectedSession* connectedSession, DWORD protocol, BYTE* data, DWORD dataLength);
	VOID PROC_PT_SEL_PROGRAM(ConnectedSession* connectedSession, DWORD protocol, BYTE* data, DWORD dataLength);
};

#endif // __SERVER_SERVERIOCP_H__