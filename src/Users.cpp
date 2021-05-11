#include "Users.h"
User::User() : name("N/A"), password(nullptr), permissions(nothing)
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

std::ostream& operator<<(std::ostream& out, User& user)
{
	out << user.name;
	out << user.password;
	out << user.permissions;
	return out;
}
std::istream& operator>>(std::istream& in, User& user)
{
	int temp;
	in >> user.name;
	in >> user.password;
	in >> temp;
	user.permissions = static_cast<Permissions>(temp);
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
