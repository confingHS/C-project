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

//메뉴창 상위 클래스
class BaseMenu
{
	std::string title;
public:
	BaseMenu(const std::string& s) : title(s) {}

	std::string get_title() { return title; }

	virtual ~BaseMenu() {}
	virtual void command() = 0;
};

//함수실행용 메뉴 클래스
class MenuItem : public BaseMenu
{
	using HANDLER = std::function<void()>;

	HANDLER handler; // 메뉴 선택시 호출될 함수

public:
	MenuItem(const std::string& s, HANDLER h = nullptr)
		: BaseMenu(s), handler(h) {}
	//binding 된 함수 호출 함수
	void command()
	{
		if (handler != nullptr)
			handler();
	}
};

//반복 팝업용 메뉴 클래스
class PopupMenu : public BaseMenu
{
	std::vector<std::shared_ptr<BaseMenu>> v;

public:
	PopupMenu(const std::string& s) : BaseMenu(s) {}

	//메뉴목록 추가 함수
	void add(std::shared_ptr<BaseMenu> p) { v.push_back(p); }
	//메뉴목록 삭제 함수
	void pop(std::string title);
	//메뉴목록 팝업 함수
	void command();
};

int intCin(std::string printString);

#endif