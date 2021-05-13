#pragma once

#include <array>
#include <exception>
#include <iostream>
#include <unordered_map>
#include "Definitions.hpp"

namespace Core
{
	class IComponentArray
	{
	public:
		virtual ~IComponentArray() = default;
		virtual void entity_destroyed(Entity entity) = 0;
	};

	template<class T>
	class ComponentArray : public IComponentArray
	{
	private:
		std::array<T, MAX_ENTITIES> mComponentsArray{};
		std::unordered_map<Entity, size_t> mEntity2IndexMap{};
		std::unordered_map<size_t, Entity> mIndex2EntityMap{};
		size_t mSize{};
	public:
		void insert_data(Entity entity, T component);
		void remove_data(Entity entity);
		T& get_data(Entity entity);
		void entity_destroyed(Entity entity) override;
	};

	template<class T>
	void ComponentArray<T>::insert_data(Entity entity, T component)
	{
		try
		{
			if (mEntity2IndexMap.find(entity) != mEntity2IndexMap.end())
			{
				throw std::runtime_error("Данный компонент уже был добален к сущности!");
			}
		}
		catch (std::runtime_error& error)
		{
			std::cout << error.what() << std::endl;
			return;
		}

		//Put a component at the end
		size_t newIndex = mSize;
		mEntity2IndexMap[entity] = newIndex;
		mIndex2EntityMap[newIndex] = entity;
		mComponentsArray[newIndex] = component;
		mSize++;
	}
	template<class T>
	void ComponentArray<T>::remove_data(Entity entity)
	{
		try
		{
			if (mEntity2IndexMap.find(entity) == mEntity2IndexMap.end())
			{
				throw std::runtime_error("Попытка удалить несуществующий компонент.");
			}
		}
		catch (std::runtime_error& error)
		{
			std::cout << error.what() << std::endl;
			return;
		}

		// Copy element at end into deleted element's place to maintain density
		size_t indexOfRemovedEnt = mEntity2IndexMap[entity];
		size_t indexOfLastEnt = mSize - 1;
		mComponentsArray[indexOfRemovedEnt] = mComponentsArray[indexOfLastEnt];

		//Update maps
		Entity lastEntity = mIndex2EntityMap[indexOfLastEnt];
		mEntity2IndexMap[lastEntity] = indexOfRemovedEnt;
		mIndex2EntityMap[indexOfRemovedEnt] = lastEntity;

		mEntity2IndexMap.erase(entity);
		mIndex2EntityMap.erase(indexOfLastEnt);
	}
	template<class T>
	T& ComponentArray<T>::get_data(Entity entity)
	{
		if (mEntity2IndexMap.find(entity) == mEntity2IndexMap.end())
		{
			throw std::runtime_error("Попытка получить несуществующий компонент.");
		}
		

		return mComponentsArray[mEntity2IndexMap[entity]];
	}
	template<class T>
	void ComponentArray<T>::entity_destroyed(Entity entity)
	{
		if(mEntity2IndexMap.find(entity) != mEntity2IndexMap.end()) remove_data(entity);
	}

}