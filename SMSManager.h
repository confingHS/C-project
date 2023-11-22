#pragma once
#include "menu.h"

class SMSManager
{
	using PHONENUMBER = std::string;

	std::map<std::string, std::vector<PHONENUMBER>> m;

public:
	//callback 번호 등록 함수
	void add_sms_number(const std::string& key, const PHONENUMBER& number);
	//callback 함수
	void send_sms(const std::string& key, const std::string& msg);
	//중복 이름 검색 함수
	bool findPhoneNum(std::string phoneNum);
};

