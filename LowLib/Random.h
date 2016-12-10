#ifndef __LOWLIB_RANDOM_H__
#define __LOWLIB_RANDOM_H__

class Random {
private:
	UINT mSeed;

public:
	Random(VOID);
	~Random(VOID);

	BOOL init(UINT seed);
	INT rand(VOID);
	INT simpleRandom(VOID);
	INT complexRandom(VOID);
};

#endif // __LOWLIB_RANDOM_H__