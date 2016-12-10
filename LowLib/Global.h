#ifndef __LOWLIB_GLOBAL_H__
#define __LOWLIB_GLOBAL_H__

#include <iostream>
#include <tchar.h>

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <MSWSock.h>
#include <Windows.h>
#include <DbgHelp.h>
#include <assert.h>
#include <time.h>

#include <vector>
#include <queue>
#include <list>
#include <map>
#include <string>
#include <utility>

#import "C:\\Program Files\\Common Files\\System\\ado\\msado15.dll" rename("EOF", "EndOfFile") no_namespace

enum IO_TYPE {
	IO_ACCEPT,
	IO_READ,
	IO_WRITE
};

#pragma pack(push, 1)

typedef struct _OVERLAPPED_EX {
	OVERLAPPED overlapped;
	IO_TYPE ioType;
	VOID* object;
} OVERLAPPED_EX;

#pragma pack(pop)

#define MAX_BUFFER_LENGTH 4096
#define IP_ADDRESS_LENGTH 32
#define PACKET_BUFFER_SIZE 3

#ifdef _SERVER_SIDE
#define MAX_QUEUE_LENGTH 50
#else
#define MAX_QUEUE_LENGTH 500
#endif // _SERVER_SIDE

#include "Log.h"

#endif // __LOWLIB_GLOBAL_H__