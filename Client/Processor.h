#ifndef __CLIENT_PROCESSOR_H__
#define __CLIENT_PROCESSOR_H__

class Processor {
protected:
	ClientSession* clientSession;

public:
	Processor(ClientSession* clientSession);
	virtual ~Processor(VOID);

protected:
	virtual VOID insert(VOID);
	virtual VOID select(VOID);
};

#endif // __CLIENT_PROCESSOR_H__