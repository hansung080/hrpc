#ifndef __LOWLIB_MINIDUMP_H__
#define __LOWLIB_MINIDUMP_H__

class MiniDump {
private:
	MiniDump(VOID);
	~MiniDump(VOID);

public:
	static BOOL begin(VOID);
	static BOOL end(VOID);
};

#endif // __LOWLIB_MINIDUMP_H__