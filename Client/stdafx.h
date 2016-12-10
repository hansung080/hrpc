// stdafx.h : 자주 사용하지만 자주 변경되지는 않는 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 들어 있는 포함 파일입니다.
#ifndef __CLIENT_STDAFX_H__
#define __CLIENT_STDAFX_H__

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "../LowLib/LowLib.h"
#include "../Server/PT.h"
#include "../Server/PT_Structure.h"
#include "../Server/PT_ReadData.h"
#include "../Server/PT_WriteData.h"
#include "ClientConstant.h"
#include "ClientDefine.h"
#include "Processor.h"
#include "UserProcessor.h"
#include "ComputerProcessor.h"
#include "ProgramProcessor.h"

#endif // __CLIENT_STDAFX_H__
