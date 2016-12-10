#pragma once

inline VOID READ_PT_INS_USER(BYTE* buffer, S_PT_INS_USER& param) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	stream->readWCHARs(param.user_id, 32);
	stream->readWCHARs(param.user_name, 32);
	stream->readDWORD(&param.age);
	stream->readBYTE(&param.sex);
	stream->readWCHARs(param.address, 32);
}

inline VOID READ_PT_SEL_USER(BYTE* buffer, S_PT_SEL_USER& param) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	stream->readWCHARs(param.user_id, 32);
}

inline VOID READ_PT_SEL_USER_RESULT(BYTE* buffer, S_PT_SEL_USER_RESULT& param) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	stream->readWCHARs(param.user_id, 32);
	stream->readWCHARs(param.user_name, 32);
	stream->readDWORD(&param.age);
	stream->readBYTE(&param.sex);
	stream->readWCHARs(param.address, 32);
}

inline VOID READ_PT_INS_COMPUTER(BYTE* buffer, S_PT_INS_COMPUTER& param) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	stream->readWCHARs(param.computer_name, 32);
	stream->readWCHARs(param.ip_address, 32);
	stream->readBYTE(&param.cpu_type);
	stream->readDWORD(&param.ram);
	stream->readDWORD(&param.hdd);
}

inline VOID READ_PT_SEL_COMPUTER(BYTE* buffer, S_PT_SEL_COMPUTER& param) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	stream->readWCHARs(param.computer_name, 32);
}

inline VOID READ_PT_SEL_COMPUTER_RESULT(BYTE* buffer, S_PT_SEL_COMPUTER_RESULT& param) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	stream->readWCHARs(param.computer_name, 32);
	stream->readWCHARs(param.ip_address, 32);
	stream->readBYTE(&param.cpu_type);
	stream->readDWORD(&param.ram);
	stream->readDWORD(&param.hdd);
}

inline VOID READ_PT_INS_PROGRAM(BYTE* buffer, S_PT_INS_PROGRAM& param) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	stream->readWCHARs(param.program_name, 32);
	stream->readDWORD(&param.cost);
	stream->readWCHARs(param.comment, 32);
}

inline VOID READ_PT_SEL_PROGRAM(BYTE* buffer, S_PT_SEL_PROGRAM& param) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	stream->readWCHARs(param.program_name, 32);
}

inline VOID READ_PT_SEL_PROGRAM_RESULT(BYTE* buffer, S_PT_SEL_PROGRAM_RESULT& param) {
	SmartPointer<Stream> stream;
	stream->setBuffer(buffer);

	stream->readWCHARs(param.program_name, 32);
	stream->readDWORD(&param.cost);
	stream->readWCHARs(param.comment, 32);
}

