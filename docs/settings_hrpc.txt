<< ServerSolution 솔루션 생성 방법 >>

@ 새 솔루션 추가
  1. 새 프로젝트 -> Visual C++ -> 일반 -> 빈 프로젝트
     이름(N) : ServerSolution
     위치(L) : C:\work\ws\visstu\
     솔루션 이름(M) : ServerSolution

  2. 솔루션 추가후, ServerSolution 프로젝트 제거

@ 프로젝트 추가 순서
  1. ServerSolution
  2. LowLib
  3. TestServer
  4. PacketGenerator
  5. PerformanceProvider
  6. Server
  7. Client

<< [참조] 라이브러리 추가 방법 >>

@ 라이브러리 추가
  1. 프로젝트 속성 -> 구성 속성 -> C/C++ -> 일반
     추가 포함 디렉토리 : *.h 경로

  2. 프로젝트 속성 -> 구성 속성 -> 링커 -> 일반
     추가 라이브러리 디렉토리 : *.lib 경로

  3. 프로젝트 속성 -> 구성 속성 -> 링커 -> 입력 (또는, #pragma comment(lib, "*.lib") 를 소스에 직접 입력)
     추가 종속성 : *.lib 파일명

  4. 프로젝트 속성 -> 구성 속성 -> 디버깅
     작업 디렉토리 : *.dll 경로 (단, *.dll 경로와 *.exe 경로가 같은 경우 입력 불필요)
