#pragma once

#ifndef COMPONENTSRELATIONS_SRC_DATABASE_H
#define COMPONENTSRELATIONS_SRC_DATABASE_H

#include <string>
#include <fstream>
#include <iostream>
#include <functional>
#include <memory>
#include "Users.h"
extern const char* database_file;

class Database
{
private:
	static Database *instance;
	static int check_for_same_login(const User& other);
	Database();
public:
	bool check_user(User& user);
	bool add_user(User& user);
	static Database* get_instance();
	Database(const Database& other) = delete;
	void operator=(const Database&) = delete;
};

class Hash
{
public:
	static std::string hash_function(const std::string &password);
};

#endif //COMPONENTSRELATIONS_SRC_DATABASE_H
