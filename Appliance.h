#pragma once
#include "menu.h"
#include "SMSManager.h"

class ApplianceType
{
protected:
	std::string typeName; //���� Ÿ�Ը�
	std::map<int, std::string> stateList; // ���� ����
	std::map<int, std::string> onoffState = { {0,"OFF"},{1,"ON"} }; // �������� ���ڿ� ��¿�
public:
	std::string appName; // ������
	int powerState; // ���� On/Off ����
	int state; // ���� ���� number
	int powerComsumtion; // �ð��� �Һ�����
	time_t startHour; // ���� on�� ���� �ð�
	time_t useHour; // ��� �����ð� 

	//����Ÿ�� ������ �ʱ�ȭ
	ApplianceType(std::string typeName, std::map<int, std::string> list, std::string appname, int powerComsumtion);

	virtual ~ApplianceType() {};
	virtual void chageMenu(SMSManager& sms) = 0;
	virtual void infoShow() = 0;

	std::string getTypeName() { return typeName; }
	std::string getAppName() { return appName; }
	std::string getState() { return stateList[state]; }

	//�������� ���� �Լ�(�� ���� ����)
	void turnOnOff(SMSManager& sms);

	//���ۻ��� ���� �Լ�(�� ���� ����)
	void chageState();

};

//������ ��ü Ŭ����
class Airconditioner : public ApplianceType
{
private:
	int temp;
public:
	Airconditioner(std::string name, int power) : ApplianceType("Airconditioner", { {1,"��ǳ"},{2,"�ù�"},{3,"����"} }, name, power)
	{
		this->temp = 25;
	}
	~Airconditioner() {}

	void changeTemp();
	//������ ���� ǥ��
	virtual void infoShow() override;
	//������ ���� ����
	virtual void chageMenu(SMSManager& sms) override;
};

//��� ��ü Ŭ����
class Ricecooker : public ApplianceType
{
public:
	Ricecooker(std::string name, int power) : ApplianceType("Ricecooker", { {1,"������"},{2,"����"},{3,"������"},{4,"�����"} }, name, power) {}
	~Ricecooker() {}

	//��� ���� ǥ��
	virtual void infoShow() override;
	//��� ���� ����
	virtual void chageMenu(SMSManager& sms) override;
};

//��Ź�� ��ü Ŭ����
class Washer : public ApplianceType
{
public:
	Washer(std::string name, int power) : ApplianceType("Washer", { {1,"������"},{2,"�Ϲݻ���"},{3,"��������"},{4,"����"} }, name, power) {}
	~Washer() {}

	//��Ź�� ���� ǥ��
	virtual void infoShow() override;

	//��Ź�� ���� ����
	virtual void chageMenu(SMSManager& sms) override;
};

// ���� ��ü Ŭ����
class Light : public ApplianceType
{
public:
	Light(std::string name, int power) : ApplianceType("Light", {}, name, power) {}
	~Light() {}

	//���� ���� ǥ��
	virtual void infoShow() override;
	//���� ���� ����
	virtual void chageMenu(SMSManager& sms) override;
};