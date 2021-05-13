#pragma once

#include "Definitions.hpp"
#include "System.hpp"
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <iostream>

namespace Core
{


	class SystemManager
	{
	private:
		std::unordered_map<const char*, Signature> mSignatures;
		std::unordered_map<const char*, std::shared_ptr<System> > mSystems{};
	public:
		template<class T>
		std::shared_ptr<T> register_system();

		template<class T >
		void set_signature(Signature signature);

		void entity_destroyed(Entity entity);

		void entity_signature_changed(Entity entity, Signature entitySignature);
	};

	inline void SystemManager::entity_destroyed(Entity entity)
	{
		for (auto const& pair : mSystems)
		{
			auto const& system = pair.second;

			system->mEntities.erase(entity);
		}
	}

	inline void SystemManager::entity_signature_changed(Entity entity, Signature entitySignature)
	{
		for (auto const& pair : mSystems)
		{
			auto const& type = pair.first;
			auto const& system = pair.second;
			auto const& systemSignature = mSignatures[type];

			if ((entitySignature & systemSignature) == systemSignature)
			{
				system->mEntities.insert(entity);
			}
			else
			{
				system->mEntities.erase(entity);
			}
		}
	}

	template <class T>
	std::shared_ptr<T> SystemManager::register_system()
	{
		const char* typeName = typeid(T).name();

		try
		{
			if (mSystems.find(typeName) == mSystems.end())
			{
				throw std::runtime_error("Система уже зарегистрирована.");
			}
		}
		catch (std::runtime_error& error)
		{
			std::cout << error.what() << std::endl;
			return nullptr;
		}

		auto system = std::make_shared<T>();
		mSystems.insert({ typeName, system });
		return system;
	}

	template <class T>
	void SystemManager::set_signature(Signature signature)
	{
		const char* typeName = typeid(T).name();

		try
		{
			if (mSystems.find(typeName) != mSystems.end())
			{
				throw std::runtime_error("Использование системы до её регистрации.");
			}
		}
		catch (std::runtime_error& error)
		{
			std::cout << error.what() << std::endl;
			return;
		}

		mSignatures.insert({ typeName, signature });
	}


}
