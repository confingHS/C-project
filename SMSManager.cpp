#include "SMSManager.h"

void SMSManager::add_sms_number(const std::string& key, const PHONENUMBER& number)
{
	m[key].push_back(number);
}

void SMSManager::send_sms(const std::string& key, const std::string& msg)
{
	auto it = m.find(key);

	if (it != m.end())
	{
		for (const PHONENUMBER& number : it->second)
		{
			std::cout << "¢º CallBackMSG " << number << " : " << msg << std::endl;
		}
	}
}

bool SMSManager::findPhoneNum(std::string phoneNum)
{
	for (auto v : m)
	{
		for (auto e : v.second)
		{
			if (e == phoneNum)
			{
				return 1;
			}
		}
	}
	return 0;
}