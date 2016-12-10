#ifndef __LOWLIB_CLIENTINFO_H__
#define __LOWLIB_CLIENTINFO_H__

#pragma pack(push, 1)

typedef struct _CLIENT_INFO {
public:
	DWORD protocol;
	BYTE data[MAX_BUFFER_LENGTH];
	DWORD dataLength;
	CHAR remoteAddress[IP_ADDRESS_LENGTH];
	USHORT remotePort;

	_CLIENT_INFO(VOID){
		init();
	}

	~_CLIENT_INFO(VOID){
	}

	VOID init(VOID){
		protocol = 0;
		memset(data, 0, sizeof(data));
		dataLength = 0;
		memset(remoteAddress, 0, sizeof(remoteAddress));
		remotePort = 0;
	}

	VOID set(DWORD protocol, const BYTE* data, DWORD dataLength){
		this->protocol = protocol;
		memcpy(this->data, data, dataLength);
		this->dataLength = dataLength;
		memset(this->remoteAddress, 0, sizeof(this->remoteAddress));
		this->remotePort = 0;
	}

	VOID set(DWORD protocol, const BYTE* data, DWORD dataLength, LPCSTR remoteAddress, USHORT remotePort){
		this->protocol = protocol;
		memcpy(this->data, data, dataLength);
		this->dataLength = dataLength;
		strncpy(this->remoteAddress, remoteAddress, sizeof(this->remoteAddress));
		this->remotePort = remotePort;
	}

	VOID get(DWORD& protocol, BYTE* data, DWORD& dataLength){
		protocol = this->protocol;
		memcpy(data, this->data, this->dataLength);
		dataLength = this->dataLength;
	}

	VOID get(DWORD& protocol, BYTE* data, DWORD& dataLength, LPSTR remoteAddress, USHORT& remotePort){
		protocol = this->protocol;
		memcpy(data, this->data, this->dataLength);
		dataLength = this->dataLength;
		strncpy(remoteAddress, this->remoteAddress, sizeof(this->remoteAddress));
		remotePort = this->remotePort;
	}

} CLIENT_INFO;

#pragma pack(pop)

#endif // __LOWLIB_CLIENTINFO_H__