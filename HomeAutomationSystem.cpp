#include "HomeAutomationSystem.h"
#include <cctype>
#include <regex>

SMSManager sms;


HomeAutomationSystem::HomeAutomationSystem()
{
	std::cout << "==================================================" << std::endl;
	std::cout << "========= HomeAutomation�� �����մϴ� ============" << std::endl;
	std::cout << "==================================================" << std::endl;
	Sleep(700);
	init_menu();
}

HomeAutomationSystem::~HomeAutomationSystem()
{
	system("cls");
	std::cout << "==================================================" << std::endl;
	std::cout << "=============== �Һ� ���·� ��� =================" << std::endl;
	std::cout << "==================================================" << std::endl;
	totalPowerConsumtion();
	std::cout << "==================================================" << std::endl;
	std::cout << "========= HomeAutomation�� �����մϴ� ============" << std::endl;
	std::cout << "==================================================" << std::endl;
}

void HomeAutomationSystem::init_menu()
{
	std::shared_ptr<PopupMenu> root = std::make_shared<PopupMenu>("ROOT");

	root->add(std::make_shared<MenuItem>("��ǰ���", std::bind(&HomeAutomationSystem::add_product, this)));
	root->add(std::make_shared<MenuItem>("��ǰ����", std::bind(&HomeAutomationSystem::remove_product, this)));
	root->add(std::make_shared<MenuItem>("��ǰȮ��", std::bind(&HomeAutomationSystem::show_productInfo, this)));
	root->add(std::make_shared<MenuItem>("��ǰ����", std::bind(&HomeAutomationSystem::control_menu, this)));
	root->add(std::make_shared<MenuItem>("�������", std::bind(&HomeAutomationSystem::add_callback_user, this)));
	root->command();
}

void HomeAutomationSystem::add_product()
{
	std::shared_ptr<PopupMenu> AppTypePopUp = std::make_shared<PopupMenu>("ROOT");
	AppTypePopUp->add(std::make_shared<MenuItem>("Airconditioner", std::bind(&HomeAutomationSystem::addAppliance, this, "Airconditioner")));
	AppTypePopUp->add(std::make_shared<MenuItem>("Ricecooker", std::bind(&HomeAutomationSystem::addAppliance, this, "Ricecooker")));
	AppTypePopUp->add(std::make_shared<MenuItem>("Washer", std::bind(&HomeAutomationSystem::addAppliance, this, "Washer")));
	AppTypePopUp->add(std::make_shared<MenuItem>("Light", std::bind(&HomeAutomationSystem::addAppliance, this, "Light")));
	AppTypePopUp->command();
}

void HomeAutomationSystem::addAppliance(std::string typeName)
{
	// �����̸� �Է� �� �ߺ� �̸� �˻�
	std::string imsiName;

	while (1)
	{
		int flag = 1;
		std::cout << "�� ����� ��ǰ�� �̸��� �Է��ϼ��� : ";
		std::cin >> imsiName;

		for (auto& v : mAppliance[typeName])
		{
			if (v->appName == imsiName)
			{
				std::cout << "�̹� ���� �̸��� ��ǰ�� �����մϴ�" << std::endl;
				flag = 0;
				break;
			}
		}

		if (flag == 1)
		{
			break;
		}
	}

	// �Һ����� �Է� �� ��ȿ�� �˻�
	int imsiPowerConsumtion = intCin("�� ����� ��ǰ�� �Һ������� �Է��ϼ���(kw/h) : ");

	if (typeName == "Airconditioner")
	{
		mAppliance[typeName].push_back(std::make_shared<Airconditioner>(imsiName, imsiPowerConsumtion));
	}
	else if (typeName == "Ricecooker")
	{
		mAppliance[typeName].push_back(std::make_shared<Ricecooker>(imsiName, imsiPowerConsumtion));
	}
	else if (typeName == "Washer")
	{
		mAppliance[typeName].push_back(std::make_shared<Washer>(imsiName, imsiPowerConsumtion));
	}
	else if (typeName == "Light")
	{
		mAppliance[typeName].push_back(std::make_shared<Light>(imsiName, imsiPowerConsumtion));
	}
	std::cout << "****************************************" << std::endl;
	std::cout <<"[" << typeName <<"] " << imsiName << " �� ��� �Ǿ����ϴ�" << std::endl;
	std::cout << "****************************************" << std::endl;
	Sleep(700);

}

void HomeAutomationSystem::remove_product()
{
	std::shared_ptr<PopupMenu> nowAppList = std::make_shared<PopupMenu>("ROOT");
	for (auto& v : mAppliance)
	{
		for (int i = 0; i < v.second.size(); i++)
		{
			std::string imsi = "[" + v.second[i]->getTypeName() + "] " + v.second[i]->getAppName();
			nowAppList->add(std::make_shared<MenuItem>(imsi, std::bind(&HomeAutomationSystem::deleteAppliance,this, std::ref(nowAppList), imsi, v.first, v.second[i]->appName)));
		}
	}
	nowAppList->command();
}

void HomeAutomationSystem::deleteAppliance(std::shared_ptr<PopupMenu> menu, std::string menutitle, std::string apptype, std::string appname)
{
	//���� ���� �޴�â �׸� ����
	menu->pop(menutitle);

	//vector ������ ��ϵ� ���� ����
	for (int i = 0; i < mAppliance[apptype].size(); i++)
	{
		if (mAppliance[apptype][i]->appName == appname)
		{
			std::cout << "****************************************" << std::endl;
			std::cout << "[" << apptype << "] " << appname << " �� ���� �Ǿ����ϴ�" << std::endl;
			std::cout << "****************************************" << std::endl;
			mAppliance[apptype].erase(mAppliance[apptype].begin() + i);
			Sleep(700);
			break;
		}
	}
}

