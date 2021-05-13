#include "Components.hpp"

void RigidBody::about()
{
	std::cout << "\nМасса: " << mass
		<< "\nСтатичен: " << isKinematic
		<< "\nИспользует гравитацию: " << useGravity << std::endl;

	printf("Скорость: Vector3(%f, %f, %f,)\n", velocity.x, velocity.y, velocity.z);
	printf("Ускорение: Vector3(%f, %f, %f,)\n", acceleration.x, acceleration.y, acceleration.z);

}

void RigidBody::change_params()
{
	std::cout << "Введите массу: ";
	std::cin >> mass;
	std::cout << "Объект статичен: ";
	std::cin >> isKinematic;
	std::cout << "Использует гравитацию: ";
	std::cin >> useGravity;
	std::cout << "Скорость (x, y, z): ";
	velocity = Math::get_vector();
	std::cout << "Ускорение (x, y, z): ";
	acceleration = Math::get_vector();
}

void Transform::about()
{
	printf("Позиция: Vector3(%f, %f, %f,)\n", position.x, position.y, position.z);
	printf("Угол поворота: Vector3(%f, %f, %f,)\n", rotation.x, rotation.y, rotation.z);
	printf("Размер: Vector3(%f, %f, %f,)\n", scale.x, scale.y, scale.z);

}

void Transform::change_params()
{
	std::cout << "Позиция (x, y, z): ";
	position = Math::get_vector();
	std::cout << "Угол поворота (x, y, z): ";
	rotation = Math::get_vector();
	std::cout << "Размер (x, y, z): ";
	scale = Math::get_vector();
}

void BoxCollider::about()
{
	printf("Центр: Vector3(%f, %f, %f,)\n", center.x, center.y, center.z);
	printf("Размер: Vector3(%f, %f, %f,)", size.x, size.y, size.z);
}

void BoxCollider::change_params()
{
	std::cout << "Координаты центра: \n";
	center = Math::get_vector();
	std::cout << "Размер: \n";
	size = Math::get_vector();
}

void MeshRenderer::about()
{
	printf("Цвет: RGB(%f, %f, %f,)", color.x, color.y, color.z);
}

void MeshRenderer::change_params()
{
	std::cout << "Введите цвет: \n";
	color = Math::get_vector();
}


