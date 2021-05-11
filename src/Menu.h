#pragma once

#ifndef COMPONENTSRELATIONS_SRC_MENU_H
#define COMPONENTSRELATIONS_SRC_MENU_H
#include <vector>
#include <conio.h>
#include <windows.h>
#include <iostream>

typedef void (*delegate)();

class Menu
{
private:
	int size;
	std::vector<delegate> delegates_;
	std::vector<std::string> names_;

	void color(int color);
	void set_color(int *, int, int );
	void gotoXY(int, int);
public:
	Menu();
	Menu(const Menu& other) = delete;
	Menu& operator=(const Menu& other) = delete;
	void start();
	void add(delegate, std::string name);
	void remove_at(int i);
};

#endif //COMPONENTSRELATIONS_SRC_MENU_H
