#ifndef __SERVER_CONNECTEDSESSIONMANAGER_H__
#define __SERVER_CONNECTEDSESSIONMANAGER_H__

class ConnectedSessionManager : public MultiThreadSync<ConnectedSessionManager> {
private:
	std::vector<ConnectedSession*> mConnectedSessions;

public:
	ConnectedSessionManager(VOID);
	virtual ~ConnectedSessionManager(VOID);

	BOOL begin(SOCKET listenSocket);
	BOOL end(VOID);

	VOID writeAll(DWORD protocol, BYTE* data, DWORD length);
};

#endif // __SERVER_CONNECTEDSESSIONMANAGER_H__