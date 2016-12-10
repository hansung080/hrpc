#ifndef __SERVER_SERVERCONSTANT_H__
#define __SERVER_SERVERCONSTANT_H__

class ServerConstant {
private:
	ServerConstant(VOID);
	~ServerConstant(VOID);

public:
	static const USHORT DEFAULT_PORT = 9990;

	static const DWORD KEEP_ALIVE_PROTOCOL = 0x3000000;
	static const DWORD KEEP_ALIVE_DATA = 0xFFFF;
	static const DWORD KEEP_ALIVE_INTERVAL = 30000; // 30 seconds
};

#endif // __SERVER_SERVERCONSTANT_H__