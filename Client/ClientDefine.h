#ifndef __CLIENT_CLIENTDEFINE_H__
#define __CLIENT_CLIENTDEFINE_H__

#define READ_DATA(PROTOCOL)\
			S_##PROTOCOL readData;\
			READ_##PROTOCOL(data, readData);

#define SERVER_ADDRESS "127.0.0.1"

#endif // __CLIENT_CLIENTDEFINE_H__