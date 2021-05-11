#pragma once

#include <queue>
#include <array>
#include <iostream>
#include "Definitions.hpp"

namespace Core
{
	class EntityManager
	{
	private:
		std::queue<Entity> mAvailableEntities{};
		std::array<Signature, MAX_ENTITIES> mSignatures{};
		uint32_t mLivingEntityCount;
	public:
		EntityManager();
		EntityManager(const EntityManager& other) = delete;
		Entity create_entity();
		void destroy_entity(Entity entity);
		void set_signature(Entity entity, Signature signature);
		Signature get_signature(Entity entity);
		EntityManager& operator=(const EntityManager& entityManager) = delete;

	};
	
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
			if (mLivingEntityCount >= MAX_ENTITIES)
			{
				throw std::runtime_error("Невозможно создать сущность. Превышен максимальный лимит.");
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
			if (entity < MAX_ENTITIES)
			{
				throw std::out_of_range("Сущности с данным идентификатором не существует");
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
			if (entity < MAX_ENTITIES)
			{
				throw std::out_of_range("Сущности с данным идентификатором не существует");
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
			if (entity < MAX_ENTITIES)
			{
				throw std::out_of_range("Сущности с данным идентификатором не существует");
			}
		}
		catch (std::out_of_range& error)
		{
			std::cout << error.what() << std::endl;
			return NULL;
		}

		return mSignatures[entity];
	}

}
