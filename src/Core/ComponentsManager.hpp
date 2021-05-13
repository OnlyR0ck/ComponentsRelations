#pragma once

#ifndef COMPONENTSRELATIONS_SRC_CORE_COMPONENTSMANAGER_HPP
#define COMPONENTSRELATIONS_SRC_CORE_COMPONENTSMANAGER_HPP

#include <unordered_map>
#include <memory>
#include "Definitions.hpp"
#include "ComponentArray.hpp"

namespace Core
{


	class ComponentsManager
	{
	private:
		std::unordered_map<const char*, ComponentType> mComponentTypes{};
		std::unordered_map<const char*, std::shared_ptr<Core::IComponentArray>> mComponentArrays{};
		ComponentType mNextComponentType = 0;
		template<class T>
		std::shared_ptr<Core::ComponentArray<T>> get_component_array();
	public:
		template<class T>
		void register_component();

		template<class T>
		ComponentType get_component_type();

		template<class T>
		void add_component(Entity entity, T component);

		template<class T>
		void remove_component(Entity entity);

		template<class T>
		T& get_component(Entity entity);

		void entity_destroyed(Entity entity);
	};

	inline void ComponentsManager::entity_destroyed(Entity entity)
	{
		for (auto const& pair : mComponentArrays)
		{
			pair.second->entity_destroyed(entity);
		}
	}

	template <class T>
	std::shared_ptr<Core::ComponentArray<T>> ComponentsManager::get_component_array()
	{
		const char* typeName = typeid(T).name();

		try
		{
			if (mComponentTypes.find(typeName) == mComponentTypes.end())
			{
				throw std::runtime_error("Компонент не был зарегистрирован перед использованием.");
			}
		}
		catch (std::runtime_error& error)
		{
			std::cout << error.what() << std::endl;
		}

		return std::static_pointer_cast<Core::ComponentArray<T>>(mComponentArrays[typeName]);
	}

	template <class T>
	void ComponentsManager::register_component()
	{
		const char* typeName = typeid(T).name();
		try
		{
			if (mComponentTypes.find(typeName) != mComponentTypes.end())
			{
				throw std::runtime_error("Компонент уже был зарегистрирован.");
			}
		}
		catch (std::runtime_error& error)
		{
			std::cout << error.what() << std::endl;
		}


		mComponentTypes.insert({ typeName, mNextComponentType });
		mComponentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

		++mNextComponentType;
	}

	template <class T>
	ComponentType ComponentsManager::get_component_type()
	{
		const char* typeName = typeid(T).name();

		try
		{
			if (mComponentTypes.find(typeName) == mComponentTypes.end())
			{
				throw std::runtime_error("Компонент не был зарегистрирован перед использованием.");
			}
		}
		catch (std::runtime_error& error)
		{
			std::cout << error.what() << std::endl;
		}

		return mComponentTypes[typeName];
	}

	template <class T>
	void ComponentsManager::add_component(Entity entity, T component)
	{
		get_component_array<T>()->insert_data(entity, component);
	}

	template <class T>
	void ComponentsManager::remove_component(Entity entity)
	{
		get_component_array<T>()->remove_data(entity);
	}

	template <class T>
	T& ComponentsManager::get_component(Entity entity)
	{
		try
		{
			return get_component_array<T>()->get_data(entity);
		}
		catch (std::runtime_error& error)
		{
			std::cout << error.what() << std::endl;
		}
	}

}
#endif //COMPONENTSRELATIONS_SRC_CORE_COMPONENTSMANAGER_HPP