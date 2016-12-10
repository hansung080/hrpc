#ifndef __CLIENT_PROGRAMPROCESSOR_H__
#define __CLIENT_PROGRAMPROCESSOR_H__

class ProgramProcessor : public Processor {
public:
	ProgramProcessor(ClientSession* clientSession);
	virtual ~ProgramProcessor(VOID);

	virtual VOID insert(VOID);
	virtual VOID select(VOID);
};

#endif // __CLIENT_PROGRAMPROCESSOR_H__