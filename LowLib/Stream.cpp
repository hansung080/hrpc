#include "stdafx.h"
#include "CriticalSection.h"
#include "MultiThreadSync.h"
#include "MemoryPool.h"
#include "Stream.h"

Stream::Stream(VOID){
	mBufferPointer = NULL;
	mLength = 0;
}

Stream::~Stream(VOID){
}

BOOL Stream::setBuffer(BYTE* buffer){
	if(!buffer){
		return FALSE;
	}

	mBufferPointer = buffer;
	mLength = 0;

	return TRUE;
}

BOOL Stream::setBuffer(){
	if(!mBufferPointer){
		return FALSE;
	}

	mLength = 0;

	return TRUE;
}

BOOL Stream::readINT(INT* data){
	memcpy(data, mBufferPointer + mLength, sizeof(INT));
	mLength += sizeof(INT);
	return TRUE;
}

BOOL Stream::readDWORD(DWORD* data){
	memcpy(data, mBufferPointer + mLength, sizeof(DWORD));
	mLength += sizeof(DWORD);
	return TRUE;
}

BOOL Stream::readDWORD_PTR(DWORD_PTR* data){
	memcpy(data, mBufferPointer + mLength, sizeof(DWORD_PTR));
	mLength += sizeof(DWORD_PTR);
	return TRUE;
}

BOOL Stream::readBYTE(BYTE* data){
	memcpy(data, mBufferPointer + mLength, sizeof(BYTE));
	mLength += sizeof(BYTE);
	return TRUE;
}

BOOL Stream::readBYTEs(BYTE* data, DWORD length){
	memcpy(data, mBufferPointer + mLength, sizeof(BYTE) * length);
	mLength += (sizeof(BYTE) * length);
	return TRUE;
}

BOOL Stream::readFLOAT(FLOAT* data){
	memcpy(data, mBufferPointer + mLength, sizeof(FLOAT));
	mLength += sizeof(FLOAT);
	return TRUE;
}

BOOL Stream::readINT64(INT64* data){
	memcpy(data, mBufferPointer + mLength, sizeof(INT64));
	mLength += sizeof(INT64);
	return TRUE;
}

BOOL Stream::readUSHORT(USHORT* data){
	memcpy(data, mBufferPointer + mLength, sizeof(USHORT));
	mLength += sizeof(USHORT);
	return TRUE;
}

BOOL Stream::readSHORT(SHORT* data){
	memcpy(data, mBufferPointer + mLength, sizeof(SHORT));
	mLength += sizeof(SHORT);
	return TRUE;
}

BOOL Stream::readBOOL(BOOL* data){
	memcpy(data, mBufferPointer + mLength, sizeof(BOOL));
	mLength += sizeof(BOOL);
	return TRUE;
}

BOOL Stream::readWCHAR(WCHAR* data){
	memcpy(data, mBufferPointer + mLength, sizeof(WCHAR));
	mLength += sizeof(WCHAR);
	return TRUE;
}

BOOL Stream::readWCHARs(WCHAR* data, DWORD length){
	memcpy(data, mBufferPointer + mLength, sizeof(WCHAR) * length);
	mLength += (sizeof(WCHAR) * length);
	return TRUE;
}

BOOL Stream::writeINT(INT data){
	memcpy(mBufferPointer + mLength, &data, sizeof(INT));
	mLength += sizeof(INT);
	return TRUE;
}

BOOL Stream::writeDWORD(DWORD data){
	memcpy(mBufferPointer + mLength, &data, sizeof(DWORD));
	mLength += sizeof(DWORD);
	return TRUE;
}

BOOL Stream::writeDWORD_PTR(DWORD_PTR data){
	memcpy(mBufferPointer + mLength, &data, sizeof(DWORD_PTR));
	mLength += sizeof(DWORD_PTR);
	return TRUE;
}

BOOL Stream::writeBYTE(BYTE data){
	memcpy(mBufferPointer + mLength, &data, sizeof(BYTE));
	mLength += sizeof(BYTE);
	return TRUE;
}

BOOL Stream::writeBYTEs(const BYTE* data, DWORD length){
	memcpy(mBufferPointer + mLength, data, sizeof(BYTE) * length);
	mLength += (sizeof(BYTE) * length);
	return TRUE;
}

BOOL Stream::writeFLOAT(FLOAT data){
	memcpy(mBufferPointer + mLength, &data, sizeof(FLOAT));
	mLength += sizeof(FLOAT);
	return TRUE;
}

BOOL Stream::writeINT64(INT64 data){
	memcpy(mBufferPointer + mLength, &data, sizeof(INT64));
	mLength += sizeof(INT64);
	return TRUE;
}

BOOL Stream::writeUSHORT(USHORT data){
	memcpy(mBufferPointer + mLength, &data, sizeof(USHORT));
	mLength += sizeof(USHORT);
	return TRUE;
}

BOOL Stream::writeSHORT(SHORT data){
	memcpy(mBufferPointer + mLength, &data, sizeof(SHORT));
	mLength += sizeof(SHORT);
	return TRUE;
}

BOOL Stream::writeBOOL(BOOL data){
	memcpy(mBufferPointer + mLength, &data, sizeof(BOOL));
	mLength += sizeof(BOOL);
	return TRUE;
}

BOOL Stream::writeWCHAR(WCHAR data){
	memcpy(mBufferPointer + mLength, &data, sizeof(WCHAR));
	mLength += sizeof(WCHAR);
	return TRUE;
}

BOOL Stream::writeWCHARs(const WCHAR* data, DWORD length){
	memcpy(mBufferPointer + mLength, data, sizeof(WCHAR) + length);
	mLength += (sizeof(WCHAR) * length);
	return TRUE;
}

DWORD Stream::getLength(VOID){
	return mLength;
}
