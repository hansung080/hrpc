#ifndef __LOWLIB_AUTODETECTMEMORYLEAK_H__
#define __LOWLIB_AUTODETECTMEMORYLEAK_H__

#if defined(_MSC_VER) && defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC // 메모리 누수 탐지를 위해서 선언해 주어야 한다.
#include <crtdbg.h>
#ifndef _CONSOLE
#include <cstdlib> // 콘솔 프로그램이 아닐 경우, 선언해 주어야 한다.
#endif // _CONSOLE

class _AutoDetectMemoryLeak {
public:
	_AutoDetectMemoryLeak(){
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#ifdef _CONSOLE // 콘솔 프로그램일 경우, 모든 Report를 STDOUT으로 보낸다.
		_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
		_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
		_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
		_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
		_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
		_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);

// 컴파일 에러가 발생하여 주석 처리
// 에러 내용 : 오류	2	error C2660: 'MemoryPool<Stream,50>::operator new' : 함수는 4개의 매개 변수를 사용하지 않습니다.	c:\work\ws\visstu\serversolution\lowlib\smartpointer.h	10	1	Server
//#define DEBUG_NORMALBLOCK new ( _NORMAL_BLOCK, __FILE__, __LINE__ )
//#ifdef new
//#undef new
//#endif // new
//#define new DEBUG_NORMALBLOCK

#else // _CONSOLE : 콘솔 프로그램이 아닐 경우, 모든 Report를 DEBUG Window로 보낸다.
		_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
		_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
		_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);

#endif // _CONSOLE

#ifdef malloc
#undef malloc
#endif // malloc
#define malloc(s) (_malloc_dbg( s, _NORMAL_BLOCK, __FILE__, __LINE__ ))
	}
};

// 초기화를 생성자를 통해 자동으로 해주기 위해서 객체를 전역변수로 선언합니다.
static _AutoDetectMemoryLeak _autoDetectMemoryLeak;

#endif // _MSC_VER && _DEBUG
#endif // __LOWLIB_AUTODETECTMEMORYLEAK_H__