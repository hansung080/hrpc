#ifndef __PERFORMANCEPROVIDER_PERFORMANCEINFO_H__
#define __PERFORMANCEPROVIDER_PERFORMANCEINFO_H__

// [참고] Not Defined Error가 발생하여 내가 직접 정의 
#define PERF_DETAIL_NOVICE 100
#define PERF_NO_INSTANCES -1
#define PERF_COUNTER_RAWCOUNT 65536

#pragma pack(push, 1)

// [참고] Not Defined Error가 발생하여 내가 직접 정의 
typedef struct _PERF_COUNTER_DEFINITION {
	DWORD ByteLength;
	DWORD CounterNameTitleIndex;
	LPWSTR CounterNameTitle;
	DWORD CounterHelpTitleIndex;
	LPWSTR CounterHelpTitle;
	LONG DefaultScale;
	DWORD DetailLevel;
	DWORD CounterType;
	DWORD CounterSize;
	DWORD CounterOffset;
} PERF_COUNTER_DEFINITION;

// [참고] Not Defined Error가 발생하여 내가 직접 정의 
typedef struct _PERF_OBJECT_TYPE {
	DWORD TotalByteLength;
	DWORD DefinitionLength;
	DWORD HeaderLength;
	DWORD ObjectNameTitleIndex;
	LPWSTR ObjectNameTitle;
	DWORD ObjectHelpTitleIndex;
	LPWSTR ObjectHelpTitle;
	DWORD DetailLevel;
	DWORD NumCounters;
	DWORD DefaultCounter;
	DWORD NumInstances;
	DWORD CodePage;
	LARGE_INTEGER PerfTime;
	LARGE_INTEGER PerfFreq;
} PERF_OBJECT_TYPE;

typedef struct _PERFORMANCE_COUNTER {
	DWORD Index;
	TCHAR Name[32];
	DWORD Value;
	PERF_COUNTER_DEFINITION Data;
} PERFORMANCE_COUNTER;

#pragma pack(pop)

#endif // __PERFORMANCEPROVIDER_PERFORMANCEINFO_H__