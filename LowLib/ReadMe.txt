<< LowLib 프로젝트 생성 방법 >>

@ 새 프로젝트 추가
  1. 새 프로젝트 추가 -> Visual C++ -> Win32 -> Win32 콘솔 응용 프로그램
     이름(N) : LowLib
     위치(L) : C:\work\ws\visstu\ServerSolution

  2. Win32 응용 프로그램 마법사 - LowLib
     응용 프로그램 종류 : 정적 라이브러리(S)
     추가 옵션 : 미리 컴파일된 헤더(P), SDL(Security Development Lifecycle) 검사(C)
     공용 헤더 파일 추가 대상 : -


<< LowLib 프로젝트 속성 설정 방법 >>

@ 유니코드 설정
  1. 프로젝트 속성 -> 구성 속성 -> 일반
     문자 집합 : 유니코드 문자 집합 사용
     
@ 다중 스레드 설정
  2. 프로젝트 속성 -> 구성 속성 -> C/C++ -> 코드 생성
     런타임 라이브러리 : 다중 스레드 디버그 DLL(/MDd)

@ 미리 컴파일된 헤더 설정
  1. 프로젝트 속성 -> 구성 속성 -> C/C++ -> 미리 컴파일된 헤더
     미리 컴파일된 헤더 : 사용(/Yu)
     
  2. stdafx.cpp 속성 -> 구성 속성 -> C/C++ -> 미리 컴파일된 헤더
     미리 컴파일된 헤더 : 만들기(/Yc)

@ 전처리기 정의 추가
  1. 프로젝트 속성 -> 구성 속성 -> C/C++ -> 전처리기
     전처리기 정의 : 
     _CRT_SECURE_NO_WARNINGS
     _CRT_NON_CONFORMING_SWPRINTFS

@ 라이브러리 추가 (선택사항)
  1. 솔루션에 새 폴더 추가후, 헤더 및 라이브러리를 추가함.
     <원래 위치>
     C:\Program Files (x86)\Windows Kits\8.1\Include\um\DbgHelp.h
     C:\Windows\System32\dbghelp.dll
     <솔루션내 위치>
     $(SolutionDir)libs\dbghelp\include\DbgHelp.h
     $(SolutionDir)libs\dbghelp\lib\dbghelp.dll

  2. 프로젝트 속성은 일단 변경 안 함.
