#ifndef __LOWLIB_CONSTANT_H__
#define __LOWLIB_CONSTANT_H__

class Constant {
private:
	Constant(){}
	~Constant(){}

public:
	static const USHORT RESULT_FAIL = 0;

	static const USHORT RELIABLE_UDP_ACK = 9999;

	static const INT RELIABLE_UDP_RETRY_COUNT = 10;

	static const DWORD IOCP_WORKER_THREAD_COUNT_PER_PROCESSOR = 2;
};

#endif // __LOWLIB_CONSTANT_H__
