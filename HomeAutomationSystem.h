#pragma once
#include "Appliance.h"



class HomeAutomationSystem
{

public:
	std::map<std::string, std::vector<std::shared_ptr<ApplianceType>>> mAppliance;

	HomeAutomationSystem();
	~HomeAutomationSystem();

	//HomeAuto �޴�â
	void init_menu();

	//��ǰ ��� ���� �޴� â
	void add_product();

	//��ǰ ��� �Լ�
	void addAppliance(std::string typeName);

	//��ǰ ���� ���� �޴� â
	void remove_product();

	//���� ���� �Լ�
	void deleteAppliance(std::shared_ptr<PopupMenu> menu, std::string menutitle, std::string apptype, std::string appname);

	//��ǰ Ȯ�� ���� �޴� â
	void show_productInfo();

	//��ǰ ���� ���� �޴� â
	void control_menu();

	//��ǰ �� ���� �޴� â
	void control_product();

	//����ǰ ���� ON �Լ�
	void allProductPowerOn();

	//����ǰ ���� OFF �Լ�
	void allProductPowerOff();

	//���·� ��� �Լ�
	void totalPowerConsumtion();

	//�ݹ� �������� �޴� â
	void user_menu();

	//�ݹ� ���� ��� �Լ�
	void add_callback_user();

	//�ݹ� ���� ���� �Լ�
	void delet_callbakc_user();

};

