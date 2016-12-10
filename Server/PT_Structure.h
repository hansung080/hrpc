#pragma once

#pragma pack(push, 1)

typedef struct _S_PT_INS_USER {
	WCHAR user_id[32];
	WCHAR user_name[32];
	DWORD age;
	BYTE sex;
	WCHAR address[32];
} S_PT_INS_USER;

typedef struct _S_PT_SEL_USER {
	WCHAR user_id[32];
} S_PT_SEL_USER;

typedef struct _S_PT_SEL_USER_RESULT {
	WCHAR user_id[32];
	WCHAR user_name[32];
	DWORD age;
	BYTE sex;
	WCHAR address[32];
} S_PT_SEL_USER_RESULT;

typedef struct _S_PT_INS_COMPUTER {
	WCHAR computer_name[32];
	WCHAR ip_address[32];
	BYTE cpu_type;
	DWORD ram;
	DWORD hdd;
} S_PT_INS_COMPUTER;

typedef struct _S_PT_SEL_COMPUTER {
	WCHAR computer_name[32];
} S_PT_SEL_COMPUTER;

typedef struct _S_PT_SEL_COMPUTER_RESULT {
	WCHAR computer_name[32];
	WCHAR ip_address[32];
	BYTE cpu_type;
	DWORD ram;
	DWORD hdd;
} S_PT_SEL_COMPUTER_RESULT;

typedef struct _S_PT_INS_PROGRAM {
	WCHAR program_name[32];
	DWORD cost;
	WCHAR comment[32];
} S_PT_INS_PROGRAM;

typedef struct _S_PT_SEL_PROGRAM {
	WCHAR program_name[32];
} S_PT_SEL_PROGRAM;

typedef struct _S_PT_SEL_PROGRAM_RESULT {
	WCHAR program_name[32];
	DWORD cost;
	WCHAR comment[32];
} S_PT_SEL_PROGRAM_RESULT;

#pragma pack(pop)

