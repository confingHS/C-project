#include "HomeAutomationSystem.h"
#include <cctype>
#include <regex>

SMSManager sms;


HomeAutomationSystem::HomeAutomationSystem()
{
	std::cout << "==================================================" << std::endl;
	std::cout << "========= HomeAutomation을 시작합니다 ============" << std::endl;
	std::cout << "==================================================" << std::endl;
	Sleep(700);
	init_menu();
}

HomeAutomationSystem::~HomeAutomationSystem()
{
	system("cls");
	std::cout << "==================================================" << std::endl;
	std::cout << "=============== 소비 전력량 계산 =================" << std::endl;
	std::cout << "==================================================" << std::endl;
	totalPowerConsumtion();
	std::cout << "==================================================" << std::endl;
	std::cout << "========= HomeAutomation을 종료합니다 ============" << std::endl;
	std::cout << "==================================================" << std::endl;
}

void HomeAutomationSystem::init_menu()
{
	std::shared_ptr<PopupMenu> root = std::make_shared<PopupMenu>("ROOT");

	root->add(std::make_shared<MenuItem>("제품등록", std::bind(&HomeAutomationSystem::add_product, this)));
	root->add(std::make_shared<MenuItem>("제품삭제", std::bind(&HomeAutomationSystem::remove_product, this)));
	root->add(std::make_shared<MenuItem>("제품확인", std::bind(&HomeAutomationSystem::show_productInfo, this)));
	root->add(std::make_shared<MenuItem>("제품제어", std::bind(&HomeAutomationSystem::control_menu, this)));
	root->add(std::make_shared<MenuItem>("유저등록", std::bind(&HomeAutomationSystem::add_callback_user, this)));
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
	// 가전이름 입력 및 중복 이름 검사
	std::string imsiName;

	while (1)
	{
		int flag = 1;
		std::cout << "▶ 등록할 제품의 이름을 입력하세요 : ";
		std::cin >> imsiName;

		for (auto& v : mAppliance[typeName])
		{
			if (v->appName == imsiName)
			{
				std::cout << "이미 같은 이름의 제품이 존재합니다" << std::endl;
				flag = 0;
				break;
			}
		}

		if (flag == 1)
		{
			break;
		}
	}

	// 소비전력 입력 및 유효성 검사
	int imsiPowerConsumtion = intCin("▶ 등록할 제품의 소비전력을 입력하세요(kw/h) : ");

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
	std::cout <<"[" << typeName <<"] " << imsiName << " 이 등록 되었습니다" << std::endl;
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
	//가전 삭제 메뉴창 항목 삭제
	menu->pop(menutitle);

	//vector 내에서 등록된 가전 삭제
	for (int i = 0; i < mAppliance[apptype].size(); i++)
	{
		if (mAppliance[apptype][i]->appName == appname)
		{
			std::cout << "****************************************" << std::endl;
			std::cout << "[" << apptype << "] " << appname << " 이 삭제 되었습니다" << std::endl;
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

	root->add(std::make_shared <MenuItem>("개별제품 제어", std::bind(&HomeAutomationSystem::control_product, this)));
	root->add(std::make_shared <MenuItem>("전제품 전원 On", std::bind(&HomeAutomationSystem::allProductPowerOn, this)));
	root->add(std::make_shared <MenuItem>("전제품 전원 Off", std::bind(&HomeAutomationSystem::allProductPowerOff, this)));

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
		std::cout << "[" << v.first << "] 의 총 소비전력량 : " << appPowerSum / 3600 << "(kW/h)" << std::endl;
		sum += appPowerSum;
	}
	std::cout << "▶ 총 소비 전력량 : " << sum / 3600 << "(kW/h)" << std::endl;
}

bool isValidPhoneNumber(const std::string& phoneNumber) {
	// 핸드폰 번호는 11자리여야 함
	if (phoneNumber.length() != 11) {
		return false;
	}

	// 모든 문자가 숫자여야 함
	for (char digit : phoneNumber) {
		if (!std::isdigit(digit)) {
			return false;
		}
	}

	return true;
}

std::string formatPhoneNumber(const std::string& phoneNumber) {
	// 정규식을 사용하여 핸드폰 번호를 ***-****-**** 형식으로 변경
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
	std::cout << "전원 동작시 등록된 번호로 Call Back Message를 알려주는 기능입니다" << std::endl;
	std::cout << "=================================================================" << std::endl;
	Sleep(500);

	//입력 번호 유효성 검사 및 중복이름 검사
	do {
		std::cout << "▶ 11자리 핸드폰 번호를 등록해주세요('-' 생략)"<<std::endl;
		std::cout << "▶ 입력 : ";
		std::cin >> phoneNum;
		
		if (!isValidPhoneNumber(phoneNum)) {
			std::cout << "유효하지 않은 번호입니다. 다시 입력해주세요." << std::endl;
		}

		formattedPhoneNumber = formatPhoneNumber(phoneNum);

		if (sms.findPhoneNum(formattedPhoneNumber))
		{
			std::cout << "기존에 있는 번호입니다. 다시 입력해주세요." << std::endl;
		}
		
	} while (!isValidPhoneNumber(phoneNum)||sms.findPhoneNum(formattedPhoneNumber));

	sms.add_sms_number("Airconditioner", formattedPhoneNumber);
	sms.add_sms_number("Ricecooker", formattedPhoneNumber);
	sms.add_sms_number("Washer", formattedPhoneNumber);
	sms.add_sms_number("Light", formattedPhoneNumber);
	std::cout << "****************************************" << std::endl;
	std::cout << "[" << formattedPhoneNumber << "]" << " 이 등록 되었습니다" << std::endl;
	std::cout << "****************************************" << std::endl;
	Sleep(1000);
}