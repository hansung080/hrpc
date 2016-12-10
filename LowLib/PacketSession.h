#ifndef __LOWLIB_PACKETSESSION_H__
#define __LOWLIB_PACKETSESSION_H__

/**
	Packet 구조
	-> Total Size : 4096 bytes
	-> Encryption : packetNumber, protocol, data
	---------------------------------------------------------------------------
	|  DWORD length  |  DWORD packetNumber  |  DWORD protocol  |  BYTE* data  |
	|  4 bytes       |  4 bytes             |  4 bytes         |  4084 bytes  |
	---------------------------------------------------------------------------
*/

class PacketSession : public NetworkSession {
private:
	BYTE mPacketBuffer[MAX_BUFFER_LENGTH * PACKET_BUFFER_SIZE];
	DWORD mRemainLength;
	DWORD mCurrentPacketNumber;
	DWORD mLastReadPacketNumber;
	CircularQueue<PACKET_INFO> mWriteQueue;
	std::vector<READ_PACKET_INFO> mLastReadPacketInfoVectorForUDP;

public:
	PacketSession(VOID);
	virtual ~PacketSession(VOID);

	BOOL begin(VOID);
	BOOL end(VOID);

	// TCP Read/Write
	BOOL readPacketForIOCP(DWORD readLength);
	BOOL readPacketForEventSelect(VOID);
	BOOL parsePacket(DWORD& protocol, BYTE* data, DWORD& dataLength);
	BOOL writePacket(DWORD protocol, const BYTE* data, DWORD dataLength);

	// UDP Read/Write
	BOOL readFromPacketForIOCP(LPSTR remoteAddress, USHORT& remotePort, DWORD readLength);
	BOOL readFromPacketForEventSelect(LPSTR remoteAddress, USHORT& remotePort);
	BOOL parseFromPacket(LPSTR remoteAddress, USHORT remotePort, DWORD& protocol, BYTE* data, DWORD& dataLength);
	BOOL writeToPacket(LPCSTR remoteAddress, USHORT remotePort, DWORD protocol, const BYTE* data, DWORD dataLength);
	BOOL writeComplete(VOID); // TCP/UDP 모두 사용
	BOOL resetUDP(VOID);
};

#endif // __LOWLIB_PACKETSESSION_H__