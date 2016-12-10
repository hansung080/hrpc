#ifndef __LOWLIB_MULTITHREADSYNC_H__
#define __LOWLIB_MULTITHREADSYNC_H__

template <typename T>
class MultiThreadSync {
	friend class ThreadSync;

private:
	static CriticalSection mSync;

public:
	MultiThreadSync(VOID){}
	virtual ~MultiThreadSync(VOID){}

	class ThreadSync {
	public:
		ThreadSync(VOID){ T::mSync.enter(); }
		~ThreadSync(VOID){ T::mSync.leave(); }
	};
};

// static 멤버 변수 초기화
// -> MultiThreadSync의 객체를 생성하지 않더라도, CriticalSection의 생성자를 호출할 수 있도록 한다.
template <typename T>
CriticalSection MultiThreadSync<T>::mSync;

#endif // __LOWLIB_MULTITHREADSYNC_H__