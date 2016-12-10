#ifndef __LOWLIB_CRYPT_H__
#define __LOWLIB_CRYPT_H__

class Crypt {
private:
	Crypt(VOID){}
	~Crypt(VOID){}

public:
	static BOOL encrypt(BYTE* src, BYTE* dest, DWORD len);
	static BOOL decrypt(BYTE* src, BYTE* dest, DWORD len);
};

#endif // __LOWLIB_CRYPT_H__