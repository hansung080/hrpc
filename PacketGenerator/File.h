#ifndef __PACKETGENERATOR_FILE_H__
#define __PACKETGENERATOR_FILE_H__

enum FILE_MODE {
	FILE_READ,
	FILE_WRITE,
	FILE_APPEND,
	FILE_READ_PLUS,
	FILE_WRITE_PLUS,
	FILE_APPEND_PLUS
};

class File {
protected:
	FILE* mFile;

public:
	File(VOID);
	virtual ~File(VOID);

	BOOL open(const TCHAR* fileName, FILE_MODE mode);
	BOOL close(VOID);

protected:
	virtual BOOL read(VOID* buffer, DWORD& length);
	virtual BOOL write(VOID* buffer, DWORD length);
};

#endif // __PACKETGENERATOR_FILE_H__