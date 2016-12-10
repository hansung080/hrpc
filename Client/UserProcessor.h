#ifndef __CLIENT_USERPROCESSOR_H__
#define __CLIENT_USERPROCESSOR_H__

class UserProcessor : public Processor {
public:
	UserProcessor(ClientSession* clientSession);
	virtual ~UserProcessor(VOID);

	virtual VOID insert(VOID);
	virtual VOID select(VOID);
};

#endif // __CLIENT_USERPROCESSOR_H__