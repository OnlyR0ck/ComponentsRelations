//
// Created by guita on 13.04.2021.
//
#include "Menu.h"

#pragma region Menu

void Menu::color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void Menu::set_color(int* arr, int count, int color)
{
	for (int i = 0; i < count; i++)
	{
		arr[i] = color;
	}
}
void Menu::start()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	const char* top;
	top = R"(
 ███▄ ▄███▓▓█████  ███▄    █  █    ██
▓██▒▀█▀ ██▒▓█   ▀  ██ ▀█   █  ██  ▓██▒
▓██    ▓██░▒███   ▓██  ▀█ ██▒▓██  ▒██░
▒██    ▒██ ▒▓█  ▄ ▓██▒  ▐▌██▒▓▓█  ░██░
▒██▒   ░██▒░▒████▒▒██░   ▓██░▒▒█████▓
░ ▒░   ░  ░░░ ▒░ ░░ ▒░   ▒ ▒ ░▒▓▒ ▒ ▒
░  ░      ░ ░ ░  ░░ ░░   ░ ▒░░░▒░ ░ ░
░      ░      ░      ░   ░ ░  ░░░ ░ ░
       ░      ░  ░         ░    ░    )";
	int* Set = new int[size];
	set_color(Set, size, 7);
	int counter = 0;
	char key;

	add([] {}, "Выход.");
	while (true)
	{
		gotoXY(0, 0);
		color(4);
		std::cout << top << std::endl;
		for (int j = 0; j < size; j++)
		{
			gotoXY(1, 12 + j);
			color(Set[j]);
			std::cout << j + 1 << ". " << names_.at(j) << std::endl;
		}

		key = _getch();
		if (static_cast<int>(key) == -32)
		{
			switch (_getch())
			{
			case 72:
				if ((counter >= 1 && counter < size))
				{
					counter--;
				}
				break;
			case 80:
				if (counter >= 0 && counter < size - 1)
				{
					counter++;
				}
				break;
			}
		}
		else if (key == '\r')
		{
			if (counter == size - 1) break;
			system("cls");
			delegates_[counter]();
			_getch();
			system("cls");
		}

		set_color(Set, size, 7);

		if (counter >= 0 && counter < size)
		{
			Set[counter] = 4;
		}
	}
}
void Menu::add(delegate del, std::string name)
{
	delegates_.push_back(del);
	names_.push_back(name);
	size++;
}
void Menu::remove_at(int i)
{
	auto iter = delegates_.begin();

	while (iter != delegates_.end())
	{
		if (*iter == delegates_.at(i))
		{
			delegates_.erase(iter);
			break;
		}
		++iter;
	}
}
Menu::Menu() : size(0)
{
}
void Menu::gotoXY(int x, int y)
{
	COORD point;
	point.X = x;
	point.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

#pragma endregion
