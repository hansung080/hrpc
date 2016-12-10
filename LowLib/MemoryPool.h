#ifndef __LOWLIB_MEMORYPOOL_H__
#define __LOWLIB_MEMORYPOOL_H__

template <typename T, int ALLOC_BLOCK_SIZE = 50>
class MemoryPool : public MultiThreadSync<T> {
private:
	static UCHAR* mFreePointer; // the pointer of free block

public:
	MemoryPool(VOID){}
	virtual ~MemoryPool(VOID){}

	static VOID* operator new(std::size_t allocLength){
		ThreadSync sync;

		if(sizeof(T) != allocLength || sizeof(T) < sizeof(UCHAR*)){
			return NULL;
		}

		if(!mFreePointer){
			allocBlocks();
		}

		UCHAR* returnPointer = mFreePointer;
		mFreePointer = *reinterpret_cast<UCHAR**>(returnPointer);

		return returnPointer;
	}

	static VOID operator delete(VOID* deletePointer){
		ThreadSync sync;

		*reinterpret_cast<UCHAR**>(deletePointer) = mFreePointer;
		mFreePointer = reinterpret_cast<UCHAR*>(deletePointer);
	}

private:
	/**
      블록 구조 (5블록 할당한 경우)

	   0x100       0x200       0x300       0x400       0x500
	  -------------------------------------------------------------
	  |0x200:     |0x300:     |0x400:     |0x500:     |NULL :     |
	  -------------------------------------------------------------
	*/
	static VOID allocBlocks(VOID){
		mFreePointer = new UCHAR[sizeof(T) * ALLOC_BLOCK_SIZE];

		UCHAR** current = reinterpret_cast<UCHAR**>(mFreePointer);
		UCHAR* next = mFreePointer;

		for(INT i = 0; i < ALLOC_BLOCK_SIZE - 1; i++){
			next += sizeof(T);
			*current = next;
			current = reinterpret_cast<UCHAR**>(next);
		}

		*current = NULL;
	}
};

template <typename T, int ALLOC_BLOCK_SIZE>
UCHAR* MemoryPool<T, ALLOC_BLOCK_SIZE>::mFreePointer;

#endif // __LOWLIB_MEMORYPOOL_H__