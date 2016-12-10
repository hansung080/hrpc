#ifndef __LOWLIB_SMARTPOINTER_H__
#define __LOWLIB_SMARTPOINTER_H__

template <typename T>
class SmartPointer {
private:
	T* mT;

public:
	SmartPointer(VOID){ mT = new T(); }
	~SmartPointer(VOID){ delete mT; }

	T& operator*() const { return *mT; }
	T* operator->() const { return mT; }
};

#endif // __LOWLIB_SMARTPOINTER_H__