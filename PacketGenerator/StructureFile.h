#ifndef __PACKETGENERATOR_STRUCTUREFILE_H__
#define __PACKETGENERATOR_STRUCTUREFILE_H__

class StructureFile : public File {
public:
	StructureFile(VOID);
	virtual ~StructureFile(VOID);
	
	virtual BOOL write(VOID* buffer, DWORD protocolPos);
};

#endif // __PACKETGENERATOR_STRUCTUREFILE_H__