void HomeAutomationSystem::show_productInfo()
{
	std::shared_ptr<PopupMenu> nowAppList = std::make_shared<PopupMenu>("ROOT");
	for (auto& v : mAppliance)
	{
		for (auto e : v.second)
		{
			std::string imsi = "[" + e->getTypeName() + "] " + e->getAppName();
			nowAppList->add(std::make_shared<MenuItem>(imsi, std::bind(&ApplianceType::infoShow, e)));
		}
	}
	nowAppList->command();
}

void HomeAutomationSystem::control_menu()
{
	std::shared_ptr<PopupMenu> root = std::make_shared<PopupMenu>("ROOT");

	root->add(std::make_shared <MenuItem>("������ǰ ����", std::bind(&HomeAutomationSystem::control_product, this)));
	root->add(std::make_shared <MenuItem>("����ǰ ���� On", std::bind(&HomeAutomationSystem::allProductPowerOn, this)));
	root->add(std::make_shared <MenuItem>("����ǰ ���� Off", std::bind(&HomeAutomationSystem::allProductPowerOff, this)));

	root->command();
}

void HomeAutomationSystem::control_product()
{
	std::shared_ptr<PopupMenu> nowAppList = std::make_shared<PopupMenu>("ROOT");
	for (auto& v : mAppliance)
	{
		for (auto& e : v.second)
		{
			std::string imsi = "[" + e->getTypeName() + "] " + e->getAppName();
			nowAppList->add(std::make_shared<MenuItem>(imsi, std::bind(&ApplianceType::chageMenu, e, sms)));
		}
	}
	nowAppList->command();
}

void HomeAutomationSystem::allProductPowerOn()
{
	for (auto& v : mAppliance) {
		for (auto& e : v.second) {
			if (e->powerState == 0) {
				e->turnOnOff(sms);
			}
		}
	}
}

void HomeAutomationSystem::allProductPowerOff()
{
	for (auto& v : mAppliance) {
		for (auto& e : v.second) {
			if (e->powerState == 1) {
				e->turnOnOff(sms);
			}
		}
	}
}

void HomeAutomationSystem::totalPowerConsumtion()
{
	float sum = 0;
	for (auto& v : mAppliance) {
		float appPowerSum = 0;
		for (auto& e : v.second) {
			if (e->powerState == 1) {
				e->turnOnOff(sms);
			}
			appPowerSum += (e->useHour) * (e->powerComsumtion);
		}
		std::cout << "[" << v.first << "] �� �� �Һ����·� : " << appPowerSum / 3600 << "(kW/h)" << std::endl;
		sum += appPowerSum;
	}
	std::cout << "�� �� �Һ� ���·� : " << sum / 3600 << "(kW/h)" << std::endl;
}

bool isValidPhoneNumber(const std::string& phoneNumber) {
	// �ڵ��� ��ȣ�� 11�ڸ����� ��
	if (phoneNumber.length() != 11) {
		return false;
	}

	// ��� ���ڰ� ���ڿ��� ��
	for (char digit : phoneNumber) {
		if (!std::isdigit(digit)) {
			return false;
		}
	}

	return true;
}

std::string formatPhoneNumber(const std::string& phoneNumber) {
	// ���Խ��� ����Ͽ� �ڵ��� ��ȣ�� ***-****-**** �������� ����
	std::regex regexPattern("(\\d{3})(\\d{4})(\\d{4})");
	std::string formattedNumber = std::regex_replace(phoneNumber, regexPattern, "$1-$2-$3");
	return formattedNumber;
}

void HomeAutomationSystem::add_callback_user()
{
	std::string phoneNum;
	std::string formattedPhoneNumber;

	system("cls");
	std::cout << "=================================================================" << std::endl;
	std::cout << "���� ���۽� ��ϵ� ��ȣ�� Call Back Message�� �˷��ִ� ����Դϴ�" << std::endl;
	std::cout << "=================================================================" << std::endl;
	Sleep(500);

	//�Է� ��ȣ ��ȿ�� �˻� �� �ߺ��̸� �˻�
	do {
		std::cout << "�� 11�ڸ� �ڵ��� ��ȣ�� ������ּ���('-' ����)"<<std::endl;
		std::cout << "�� �Է� : ";
		std::cin >> phoneNum;
		
		if (!isValidPhoneNumber(phoneNum)) {
			std::cout << "��ȿ���� ���� ��ȣ�Դϴ�. �ٽ� �Է����ּ���." << std::endl;
		}

		formattedPhoneNumber = formatPhoneNumber(phoneNum);

		if (sms.findPhoneNum(formattedPhoneNumber))
		{
			std::cout << "������ �ִ� ��ȣ�Դϴ�. �ٽ� �Է����ּ���." << std::endl;
		}
		
	} while (!isValidPhoneNumber(phoneNum)||sms.findPhoneNum(formattedPhoneNumber));

	sms.add_sms_number("Airconditioner", formattedPhoneNumber);
	sms.add_sms_number("Ricecooker", formattedPhoneNumber);
	sms.add_sms_number("Washer", formattedPhoneNumber);
	sms.add_sms_number("Light", formattedPhoneNumber);
	std::cout << "****************************************" << std::endl;
	std::cout << "[" << formattedPhoneNumber << "]" << " �� ��� �Ǿ����ϴ�" << std::endl;
	std::cout << "****************************************" << std::endl;
	Sleep(1000);
}