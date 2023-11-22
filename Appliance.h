#pragma once
#include "menu.h"
#include "SMSManager.h"

class ApplianceType
{
protected:
	std::string typeName; //가전 타입명
	std::map<int, std::string> stateList; // 상태 종류
	std::map<int, std::string> onoffState = { {0,"OFF"},{1,"ON"} }; // 전원상태 문자열 출력용
public:
	std::string appName; // 가전명
	int powerState; // 전원 On/Off 상태
	int state; // 동작 상태 number
	int powerComsumtion; // 시간당 소비전력
	time_t startHour; // 동작 on시 시작 시간
	time_t useHour; // 사용 누적시간 

	//가전타입 생성자 초기화
	ApplianceType(std::string typeName, std::map<int, std::string> list, std::string appname, int powerComsumtion);

	virtual ~ApplianceType() {};
	virtual void chageMenu(SMSManager& sms) = 0;
	virtual void infoShow() = 0;

	std::string getTypeName() { return typeName; }
	std::string getAppName() { return appName; }
	std::string getState() { return stateList[state]; }

	//전원상태 변경 함수(전 가전 공통)
	void turnOnOff(SMSManager& sms);

	//동작상태 변경 함수(전 가전 공통)
	void chageState();

};

//에어컨 객체 클래스
class Airconditioner : public ApplianceType
{
private:
	int temp;
public:
	Airconditioner(std::string name, int power) : ApplianceType("Airconditioner", { {1,"송풍"},{2,"냉방"},{3,"난방"} }, name, power)
	{
		this->temp = 25;
	}
	~Airconditioner() {}

	void changeTemp();
	//에어컨 정보 표시
	virtual void infoShow() override;
	//에어컨 정보 변경
	virtual void chageMenu(SMSManager& sms) override;
};

//밥솥 객체 클래스
class Ricecooker : public ApplianceType
{
public:
	Ricecooker(std::string name, int power) : ApplianceType("Ricecooker", { {1,"무동작"},{2,"보온"},{3,"밥짓기"},{4,"데우기"} }, name, power) {}
	~Ricecooker() {}

	//밥솥 정보 표시
	virtual void infoShow() override;
	//밥솥 상태 변경
	virtual void chageMenu(SMSManager& sms) override;
};

//세탁기 객체 클래스
class Washer : public ApplianceType
{
public:
	Washer(std::string name, int power) : ApplianceType("Washer", { {1,"무동작"},{2,"일반빨래"},{3,"삶은빨래"},{4,"건조"} }, name, power) {}
	~Washer() {}

	//세탁기 정보 표시
	virtual void infoShow() override;

	//세탁기 상태 변경
	virtual void chageMenu(SMSManager& sms) override;
};

// 전등 객체 클래스
class Light : public ApplianceType
{
public:
	Light(std::string name, int power) : ApplianceType("Light", {}, name, power) {}
	~Light() {}

	//전등 정보 표시
	virtual void infoShow() override;
	//전등 상태 변경
	virtual void chageMenu(SMSManager& sms) override;
};