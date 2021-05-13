//
// Created by guita on 01.05.2021.
//

#include "Math.h"


Math::Vector3::Vector3() : x(0), y(0), z(0)
{
}

Math::Vector3::Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z)
{
	
}

Math::Vector3::Vector3(const Vector3& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

Math::Vector3 Math::Vector3::normalized()
{
	const float length = sqrt(x * x + y * y + z * z);
	
	return Vector3(x / length, y / length, z / length);
}

Math::Vector3 Math::Vector3::forward()
{
	return Vector3(0, 0, 1);
}

Math::Vector3 Math::Vector3::up()
{
	return Vector3(0, -1, 0);
}

Math::Vector3 Math::Vector3::right()
{
	return Vector3(1, 0, 0);
}

Math::Vector3 Math::get_vector()
{
	Vector3 vector3(0,0,0);
	
	std::cout << "¬ведите x: ";
	std::cin >> vector3.x;
	std::cout << "¬ведите y: ";
	std::cin >> vector3.y;
	std::cout << "¬ведите z: ";
	std::cin >> vector3.z;

	return vector3;
}


std::ostream& Math::operator<<(std::ostream& out, Vector3& other)
{
	out << other.x;
	out << other.y;
	out << other.z;
	
	return out;
}

std::istream& Math::operator>>(std::istream& in, Vector3& other)
{
	in >> other.x;
	in >> other.y;
	in >> other.z;

	return in;
}
