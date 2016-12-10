#ifndef __SERVER_CONNECTEDSESSION_H__
#define __SERVER_CONNECTEDSESSION_H__

class ConnectedSession : public PacketSession {
private:
	BOOL mConnected;

public:
	ConnectedSession(VOID);
	virtual ~ConnectedSession(VOID);

	BOOL restart(SOCKET listenSocket);
	VOID setConnected(BOOL connected);
	BOOL getConnected(VOID);
};

#endif // __SERVER_CONNECTEDSESSION_H__