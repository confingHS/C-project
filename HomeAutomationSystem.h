#pragma once
#include "Appliance.h"



class HomeAutomationSystem
{

public:
	std::map<std::string, std::vector<std::shared_ptr<ApplianceType>>> mAppliance;

	HomeAutomationSystem();
	~HomeAutomationSystem();

	//HomeAuto 메뉴창
	void init_menu();

	//제품 등록 하위 메뉴 창
	void add_product();

	//제품 등록 함수
	void addAppliance(std::string typeName);

	//제품 삭제 하위 메뉴 창
	void remove_product();

	//가전 삭제 함수
	void deleteAppliance(std::shared_ptr<PopupMenu> menu, std::string menutitle, std::string apptype, std::string appname);

	//제품 확인 하위 메뉴 창
	void show_productInfo();

	//제품 제어 하위 메뉴 창
	void control_menu();

	//제품 상세 제어 메뉴 창
	void control_product();

	//전제품 전원 ON 함수
	void allProductPowerOn();

	//전제품 전원 OFF 함수
	void allProductPowerOff();

	//전력량 계산 함수
	void totalPowerConsumtion();

	//콜백 유저관리 메뉴 창
	void user_menu();

	//콜백 유저 등록 함수
	void add_callback_user();

	//콜백 유저 삭제 함수
	void delet_callbakc_user();

};

