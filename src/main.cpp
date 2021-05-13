#include "Menu.h"
#include "Scene.h"
#include "Database.h"
#include <pchannel.h>
#include <iostream>

void sign_up();
void sign_in();

int main()
{
	SetConsoleCP(866);
	SetConsoleOutputCP(866);

	Menu menu;
	menu.add(sign_up, "Зарегистрироваться.");
	menu.add(sign_in, "Войти.");
	menu.start();
	return 0;
}

void sign_up()
{
	Database* database = Database::get_instance();
	User user;
	std::string temp;

	std::cout << "Введите имя пользователя: ";
	std::cin >> temp;
	user.set_name(temp);

	std::cout << "\nВведите пароль: ";
	std::cin >> temp;
	user.set_password(temp);
	user.set_password(Hash::hash_function(user.get_password()));
	database->add_user(user);
}

void sign_in()
{
	Database* database = Database::get_instance();
	User user;
	std::string temp;

	std::cout << "Введите имя пользователя: ";
	std::cin >> temp;
	user.set_name(temp);

	std::cout << "\nВведите пароль: ";
	std::cin >> temp;
	user.set_password(temp);
	if (user.get_name() == "admin" && user.get_password() == "admin")
	{
		user.set_permissions(admin);
		Scene::get_instance()->start(user);
		return;
	}
	
	user.set_password(Hash::hash_function(user.get_password()));

	if (database->check_user(user))
	{
		std::cout << "Sign in successfully" << std::endl;
		//Need to share user and check permissions
		Scene::get_instance()->start(user);
	}
}
