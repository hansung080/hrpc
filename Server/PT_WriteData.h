#pragma once

inline DWORD WRITE_PT_INS_USER(BYTE* buffer, S_PT_INS_USER& param) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	stream->writeWCHARs(param.user_id, 32);
	stream->writeWCHARs(param.user_name, 32);
	stream->writeDWORD(param.age);
	stream->writeBYTE(param.sex);
	stream->writeWCHARs(param.address, 32);

	return stream->getLength();
}

inline DWORD WRITE_PT_SEL_USER(BYTE* buffer, S_PT_SEL_USER& param) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	stream->writeWCHARs(param.user_id, 32);

	return stream->getLength();
}

inline DWORD WRITE_PT_SEL_USER_RESULT(BYTE* buffer, S_PT_SEL_USER_RESULT& param) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	stream->writeWCHARs(param.user_id, 32);
	stream->writeWCHARs(param.user_name, 32);
	stream->writeDWORD(param.age);
	stream->writeBYTE(param.sex);
	stream->writeWCHARs(param.address, 32);

	return stream->getLength();
}

inline DWORD WRITE_PT_INS_COMPUTER(BYTE* buffer, S_PT_INS_COMPUTER& param) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	stream->writeWCHARs(param.computer_name, 32);
	stream->writeWCHARs(param.ip_address, 32);
	stream->writeBYTE(param.cpu_type);
	stream->writeDWORD(param.ram);
	stream->writeDWORD(param.hdd);

	return stream->getLength();
}

inline DWORD WRITE_PT_SEL_COMPUTER(BYTE* buffer, S_PT_SEL_COMPUTER& param) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	stream->writeWCHARs(param.computer_name, 32);

	return stream->getLength();
}

inline DWORD WRITE_PT_SEL_COMPUTER_RESULT(BYTE* buffer, S_PT_SEL_COMPUTER_RESULT& param) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	stream->writeWCHARs(param.computer_name, 32);
	stream->writeWCHARs(param.ip_address, 32);
	stream->writeBYTE(param.cpu_type);
	stream->writeDWORD(param.ram);
	stream->writeDWORD(param.hdd);

	return stream->getLength();
}

inline DWORD WRITE_PT_INS_PROGRAM(BYTE* buffer, S_PT_INS_PROGRAM& param) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	stream->writeWCHARs(param.program_name, 32);
	stream->writeDWORD(param.cost);
	stream->writeWCHARs(param.comment, 32);

	return stream->getLength();
}

inline DWORD WRITE_PT_SEL_PROGRAM(BYTE* buffer, S_PT_SEL_PROGRAM& param) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	stream->writeWCHARs(param.program_name, 32);

	return stream->getLength();
}

inline DWORD WRITE_PT_SEL_PROGRAM_RESULT(BYTE* buffer, S_PT_SEL_PROGRAM_RESULT& param) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	stream->writeWCHARs(param.program_name, 32);
	stream->writeDWORD(param.cost);
	stream->writeWCHARs(param.comment, 32);

	return stream->getLength();
}

inline DWORD WRITE_PT_INS_USER(BYTE *buffer, WCHAR* user_id, WCHAR* user_name, DWORD age, BYTE sex, WCHAR* address) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	WCHAR _user_id[32] = {0, };
	_tcsncpy(_user_id, user_id, 32);
	stream->writeWCHARs(_user_id, 32);
	WCHAR _user_name[32] = {0, };
	_tcsncpy(_user_name, user_name, 32);
	stream->writeWCHARs(_user_name, 32);
	stream->writeDWORD(age);
	stream->writeBYTE(sex);
	WCHAR _address[32] = {0, };
	_tcsncpy(_address, address, 32);
	stream->writeWCHARs(_address, 32);

	return stream->getLength();
}

inline DWORD WRITE_PT_SEL_USER(BYTE *buffer, WCHAR* user_id) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	WCHAR _user_id[32] = {0, };
	_tcsncpy(_user_id, user_id, 32);
	stream->writeWCHARs(_user_id, 32);

	return stream->getLength();
}

