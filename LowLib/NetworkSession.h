#ifndef __LOWLIB_NETWORKSESSION_H__
#define __LOWLIB_NETWORKSESSION_H__

class NetworkSession : public MultiThreadSync<NetworkSession> {
private:
	OVERLAPPED_EX mAcceptOverlapped;
	OVERLAPPED_EX mReadOverlapped;
	OVERLAPPED_EX mWriteOverlapped;
	BYTE mReadBuffer[MAX_BUFFER_LENGTH];
	SOCKADDR_IN mUDPRemoteInfo;

	SOCKET mSocket;

	HANDLE mReliableUDPThreadHandle;
	HANDLE mReliableUDPThreadStartUpEvent;
	HANDLE mReliableUDPThreadDestroyEvent;
	HANDLE mReliableUDPThreadWakeUpEvent;
	HANDLE mReliableUDPWriteCompleteEvent;

	CircularQueue<NETWORK_INFO> mReliableWriteQueue;
	BOOL mIsReliableUDPSending;

public:
	NetworkSession(VOID);
	virtual ~NetworkSession(VOID);

	BOOL begin(VOID);
	BOOL end(VOID);

	// TCP/UDP Ready
	BOOL bindTCP(VOID);
	BOOL bindUDP(USHORT port);
	BOOL listen(USHORT port, INT backLog);
	BOOL accept(SOCKET listenSocket);
	BOOL connet(LPSTR address, USHORT port);

	// TCP Read/Write
	BOOL initReadForIOCP(VOID);
	BOOL readForIOCP(BYTE* data, DWORD dataLength);
	BOOL readForEventSelect(BYTE* data, DWORD& dataLength);
	BOOL write(BYTE* data, DWORD dataLength);

	// UDP Read/Write
	BOOL initReadFromForIOCP(VOID);
	BOOL readFromForIOCP(LPSTR remoteAddress, USHORT& remotePort, BYTE* data, DWORD& dataLength);
	BOOL readFromForEventSelect(LPSTR remoteAddress, USHORT& remotePort, BYTE* data, DWORD& dataLength);
	BOOL writeTo(LPCSTR remoteAddress, USHORT remotePort, BYTE* data, DWORD dataLength);
	BOOL writeTo2(LPCSTR remoteAddress, USHORT remotePort, BYTE* data, DWORD dataLength);

	// ETC
	SOCKET getSocket(VOID);
	BOOL getLocalIP(WCHAR* ip);
	USHORT getLocalPort(VOID);
	BOOL getRemoteAddressAfterAccept(LPTSTR remoteAddress, USHORT& remotePort);
	VOID reliableUDPThreadCallback(VOID);
};

#endif //__LOWLIB_NETWORKSESSION_H__