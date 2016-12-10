#ifndef __LOWLIB_NETWORKINFO_H__
#define __LOWLIB_NETWORKINFO_H__

#pragma pack(push, 1)

typedef struct _NETWORK_INFO {
public:
	BYTE data[MAX_BUFFER_LENGTH];
	DWORD dataLength;
	CHAR remoteAddress[IP_ADDRESS_LENGTH];
	USHORT remotePort;

	_NETWORK_INFO(VOID){
		init();
	}

	~_NETWORK_INFO(VOID){
	}

	VOID init(VOID){
		memset(data, 0, sizeof(data));
		dataLength = 0;
		memset(remoteAddress, 0, sizeof(remoteAddress));
		remotePort = 0;
	}

	VOID set(const BYTE* data, DWORD dataLength, LPCSTR remoteAddress, USHORT remotePort){
		memcpy(this->data, data, dataLength);
		this->dataLength = dataLength;
		strncpy(this->remoteAddress, remoteAddress, sizeof(this->remoteAddress));
		this->remotePort = remotePort;
	}

} NETWORK_INFO;

#pragma pack(pop)

#endif // __LOWLIB_NETWORKINFO_H__