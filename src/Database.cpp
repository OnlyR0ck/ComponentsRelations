//
// Created by guita on 12.04.2021.
//

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

bool Database::check_user(User& other)
{
	User user;
	std::ifstream fin(database_file, std::ios::binary);
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

	while(fin.good())
	{
		fin>>user;
		if(user==other)
		{

		}
	}

	return true;
}
bool Database::add_user(User& user)
{
	std::ofstream fout(database_file, std::ios::binary | std::ios::app);

	if (check_for_same_login(user))
	{
		std::cout << "Пользователь с таким именем уже существует!" << std::endl;
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

	user.set_password(Hash::hash_function(user.get_password()));
	fout << user;
	return true;
}
int Database::check_for_same_login(const User& other)
{
	User user;
	std::ifstream fin(database_file, std::ios::binary);
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
		return -1;
	}

	while (fin.good())
	{
		fin >> user;
		if (user == other)
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
