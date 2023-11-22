#pragma once
#include "menu.h"

class SMSManager
{
	using PHONENUMBER = std::string;

	std::map<std::string, std::vector<PHONENUMBER>> m;

public:
	//callback ��ȣ ��� �Լ�
	void add_sms_number(const std::string& key, const PHONENUMBER& number);
	//callback �Լ�
	void send_sms(const std::string& key, const std::string& msg);
	//�ߺ� �̸� �˻� �Լ�
	bool findPhoneNum(std::string phoneNum);
};