inline DWORD WRITE_PT_SEL_USER_RESULT(BYTE *buffer, WCHAR* user_id, WCHAR* user_name, DWORD age, BYTE sex, WCHAR* address) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	WCHAR _user_id[32] = {0, };
	_tcsncpy(_user_id, user_id, 32);
	stream->writeWCHARs(_user_id, 32);
	WCHAR _user_name[32] = {0, };
	_tcsncpy(_user_name, user_name, 32);
	stream->writeWCHARs(_user_name, 32);
	stream->writeDWORD(age);
	stream->writeBYTE(sex);
	WCHAR _address[32] = {0, };
	_tcsncpy(_address, address, 32);
	stream->writeWCHARs(_address, 32);

	return stream->getLength();
}

inline DWORD WRITE_PT_INS_COMPUTER(BYTE *buffer, WCHAR* computer_name, WCHAR* ip_address, BYTE cpu_type, DWORD ram, DWORD hdd) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	WCHAR _computer_name[32] = {0, };
	_tcsncpy(_computer_name, computer_name, 32);
	stream->writeWCHARs(_computer_name, 32);
	WCHAR _ip_address[32] = {0, };
	_tcsncpy(_ip_address, ip_address, 32);
	stream->writeWCHARs(_ip_address, 32);
	stream->writeBYTE(cpu_type);
	stream->writeDWORD(ram);
	stream->writeDWORD(hdd);

	return stream->getLength();
}

inline DWORD WRITE_PT_SEL_COMPUTER(BYTE *buffer, WCHAR* computer_name) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	WCHAR _computer_name[32] = {0, };
	_tcsncpy(_computer_name, computer_name, 32);
	stream->writeWCHARs(_computer_name, 32);

	return stream->getLength();
}

inline DWORD WRITE_PT_SEL_COMPUTER_RESULT(BYTE *buffer, WCHAR* computer_name, WCHAR* ip_address, BYTE cpu_type, DWORD ram, DWORD hdd) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	WCHAR _computer_name[32] = {0, };
	_tcsncpy(_computer_name, computer_name, 32);
	stream->writeWCHARs(_computer_name, 32);
	WCHAR _ip_address[32] = {0, };
	_tcsncpy(_ip_address, ip_address, 32);
	stream->writeWCHARs(_ip_address, 32);
	stream->writeBYTE(cpu_type);
	stream->writeDWORD(ram);
	stream->writeDWORD(hdd);

	return stream->getLength();
}

inline DWORD WRITE_PT_INS_PROGRAM(BYTE *buffer, WCHAR* program_name, DWORD cost, WCHAR* comment) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	WCHAR _program_name[32] = {0, };
	_tcsncpy(_program_name, program_name, 32);
	stream->writeWCHARs(_program_name, 32);
	stream->writeDWORD(cost);
	WCHAR _comment[32] = {0, };
	_tcsncpy(_comment, comment, 32);
	stream->writeWCHARs(_comment, 32);

	return stream->getLength();
}

inline DWORD WRITE_PT_SEL_PROGRAM(BYTE *buffer, WCHAR* program_name) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	WCHAR _program_name[32] = {0, };
	_tcsncpy(_program_name, program_name, 32);
	stream->writeWCHARs(_program_name, 32);

	return stream->getLength();
}

inline DWORD WRITE_PT_SEL_PROGRAM_RESULT(BYTE *buffer, WCHAR* program_name, DWORD cost, WCHAR* comment) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	WCHAR _program_name[32] = {0, };
	_tcsncpy(_program_name, program_name, 32);
	stream->writeWCHARs(_program_name, 32);
	stream->writeDWORD(cost);
	WCHAR _comment[32] = {0, };
	_tcsncpy(_comment, comment, 32);
	stream->writeWCHARs(_comment, 32);

	return stream->getLength();
}

