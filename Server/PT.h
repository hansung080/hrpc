#ifndef __SERVER_PT_H__
#define __SERVER_PT_H__

typedef enum _PROTOCOL {
	PT_VERSION = 0x1000000,

	PT_INS_USER,
	/*
		WCHAR : user_id[32]
		WCHAR : user_name[32]
		DWORD : age
		BYTE  : sex
		WCHAR : address[32]
	*/

	PT_SEL_USER,
	/*
		WCHAR : user_id[32]
	*/

	PT_SEL_USER_RESULT,
	/*
		WCHAR : user_id[32]
		WCHAR : user_name[32]
		DWORD : age
		BYTE  : sex
		WCHAR : address[32]
	*/

	PT_INS_COMPUTER,
	/*
		WCHAR : computer_name[32]
		WCHAR : ip_address[32]
		BYTE  : cpu_type
		DWORD : ram
		DWORD : hdd
	*/

	PT_SEL_COMPUTER,
	/*
		WCHAR : computer_name[32]
	*/

	PT_SEL_COMPUTER_RESULT,
	/*
		WCHAR : computer_name[32]
		WCHAR : ip_address[32]
		BYTE  : cpu_type
		DWORD : ram
		DWORD : hdd
	*/

	PT_INS_PROGRAM,
	/*
		WCHAR : program_name[32]
		DWORD : cost
		WCHAR : comment[32]
	*/

	PT_SEL_PROGRAM,
	/*
		WCHAR : program_name[32]
	*/

	PT_SEL_PROGRAM_RESULT,
	/*
		WCHAR : program_name[32]
		DWORD : cost
		WCHAR : comment[32]
	*/

	PT_END
} PROTOCOL;

#endif // __SERVER_PT_H__