#ifndef __LOWLIB_EVENTSELECT_H__
#define __LOWLIB_EVENTSELECT_H__

class EventSelect {
private:
	HANDLE mSelectEventHandle;
	HANDLE mSelectThreadHandle;
	HANDLE mStartUpEventHandle;
	HANDLE mDestroyEventHandle;

	SOCKET mSocket;

public:
	EventSelect(VOID);
	virtual ~EventSelect(VOID);

	BOOL begin(SOCKET socket);
	BOOL end(VOID);
	
	VOID selectThreadCallback(VOID);

protected:
	virtual VOID onIORead(VOID) = 0;
	virtual VOID onIOWrote(VOID) = 0;
	virtual VOID onIOConnected(VOID) = 0;
	virtual VOID onIODisconnected(VOID) = 0;
};

#endif // __LOWLIB_EVENTSELECT_H__