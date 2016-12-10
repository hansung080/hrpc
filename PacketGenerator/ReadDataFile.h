#ifndef __PACKETGENERATOR_READDATAFILE_H__
#define __PACKETGENERATOR_READDATAFILE_H__

class ReadDataFile : public File {
public:
	ReadDataFile(VOID);
	virtual ~ReadDataFile(VOID);

	virtual BOOL write(VOID* buffer, DWORD protocolPos);
};

#endif // __PACKETGENERATOR_READDATAFILE_H__