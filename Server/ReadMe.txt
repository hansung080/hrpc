<< Server 프로젝트 생성 방법 >>

@ 새 프로젝트 추가
  1. 새 프로젝트 추가 -> Visual C++ -> Win32 -> Win32 콘솔 응용 프로그램
     이름(N) : Server
     위치(L) : C:\work\ws\visstu\ServerSolution

  2. Win32 응용 프로그램 마법사 - Server
     응용 프로그램 종류 : 콘솔 응용 프로그램(O)
     추가 옵션 : 미리 컴파일된 헤더(P), SDL(Security Development Lifecycle) 검사(C)
     공용 헤더 파일 추가 대상 : -

<< Server 프로젝트 속성 설정 방법 >>

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

@ 라이브러리 추가
  1. 프로젝트 속성 -> 구성 속성 -> C/C++ -> 일반
     추가 포함 디렉토리 : C:\work\ws\visstu\ServerSolution\LowLib

  2. 프로젝트 속성 -> 구성 속성 -> 링커 -> 일반
     추가 라이브러리 디렉토리 : C:\work\ws\visstu\ServerSolution\Debug

  3. 프로젝트 속성 -> 구성 속성 -> 링커 -> 입력 (또는, #pragma comment(lib, "*.lib") 를 소스에 직접 입력)
     추가 종속성 : ws2_32.lib;Mswsock.lib;LowLib.lib;

  4. 프로젝트 속성 -> 구성 속성 -> 디버깅
     작업 디렉토리 : -