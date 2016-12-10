#ifndef __LOWLIB_CIRCULARQUEUE_H__
#define __LOWLIB_CIRCULARQUEUE_H__

template <typename T>
class CircularQueue : public MultiThreadSync<CircularQueue<T>> {
private:
	T mQueue[MAX_QUEUE_LENGTH];
	DWORD mHead;
	DWORD mTail;

public:
	CircularQueue(VOID){
		memset(mQueue, 0, sizeof(mQueue));
		mHead = 0;
		mTail = 0;
	}

	virtual ~CircularQueue(VOID){
	}

	BOOL begin(VOID){
		memset(mQueue, 0, sizeof(mQueue));
		mHead = 0;
		mTail = 0;

		return TRUE;
	}

	BOOL end(VOID){
		return TRUE;
	}

	T* enq(const T& t){
		ThreadSync sync;

		//Log::writeLog(_T("Queue Status : Head=[%d], Tail=[%d]\n"), mHead, mTail);

		DWORD nextTail = (mTail + 1) % MAX_QUEUE_LENGTH;
		if(nextTail == mHead){ // Queue is full.
			return NULL;
		}

		memcpy(&(mQueue[nextTail]), &t, sizeof(T));
		mTail = nextTail;

		return &(mQueue[nextTail]);
	}

	BOOL deq(T& t){
		ThreadSync sync;

		//Log::writeLog(_T("Queue Status : Head=[%d], Tail=[%d]\n"), mHead, mTail);

		if(mHead == mTail){ // Queue is empty.
			return FALSE;
		}
		DWORD nextHead = (mHead + 1) % MAX_QUEUE_LENGTH;

		memcpy(&t, &(mQueue[nextHead]), sizeof(T));
		mHead = nextHead;

		return TRUE;
	}

	BOOL deq(){
		ThreadSync sync;

		//Log::writeLog(_T("Queue Status : Head=[%d], Tail=[%d]\n"), mHead, mTail);

		if(mHead == mTail){ // Queue is empty.
			return FALSE;
		}
		DWORD nextHead = (mHead + 1) % MAX_QUEUE_LENGTH;

		mHead = nextHead;

		return TRUE;
	}

	BOOL isEmpty(VOID){
		ThreadSync sync;

		if(mHead == mTail){ // Queue is empty.
			return TRUE;
		}

		return FALSE;
	}

	BOOL isFull(VOID){
		ThreadSync sync;

		if(mHead == ((mTail + 1) % MAX_QUEUE_LENGTH)){
			return TRUE;
		}

		return FALSE;
	}
};

#endif // __LOWLIB_CIRCULARQUEUE_H__