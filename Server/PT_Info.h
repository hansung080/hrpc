#ifndef __SERVER_PTINFO_H__
#define __SERVER_PTINFO_H__

#pragma pack(push, 1)

typedef struct _USER {
public:
	WCHAR user_id[32];
	WCHAR user_name[32];
	DWORD age;
	BYTE sex;
	WCHAR address[32];

	_USER(VOID){
		init();
	}

	~_USER(VOID){
	}

	VOID init(VOID){
		memset(user_id, 0, sizeof(user_id));
		memset(user_name, 0, sizeof(user_name));
		age = 0;
		sex = 0;
		memset(address, 0, sizeof(address));
	}

	VOID set(const WCHAR* user_id, const WCHAR* user_name, DWORD age, BYTE sex, const WCHAR* address){
		_tcsncpy(this->user_id, user_id, sizeof(this->user_id));
		_tcsncpy(this->user_name, user_name, sizeof(this->user_name));
		this->age = age;
		this->sex = sex;
		_tcsncpy(this->address, address, sizeof(this->address));
	}

} USER;

typedef struct _COMPUTER {
public:
	WCHAR computer_name[32];
	WCHAR ip_address[32];
	BYTE cpu_type;
	DWORD ram;
	DWORD hdd;

	_COMPUTER(VOID){
		init();
	}

	~_COMPUTER(VOID){
	}

	VOID init(VOID){
		memset(computer_name, 0, sizeof(computer_name));
		memset(ip_address, 0, sizeof(ip_address));
		cpu_type = 0;
		ram = 0;
		hdd = 0;
	}

	VOID set(const WCHAR* computer_name, const WCHAR* ip_address, BYTE cpu_type, DWORD ram, DWORD hdd){
		_tcsncpy(this->computer_name, computer_name, sizeof(this->computer_name));
		_tcsncpy(this->ip_address, ip_address, sizeof(this->ip_address));
		this->cpu_type = cpu_type;
		this->ram = ram;
		this->hdd = hdd;
	}

} COMPUTER;

typedef struct _PROGRAM {
public:
	WCHAR program_name[32];
	DWORD cost;
	WCHAR comment[32];

	_PROGRAM(VOID){
		init();
	}

	~_PROGRAM(VOID){
	}

	VOID init(VOID){
		memset(program_name, 0, sizeof(program_name));
		cost = 0;
		memset(comment, 0, sizeof(comment));
	}

	VOID set(const WCHAR* program_name, DWORD cost, const WCHAR* comment){
		_tcsncpy(this->program_name, program_name, sizeof(this->program_name));
		this->cost = cost;
		_tcsncpy(this->comment, comment, sizeof(this->comment));
	}

} PROGRAM;

#pragma pack(pop)

#endif // __SERVER_PTINFO_H__