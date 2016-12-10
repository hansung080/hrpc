#ifndef __CLIENT_COMPUTERPROCESSOR_H__
#define __CLIENT_COMPUTERPROCESSOR_H__

class ComputerProcessor : public Processor {
public:
	ComputerProcessor(ClientSession* clientSession);
	virtual ~ComputerProcessor(VOID);

	virtual VOID insert(VOID);
	virtual VOID select(VOID);
};

#endif // __CLIENT_COMPUTERPROCESSOR_H__