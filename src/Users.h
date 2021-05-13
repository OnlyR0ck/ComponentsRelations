#pragma once

#include <string>
#include <iostream>
#ifndef COMPONENTSRELATIONS_SRC_USERS_H
#define COMPONENTSRELATIONS_SRC_USERS_H

enum Permissions
{
	admin = 0,
	quest = 1,
	nothing = 2
};
class User
{
private:
	std::string name;
	std::string password;
	Permissions permissions;
public:
	User();
	User(const User& other);
	std::string get_name() const;
	void set_name(std::string name);
	std::string get_password() const;
	void set_password(const std::string &password);
	void set_permissions(Permissions permissions);
	Permissions get_permissions();
	bool operator==(const User& other);
	friend std::ostream& operator<<(std::ostream&out, User& user);
	friend std::istream& operator>>(std::istream& in, User& user);
};



#endif //COMPONENTSRELATIONS_SRC_USERS_H
