#ifndef __PACKETGENERATOR_PROTOCOLFILE_H__
#define __PACKETGENERATOR_PROTOCOLFILE_H__

class ProtocolFile : public File {
public:
	ProtocolFile(VOID);
	virtual ~ProtocolFile(VOID);

	virtual BOOL read(VOID* buffer, DWORD& protocolPos);
};

#endif // __PACKETGENERATOR_PROTOCOLFILE_H__