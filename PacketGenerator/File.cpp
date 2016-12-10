#include "stdafx.h"
#include "File.h"

File::File(VOID){
	mFile = NULL;
}

File::~File(VOID){
}

//****************************************************************************************************
// <<open 함수의 파일 열기 모드(mode)>>
//====================================================================================================
// 파일 열기 모드  | 설명
//====================================================================================================
// "r"      | - 읽기 모드(Read Mode)
//          | - 파일이 존재하지 않는 경우 열기 실패
//----------------------------------------------------------------------------------------------------
// "w"      | - 쓰기 모드(Write Mode)
//          | - 파일이 존재하지 않는 경우 파일을 생성하고, 파일이 존재하는 경우 파일의 내용을 비움
//----------------------------------------------------------------------------------------------------
// "a"      | - 덧붇여 쓰기 모드(Append Mode)
//          | - 파일이 존재하지 않는 경우 파일을 생성하고, 파일이 존재하는 경우 파일 포인터를 파일의 끝으로 이동
//----------------------------------------------------------------------------------------------------
// "r+"     | - 읽기/쓰기 모드(Read and Write Mode)
//          | - 쓰기가 가능하다는 것을 제외하면 "r"모드와 같음
//----------------------------------------------------------------------------------------------------
// "w+"     | - 쓰기/읽기 모드(Write and Read Mode)
//          | - 읽기가 가능하다는 것을 제외하면 "w"모드와 같음
//----------------------------------------------------------------------------------------------------
// "a+"     | - 덧붙여 쓰기/읽기 모드(Append and Read Mode)
//          | - 읽기가 가능하다는 것을 제외하면 "a"모드와 같음
//====================================================================================================
//****************************************************************************************************
BOOL File::open(const TCHAR* fileName, FILE_MODE mode){
	switch(mode){
	case FILE_READ:
		mFile = _tfopen(fileName, _T("r"));
		break;

	case FILE_WRITE:
		mFile = _tfopen(fileName, _T("w"));
		break;

	case FILE_APPEND:
		mFile = _tfopen(fileName, _T("a"));
		break;

	case FILE_READ_PLUS:
		mFile = _tfopen(fileName, _T("r+"));
		break;

	case FILE_WRITE_PLUS:
		mFile = _tfopen(fileName, _T("w+"));
		break;

	case FILE_APPEND_PLUS:
		mFile = _tfopen(fileName, _T("a+"));
		break;

	default:
		return FALSE;
	}

	if(!mFile){
		_ftprintf(stderr, _T("Can't open file <%s>\n"), fileName);
		return FALSE;
	}

	return TRUE;
}

BOOL File::close(VOID){
	fclose(mFile);

	return TRUE;
}

BOOL File::read(VOID* buffer, DWORD& length){
	return TRUE;
}

BOOL File::write(VOID* buffer, DWORD length){
	return TRUE;
}	
