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
		std::string CallBackMSG = "[" + this->getTypeName() + "] " + this->appName + "�� ������ ON �Ǿ����ϴ�";
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
		std::string CallBackMSG = "[" + this->getTypeName() + "] " + this->appName + "�� ������ OFF �Ǿ����ϴ�";
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
		std::cout << "* ������ ���� ���ּ��� *" << std::endl;
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
		imsiState = intCin("�� ������ ���¸� �������ּ��� : ");
		auto p = stateList.find(imsiState);
		if (p != stateList.end())
		{
			break;
		}
	}

	this->state = imsiState;
	std::cout << "******************************" << std::endl;
	std::cout << "[" << stateList[this->state] << "] �� ����Ǿ����ϴ�" << std::endl;
	std::cout << "******************************" << std::endl;
	Sleep(500);
}

void Airconditioner::changeTemp()
{
	if (powerState == 0)
	{
		std::cout << "************************" << std::endl;
		std::cout << "* ������ ���� ���ּ��� *" << std::endl;
		std::cout << "************************" << std::endl;
		Sleep(500);
		return;
	}

	std::cout << "���� �µ� " << this->temp << "�� �Դϴ�" << std::endl;
	int imsiTemp = intCin("�� ������ �µ��� �Է����ּ��� : ");
	this->temp = imsiTemp;
	std::cout << "******************************" << std::endl;
	std::cout << imsiTemp << "�� �� ����Ǿ����ϴ�" << std::endl;
	std::cout << "******************************" << std::endl;
	Sleep(500);
}
void Airconditioner::infoShow()
{
	std::cout << "======================================" << std::endl;
	std::cout << "���� Ÿ�� : " << this->getTypeName() << std::endl;
	std::cout << "���� �̸� : " << this->appName << std::endl;
	std::cout << "���� ���� : " << this->onoffState[powerState] << std::endl;
	std::cout << "���� ���� : " << this->getState() << std::endl;
	std::cout << "���� �µ� : " << temp<< " ��" << std::endl;
	std::cout << "�Һ� ���� : " << this->powerComsumtion <<" (kW/h)" << std::endl;
	std::cout << "======================================" << std::endl;
	std::cout << "�� �ƹ�Ű�� �Է����ּ���" << std::endl;
	_getch();
}
void Airconditioner::chageMenu(SMSManager& sms)
{
	std::shared_ptr<PopupMenu> change = std::make_shared<PopupMenu>("change");
	change->add(std::make_shared<MenuItem>("���� ���� ����", std::bind(&Airconditioner::turnOnOff, this, sms)));
	change->add(std::make_shared <MenuItem>("���� ���� ����", std::bind(&Airconditioner::chageState, this)));
	change->add(std::make_shared <MenuItem>("�µ� ����", std::bind(&Airconditioner::changeTemp, this)));
	change->command();
}

void Ricecooker::infoShow()
{
	std::cout << "======================================" << std::endl;
	std::cout << "���� Ÿ�� : " << this->getTypeName() << std::endl;
	std::cout << "���� �̸� : " << this->appName << std::endl;
	std::cout << "���� ���� : " << this->onoffState[powerState] << std::endl;
	std::cout << "���� ���� : " << this->getState() << std::endl;
	std::cout << "�Һ� ���� : " << this->powerComsumtion << " (kW/h)" << std::endl;
	std::cout << "======================================" << std::endl;
	std::cout << "�� �ƹ�Ű�� �Է����ּ���" << std::endl;
	_getch();
}
void Ricecooker::chageMenu(SMSManager& sms)
{
	std::shared_ptr<PopupMenu> change = std::make_shared<PopupMenu>("change");
	change->add(std::make_shared<MenuItem>("���� ���� ����", std::bind(&Ricecooker::turnOnOff, this, sms)));
	change->add(std::make_shared<MenuItem>("���� ���� ����", std::bind(&Ricecooker::chageState, this)));
	change->command();
}

void Washer::infoShow()
{
	std::cout << "======================================" << std::endl;
	std::cout << "���� Ÿ�� : " << this->getTypeName() << std::endl;
	std::cout << "���� �̸� : " << this->appName << std::endl;
	std::cout << "���� ���� : " << this->onoffState[powerState] << std::endl;
	std::cout << "���� ���� : " << this->getState() << std::endl;
	std::cout << "�Һ� ���� : " << this->powerComsumtion << " (kW/h)" << std::endl;
	std::cout << "======================================" << std::endl;
	std::cout << "�� �ƹ�Ű�� �Է����ּ���" << std::endl;
	_getch();
}
void Washer::chageMenu(SMSManager& sms)
{
	std::shared_ptr<PopupMenu> change = std::make_shared<PopupMenu>("change");
	change->add(std::make_shared<MenuItem>("���� ���� ����", std::bind(&Washer::turnOnOff, this, sms)));
	change->add(std::make_shared<MenuItem>("���� ���� ����", std::bind(&Washer::chageState, this)));
	change->command();
}

void Light::infoShow()
{
	std::cout << "======================================" << std::endl;
	std::cout << "���� Ÿ�� : " << this->getTypeName() << std::endl;
	std::cout << "���� �̸� : " << this->appName << std::endl;
	std::cout << "���� ���� : " << this->onoffState[powerState] << std::endl;
	std::cout << "�Һ� ���� : " << this->powerComsumtion << " (kW/h)" << std::endl;
	std::cout << "======================================" << std::endl;
	std::cout << "�� �ƹ�Ű�� �Է����ּ���" << std::endl;
	_getch();
}
void Light::chageMenu(SMSManager& sms)
{
	std::shared_ptr<PopupMenu> change = std::make_shared<PopupMenu>("change");
	change->add(std::make_shared<MenuItem>("���� ���� ����", std::bind(&Light::turnOnOff, this, sms)));
	change->command();
}

