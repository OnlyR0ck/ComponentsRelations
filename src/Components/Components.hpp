#pragma once


#ifndef COMPONENTSRELATIONS_SRC_COMPONENTS_H
#define COMPONENTSRELATIONS_SRC_COMPONENTS_H
#include "../Math/Math.h"

class IComponent
{
public:
	virtual void about() = 0;
	virtual void change_params() = 0;
};

class RigidBody : public IComponent
{
public:
	uint32_t mass = 1;
	bool isKinematic = false;
	bool useGravity = false;
	Math::Vector3 velocity;
	Math::Vector3 acceleration;
	
	void about() override;

	void change_params() override;
};

class Transform : public IComponent
{
public:
	Math::Vector3 position;
	Math::Vector3 rotation;
	Math::Vector3 scale;

	void about() override;
	void change_params() override;
};

class BoxCollider : public IComponent
{
public:
	Math::Vector3 center;
	Math::Vector3 size;

	void about() override;
	void change_params() override;
};

class MeshRenderer : public IComponent
{
public:
	Math::Vector3 color;

	void about() override;
	void change_params() override;
};

#endif //COMPONENTSRELATIONS_SRC_COMPONENTS_H
