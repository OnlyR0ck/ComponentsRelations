#include "Menu.h"
#include "Scene.h"
#include "Database.h"


void sign_up();
void sign_in();

int main()
{
	Menu menu;
	menu.add(sign_up, "������������������.");
	menu.add(sign_in, "�����.");
	menu.start();
	return 0;
}

void sign_up()
{
	Database* database = Database::get_instance();
	User user;
	std::string temp;

	std::cout << "������� ��� ������������: ";
	std::cin >> temp;
	user.set_name(temp);

	std::cout << "\n������� ������: ";
	std::cin >> temp;
	user.set_password(temp);
	database->add_user(user);
}

void sign_in()
{
	Database* database = Database::get_instance();
	User user;
	std::string temp;

	std::cout << "������� ��� ������������: ";
	std::cin >> temp;
	user.set_name(temp);

	std::cout << "\n������� ������: ";
	std::cin >> temp;
	user.set_password(temp);

	if(database->check_user(user))
	{
		//Need to share user and check permissions
		//Scene::get_instance()->start();
		std::cout << "Sign in successfully" << std::endl;
	}
}
