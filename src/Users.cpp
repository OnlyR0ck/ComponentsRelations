#include "Users.h"
User::User() : name("N/A"), password("N/A"), permissions(nothing)
{

}
User::User(const User& other)
{
	this->name = other.name;
	this->password = other.password;
	this->permissions = other.permissions;
}
std::string User::get_name() const
{
	return name;
}
void User::set_name(std::string name)
{
	this->name = name;
}
std::string User::get_password() const
{
	return password;
}
void User::set_password(const std::string& password)
{
	this->password = password;
}

void User::set_permissions(Permissions permissions)
{
	this->permissions = permissions;
}

Permissions User::get_permissions()
{
	return permissions;
}

std::ostream& operator<<(std::ostream& out, User& user)
{
	out << user.name;
	out << '|';
	out << user.password;
	out << '|';
	out << user.permissions;
	out << '|';
	
	return out;
}
std::istream& operator>>(std::istream& in, User& user)
{
	std::string temp;
	std::getline(in, user.name, '|');
	std::getline(in, user.password, '|');
	std::getline(in, temp, '|');
	user.permissions = static_cast<Permissions>(atoi(temp.c_str()));
	return in;
}
bool User::operator==(const User& other)
{
	if (this->name == other.name && this->password == other.password)
	{
		return true ;
	}

	return false;
}