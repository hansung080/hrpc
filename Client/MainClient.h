#ifndef __CLIENT_MAINCLIENT_H__
#define __CLIENT_MAINCLIENT_H__

class MainClient {
private:
	ClientSession* clientSession;

	UserProcessor* userProcessor;
	ComputerProcessor* computerProcessor;
	ProgramProcessor* programProcessor;

public:
	MainClient(ClientSession* clientSession);
	~MainClient(VOID);

	VOID start(VOID);

private:
	BOOL begin(VOID);
	BOOL end(VOID);
};

#endif // __CLIENT_MAINCLIENT_H__