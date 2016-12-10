#ifndef __LOWLIB_PACKETINFO_H__
#define __LOWLIB_PACKETINFO_H__

#pragma pack(push, 1)

// Max Packet Length : 4096 bytes
typedef struct _PACKET_INFO {
public:
	DWORD length;
	DWORD packetNumber;
	DWORD protocol;
	BYTE data[MAX_BUFFER_LENGTH - sizeof(DWORD)/*length*/ - sizeof(DWORD)/*packetNumber*/ - sizeof(DWORD)/*protocol*/];

	_PACKET_INFO(VOID){
		init();
	}

	~_PACKET_INFO(VOID){
	}

	VOID init(VOID){
		length = 0;
		packetNumber = 0;
		protocol = 0;
		memset(data, 0, sizeof(data));
	}

	VOID set(DWORD length, DWORD packetNumber, DWORD protocol, const BYTE* data){
		this->length = length;
		this->packetNumber = packetNumber;
		this->protocol = protocol;
		memcpy(this->data, data, length - sizeof(DWORD)/*length*/ - sizeof(DWORD)/*packetNumber*/ - sizeof(DWORD)/*protocol*/);
	}

} PACKET_INFO;

typedef struct _READ_PACKET_INFO {
public:
	CHAR remoteAddress[IP_ADDRESS_LENGTH]; // 14 -> 32
	USHORT remotePort;
	DWORD packetNumber;

	_READ_PACKET_INFO(VOID){
		init();
	}

	~_READ_PACKET_INFO(VOID){
	}

	VOID init(VOID){
		memset(remoteAddress, 0, sizeof(remoteAddress));
		remotePort = 0;
		packetNumber = 0;
	}

	VOID set(LPCSTR remoteAddress, USHORT remotePort, DWORD packetNumber){
		strncpy(this->remoteAddress, remoteAddress, sizeof(this->remoteAddress));
		this->remotePort = remotePort;
		this->packetNumber = packetNumber;
	}

} READ_PACKET_INFO;

#pragma pack(pop)

#endif // __LOWLIB_PACKETINFO_H__