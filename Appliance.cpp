#include "Appliance.h"

ApplianceType::ApplianceType(std::string typeName, std::map<int, std::string> list, std::string appname, int powerComsumtion)
{
	this->typeName = typeName;
	stateList = list;
	appName = appname;
	powerState = 0;
	state = 1;
	this->powerComsumtion = powerComsumtion;
	startHour = 0;
	useHour = 0;
}
void ApplianceType::turnOnOff(SMSManager& sms)
{
	time_t currentTime;
	if (powerState == 0)
	{
		std::string CallBackMSG = "[" + this->getTypeName() + "] " + this->appName + "의 전원이 ON 되었습니다";
		powerState = 1;
		std::cout << "***************************************************************" << std::endl;
		std::cout << CallBackMSG << std::endl;
		std::cout << "***************************************************************" << std::endl;
		sms.send_sms(this->getTypeName(), CallBackMSG);
		this->startHour = time(&currentTime);
		Sleep(1000);
	}
	else if (powerState == 1)
	{
		std::string CallBackMSG = "[" + this->getTypeName() + "] " + this->appName + "의 전원이 OFF 되었습니다";
		powerState = 0;
		std::cout << "***************************************************************" << std::endl;
		std::cout << CallBackMSG << std::endl;
		std::cout << "***************************************************************" << std::endl;
		sms.send_sms(this->getTypeName(), CallBackMSG);
		this->useHour += (time(&currentTime) - this->startHour);
		this->startHour = 0;
		Sleep(1000);
	}
}
void ApplianceType::chageState()
{
	if (powerState == 0)
	{
		std::cout << "************************" << std::endl;
		std::cout << "* 전원을 먼저 켜주세요 *" << std::endl;
		std::cout << "************************" << std::endl;
		Sleep(500);
		return;
	}

	int imsiState;

	while(1)
	{
		system("cls");
		std::cout << "======================================" << std::endl;
		for (auto& e : stateList)
		{
			std::cout << e.first << ". " << e.second << std::endl;
		}
		std::cout << "======================================" << std::endl;
		imsiState = intCin("▶ 변경할 상태를 선택해주세요 : ");
		auto p = stateList.find(imsiState);
		if (p != stateList.end())
		{
			break;
		}
	}

	this->state = imsiState;
	std::cout << "******************************" << std::endl;
	std::cout << "[" << stateList[this->state] << "] 로 변경되었습니다" << std::endl;
	std::cout << "******************************" << std::endl;
	Sleep(500);
}

void Airconditioner::changeTemp()
{
	if (powerState == 0)
	{
		std::cout << "************************" << std::endl;
		std::cout << "* 전원을 먼저 켜주세요 *" << std::endl;
		std::cout << "************************" << std::endl;
		Sleep(500);
		return;
	}

	std::cout << "현재 온도 " << this->temp << "도 입니다" << std::endl;
	int imsiTemp = intCin("▶ 변경할 온도를 입력해주세요 : ");
	this->temp = imsiTemp;
	std::cout << "******************************" << std::endl;
	std::cout << imsiTemp << "도 로 변경되었습니다" << std::endl;
	std::cout << "******************************" << std::endl;
	Sleep(500);
}
void Airconditioner::infoShow()
{
	std::cout << "======================================" << std::endl;
	std::cout << "가전 타입 : " << this->getTypeName() << std::endl;
	std::cout << "가전 이름 : " << this->appName << std::endl;
	std::cout << "전원 상태 : " << this->onoffState[powerState] << std::endl;
	std::cout << "동작 상태 : " << this->getState() << std::endl;
	std::cout << "설정 온도 : " << temp<< " ℃" << std::endl;
	std::cout << "소비 전력 : " << this->powerComsumtion <<" (kW/h)" << std::endl;
	std::cout << "======================================" << std::endl;
	std::cout << "▶ 아무키나 입력해주세요" << std::endl;
	_getch();
}
void Airconditioner::chageMenu(SMSManager& sms)
{
	std::shared_ptr<PopupMenu> change = std::make_shared<PopupMenu>("change");
	change->add(std::make_shared<MenuItem>("전원 상태 변경", std::bind(&Airconditioner::turnOnOff, this, sms)));
	change->add(std::make_shared <MenuItem>("동작 상태 변경", std::bind(&Airconditioner::chageState, this)));
	change->add(std::make_shared <MenuItem>("온도 변경", std::bind(&Airconditioner::changeTemp, this)));
	change->command();
}

void Ricecooker::infoShow()
{
	std::cout << "======================================" << std::endl;
	std::cout << "가전 타입 : " << this->getTypeName() << std::endl;
	std::cout << "가전 이름 : " << this->appName << std::endl;
	std::cout << "전원 상태 : " << this->onoffState[powerState] << std::endl;
	std::cout << "동작 상태 : " << this->getState() << std::endl;
	std::cout << "소비 전력 : " << this->powerComsumtion << " (kW/h)" << std::endl;
	std::cout << "======================================" << std::endl;
	std::cout << "▶ 아무키나 입력해주세요" << std::endl;
	_getch();
}
void Ricecooker::chageMenu(SMSManager& sms)
{
	std::shared_ptr<PopupMenu> change = std::make_shared<PopupMenu>("change");
	change->add(std::make_shared<MenuItem>("전원 상태 변경", std::bind(&Ricecooker::turnOnOff, this, sms)));
	change->add(std::make_shared<MenuItem>("동작 상태 변경", std::bind(&Ricecooker::chageState, this)));
	change->command();
}

void Washer::infoShow()
{
	std::cout << "======================================" << std::endl;
	std::cout << "가전 타입 : " << this->getTypeName() << std::endl;
	std::cout << "가전 이름 : " << this->appName << std::endl;
	std::cout << "전원 상태 : " << this->onoffState[powerState] << std::endl;
	std::cout << "동작 상태 : " << this->getState() << std::endl;
	std::cout << "소비 전력 : " << this->powerComsumtion << " (kW/h)" << std::endl;
	std::cout << "======================================" << std::endl;
	std::cout << "▶ 아무키나 입력해주세요" << std::endl;
	_getch();
}
void Washer::chageMenu(SMSManager& sms)
{
	std::shared_ptr<PopupMenu> change = std::make_shared<PopupMenu>("change");
	change->add(std::make_shared<MenuItem>("전원 상태 변경", std::bind(&Washer::turnOnOff, this, sms)));
	change->add(std::make_shared<MenuItem>("동작 상태 변경", std::bind(&Washer::chageState, this)));
	change->command();
}

void Light::infoShow()
{
	std::cout << "======================================" << std::endl;
	std::cout << "가전 타입 : " << this->getTypeName() << std::endl;
	std::cout << "가전 이름 : " << this->appName << std::endl;
	std::cout << "전원 상태 : " << this->onoffState[powerState] << std::endl;
	std::cout << "소비 전력 : " << this->powerComsumtion << " (kW/h)" << std::endl;
	std::cout << "======================================" << std::endl;
	std::cout << "▶ 아무키나 입력해주세요" << std::endl;
	_getch();
}
void Light::chageMenu(SMSManager& sms)
{
	std::shared_ptr<PopupMenu> change = std::make_shared<PopupMenu>("change");
	change->add(std::make_shared<MenuItem>("전원 상태 변경", std::bind(&Light::turnOnOff, this, sms)));
	change->command();
}

