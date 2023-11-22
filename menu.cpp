#include "menu.h"

void PopupMenu::pop(std::string title) {
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i]->get_title() == title)
		{
			v.erase(v.begin() + i);
			break;
		}
	}
}

void PopupMenu::command()
{

	while (1)
	{
		system("cls");

		int sz = v.size();
		for (int i = 0; i < sz; i++)
		{
			std::cout << i + 1 << ". " << v[i]->get_title() << std::endl;
		}
		std::cout << sz + 1 << ". 종료\n";

		int cmd;
		std::cout << "▶ 메뉴를 선택하세요 : ";
		std::cin >> cmd;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(100, '\n');
			continue;
		}

		if (std::cin.get() != '\n')
		{
			std::cin.clear();
			std::cin.ignore(100, '\n');
			continue;
		}

		if (cmd == sz + 1)
			break;

		if (cmd < 1 || cmd > sz + 1)
			continue;

		v[cmd - 1]->command();
	}
}

int intCin(std::string printString)
{
	int returnNum;

	while (1) {

		std::cout << printString;
		std::cin >> returnNum;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(100, '\n');
			continue;
		}
		else if (std::cin.get() != '\n') {
			std::cin.clear();
			std::cin.ignore(100, '\n');
			continue;
		}
		else {
			std::cin.clear();
			break;
		}
	}

	return returnNum;
}