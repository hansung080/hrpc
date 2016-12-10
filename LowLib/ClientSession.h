#ifndef __LOWLIB_CLIENTSESSION_H__
#define __LOWLIB_CLIENTSESSION_H__

class ClientSession : public EventSelect {
private:
	PacketSession mSession;
	CircularQueue<CLIENT_INFO> mReadPacketQueue;
	BOOL mIsUDP;

public:
	ClientSession(VOID);
	virtual ~ClientSession(VOID);

	BOOL beginTCP(LPSTR remoteAddress, USHORT remotePort);
	BOOL beginUDP(USHORT remotePort);
	BOOL end(VOID);

	BOOL readPacket(DWORD& protocol, BYTE* data, DWORD& dataLength);
	BOOL readFromPacket(LPSTR remoteAddress, USHORT& remotePort, DWORD& protocol, BYTE* data, DWORD& dataLength); // 파라미터 위치 변경

	BOOL writePacket(DWORD protocol, const BYTE* data, DWORD dataLength);
	BOOL writeToPacket(LPCSTR remoteAddress, USHORT remotePort, DWORD protocol, const BYTE* data, DWORD dataLength);

	BOOL getLocalIP(WCHAR* ip);
	USHORT getLocalPort(VOID);

protected:
	virtual VOID onIORead(VOID);
};

#endif // __LOWLIB_CLIENTSESSION_H__