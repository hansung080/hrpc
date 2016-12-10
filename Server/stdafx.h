// stdafx.h : 자주 사용하지만 자주 변경되지는 않는 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 들어 있는 포함 파일입니다.
#ifndef __SERVER_STDAFX_H__
#define __SERVER_STDAFX_H__

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "../LowLib/LowLib.h"
#include "ServerDefine.h"
#include "ServerConstant.h"
#include "PT.h"
#include "PT_Structure.h"
#include "PT_ReadData.h"
#include "PT_WriteData.h"
#include "PT_Info.h"
#include "ConnectedSession.h"
#include "ConnectedSessionManager.h"
#include "ServerIOCP.h"

#endif // __SERVER_STDAFX_H__