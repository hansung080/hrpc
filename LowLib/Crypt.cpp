#include "stdafx.h"
#include "Crypt.h"

const INT C1  = 52845;
const INT C2  = 22719;
const INT KEY = 72957;

BOOL Crypt::encrypt(BYTE* src, BYTE* dest, DWORD len){
	DWORD i;
	INT key = KEY;

	if(!src || !dest || len <= 0){
		return FALSE;
	}

	for(i = 0; i < len; i++){
		dest[i] = src[i] ^ key >> 8;
		key = (dest[i] + key) * C1 + C2;
	}

	return TRUE;
}

BOOL Crypt::decrypt(BYTE* src, BYTE* dest, DWORD len){
	DWORD i;
	BYTE prevBlock;
	INT key = KEY;

	if(!src || !dest || len <= 0){
		return FALSE;
	}

	for(i = 0; i < len; i++){
		prevBlock = src[i];
		dest[i] = src[i] ^ key >> 8;
		key = (prevBlock + key) * C1 + C2;
	}

	return TRUE;
}