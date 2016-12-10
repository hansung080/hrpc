#ifndef __LOWLIB_STREAM_H__
#define __LOWLIB_STREAM_H__

class Stream : public MemoryPool<Stream> {
private:
	BYTE* mBufferPointer;
	DWORD mLength;

public:
	Stream(VOID);
	virtual ~Stream(VOID);

	BOOL setBuffer(BYTE* buffer);
	BOOL setBuffer();

	BOOL readINT(INT* data);
	BOOL readDWORD(DWORD* data);
	BOOL readDWORD_PTR(DWORD_PTR* data);
	BOOL readBYTE(BYTE* data);
	BOOL readBYTEs(BYTE* data, DWORD length);
	BOOL readFLOAT(FLOAT* data);
	BOOL readINT64(INT64* data);
	BOOL readUSHORT(USHORT* data);
	BOOL readSHORT(SHORT* data);
	BOOL readBOOL(BOOL* data);
	BOOL readWCHAR(WCHAR* data);
	BOOL readWCHARs(WCHAR* data, DWORD length);
	
	BOOL writeINT(INT data);
	BOOL writeDWORD(DWORD data);
	BOOL writeDWORD_PTR(DWORD_PTR data);
	BOOL writeBYTE(BYTE data);
	BOOL writeBYTEs(const BYTE* data, DWORD length);
	BOOL writeFLOAT(FLOAT data);
	BOOL writeINT64(INT64 data);
	BOOL writeUSHORT(USHORT data);
	BOOL writeSHORT(SHORT data);
	BOOL writeBOOL(BOOL data);
	BOOL writeWCHAR(WCHAR data);
	BOOL writeWCHARs(const WCHAR* data, DWORD length);

	DWORD getLength(VOID);
};

#endif // __LOWLIB_STREAM_H__