#include "EntityManager.hpp"

using namespace Core;

EntityManager::EntityManager() : mLivingEntityCount(0)
{
	for (Entity entity = 0; entity < MAX_ENTITIES; entity++)
	{
		mAvailableEntities.push(entity);
	}
}
Entity EntityManager::create_entity()
{
	try
	{
		if (mLivingEntityCount > MAX_ENTITIES)
		{
			throw std::runtime_error("Превышено максимальное количество сущностей.");
		}
	}
	catch (std::runtime_error& error)
	{
		std::cout << error.what() << std::endl;
		return -1;
	}

	Entity id = mAvailableEntities.front();
	mAvailableEntities.pop();
	mLivingEntityCount++;

	return id;
}
void EntityManager::destroy_entity(Entity entity)
{
	try
	{
		if (entity > MAX_ENTITIES)
		{
			throw std::out_of_range("Превышено максимальное количество сущностей.");
		}
	}
	catch (std::out_of_range& error)
	{
		throw error;
	}

	mSignatures[entity].reset();
	mAvailableEntities.push(entity);
	mLivingEntityCount--;
}
void EntityManager::set_signature(Entity entity, Signature signature)
{
	try
	{
		if (entity > MAX_ENTITIES)
		{
			throw std::out_of_range("ID сущности вне диапазона.");
		}
	}
	catch (std::out_of_range& error)
	{
		std::cout << error.what() << std::endl;
		return;
	}

	mSignatures[entity] = signature;
}
Signature EntityManager::get_signature(Entity entity)
{
	try
	{
		if (entity > MAX_ENTITIES)
		{
			throw std::out_of_range("ID сущности вне диапазона.");
		}
	}
	catch (std::out_of_range& error)
	{
		std::cout << error.what() << std::endl;
		return NULL;
	}

	return mSignatures[entity];
}