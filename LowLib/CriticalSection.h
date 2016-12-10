#ifndef __LOWLIB_CRITICALSECTION_H__
#define __LOWLIB_CRITICALSECTION_H__

class CriticalSection {
private:
	CRITICAL_SECTION mSync;

public:
	CriticalSection(VOID){ InitializeCriticalSection(&mSync); }
	~CriticalSection(VOID){ DeleteCriticalSection(&mSync); }

	inline VOID enter(VOID){ EnterCriticalSection(&mSync); }
	inline VOID leave(VOID){ LeaveCriticalSection(&mSync); }
};

#endif // __LOWLIB_CRITICALSECTION_H__