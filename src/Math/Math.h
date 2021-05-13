#pragma once

#include <iostream>

namespace Math
{
	const float PI = 3.14159265;

	class Vector3
	{
	public:
		float x;
		float y;
		float z;
		
		Vector3();
		Vector3(float x, float y, float z);
		Vector3(const Vector3& other);
		
		Vector3 normalized();
		static Vector3 forward();
		static Vector3 up();
		static Vector3 right();
		friend std::ostream& operator<<(std::ostream& out, Vector3& other);
		friend std::istream& operator>>(std::istream& in, Vector3& other);
	};

	class Quaternion
	{
	private:
		float x;
		float y;
		float z;
		float w;
	public:
		Quaternion() : x(0),y(0),z(0), w(0) {}
		Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
		Quaternion(const Quaternion& other);
		Quaternion& operator=(const Quaternion& other);
		static Quaternion& identity();
		static Vector3& to_euler_angles(const Quaternion& other);
		friend std::ostream & operator<<(std::ostream& out, Quaternion& quaternion);
		friend std::istream & operator>>(std::istream& in, Quaternion& quaternion);

	};

	class Vector2
	{
	private:
		float x;
		float y;
	public :
		Vector2() : x(0), y(0){	}
		Vector2(float x, float y) : x(x), y(y){	}
		Vector2(const Vector3& other);
		Vector2(const Vector2& other);
		Vector2 normalized();
		static Vector2& up();
		static Vector2& down();
		static Vector2& left();
		static Vector2& right();
		Vector2 operator=(const Vector2& other);
		Vector2 operator=(const Vector3& other);
		friend std::ostream& operator<<(std::ostream& out, Vector2& other);
		friend std::istream& operator>>(std::istream& in, Vector2& other);
	};

	Vector3 get_vector();

}