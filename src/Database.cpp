#include "Database.h"

const char* database_file = "Database.txt";

Database::Database() = default;

Database* Database::instance = nullptr;

Database* Database::get_instance()
{
	if (instance == nullptr)
	{
		instance = new Database();
	}
	return instance;
}

bool Database::check_user(User & other)
{
	User user;

	std::ifstream fin(database_file);
	try
	{
		if (fin.fail())
		{
			throw std::runtime_error("Произошла ошибка открытия файла: ");
		}
	}
	catch (std::runtime_error& ex)
	{
		std::cout << ex.what() << database_file << std::endl;
		return false;
	}

	std::cout << other.get_name() << " " << other.get_password() << std::endl;
	while (fin.good())
	{
		fin >> user;
		std::cout << "Имя :" <<user.get_name() << " Хеш: " << user.get_password() << std::endl;
		if (user == other)
		{
			return true;
		}
	}

	return false;
}
bool Database::add_user(User & user)
{
	std::ofstream fout(database_file, std::ios::app);

	if (check_for_same_login(user))
	{
		std::cout << "Пользователь с данным именем уже зарегистрирован!" << std::endl;
		return false;
	}
	
	try
	{
		if (fout.fail())
		{
			throw std::runtime_error("Произошла ошибка открытия файла: ");
		}
	}
	catch (std::runtime_error& ex)
	{
		std::cout << ex.what() << database_file << std::endl;
		return false;
	}

	fout << user;
	return true;
}
int Database::check_for_same_login(const User & other)
{
	User user;
	
	std::ifstream fin(database_file);
	try
	{
		if (fin.fail())
		{
			throw std::runtime_error("Произошла ошибка открытия файла:  ");
		}
	}
	catch (std::runtime_error& ex)
	{
		std::cout << ex.what() << database_file << std::endl;
		return -1;
	}

	while (fin.good())
	{
		fin >> user;
		if (user.get_name() == other.get_name())
		{
			return 1;
		}
	}

	return 0;
}
std::string Hash::hash_function(const std::string& passwd)
{
	size_t hash = std::hash<std::string>{} (passwd);
	return std::to_string(hash);
}
