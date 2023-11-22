#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <functional>
#include <Windows.h>
#include <time.h>
#include <memory>
#include <map>

#ifndef MENU_H
#define MENU_H

using namespace std::placeholders;

//�޴�â ���� Ŭ����
class BaseMenu
{
	std::string title;
public:
	BaseMenu(const std::string& s) : title(s) {}

	std::string get_title() { return title; }

	virtual ~BaseMenu() {}
	virtual void command() = 0;
};

//�Լ������ �޴� Ŭ����
class MenuItem : public BaseMenu
{
	using HANDLER = std::function<void()>;

	HANDLER handler; // �޴� ���ý� ȣ��� �Լ�

public:
	MenuItem(const std::string& s, HANDLER h = nullptr)
		: BaseMenu(s), handler(h) {}
	//binding �� �Լ� ȣ�� �Լ�
	void command()
	{
		if (handler != nullptr)
			handler();
	}
};

//�ݺ� �˾��� �޴� Ŭ����
class PopupMenu : public BaseMenu
{
	std::vector<std::shared_ptr<BaseMenu>> v;

public:
	PopupMenu(const std::string& s) : BaseMenu(s) {}

	//�޴���� �߰� �Լ�
	void add(std::shared_ptr<BaseMenu> p) { v.push_back(p); }
	//�޴���� ���� �Լ�
	void pop(std::string title);
	//�޴���� �˾� �Լ�
	void command();
};

int intCin(std::string printString);

#endif