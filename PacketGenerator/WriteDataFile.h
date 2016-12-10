#ifndef __PACKETGENERATOR_WRITEDATAFILE_H__
#define __PACKETGENERATOR_WRITEDATAFILE_H__

class WriteDataFile : public File {
public:
	WriteDataFile(VOID);
	virtual ~WriteDataFile(VOID);

	virtual BOOL write(VOID* buffer, DWORD protocolPos);
};

#endif // __PACKETGENERATOR_WRITEDATAFILE_H__