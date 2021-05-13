#pragma once

#include "Definitions.hpp"
#include <memory>

#include "ComponentsManager.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"

#include "Coordinator.hpp"
#include "../Components/Components.hpp"

class Coordinator
{
private:
	std::unique_ptr<Core::ComponentsManager> mComponentsManager;
	std::unique_ptr<Core::EntityManager> mEntityManager;
	std::unique_ptr<Core::SystemManager> mSystemManager;
	//std::unique_ptr<EventManager> mEventManager;
public:
	void init();

#pragma region Entity Methods

	Entity create_entity();
	bool destroy_entity(Entity entity);
	Signature get_entity_signature(Entity entity);

#pragma endregion 

#pragma region Component Methods

	template<class T>
	void register_component();

	template<class T>
	void add_component(Entity entity, T component);

	template <class T>
	void remove_component(Entity entity);

	template<class T>
	T& get_component(Entity entity);

	template<class T>
	ComponentType get_component_type();
#pragma endregion 

#pragma region System Methods

	template<class T>
	std::shared_ptr<T> register_system();

	template<class T>
	void set_system_signature(Signature signature);

#pragma endregion

};

inline void Coordinator::init()
{
	mComponentsManager = std::make_unique<Core::ComponentsManager>();
	mEntityManager = std::make_unique<Core::EntityManager>();
	mSystemManager = std::make_unique<Core::SystemManager>();

	//You need to register all of the used components!
	mComponentsManager->register_component<Transform>();
	mComponentsManager->register_component<RigidBody>();
	mComponentsManager->register_component<BoxCollider>();
	mComponentsManager->register_component<MeshRenderer>();

	//mEventManager = std::make_unique<Core::EventManager>();
}

inline Entity Coordinator::create_entity()
{
	return mEntityManager->create_entity();
}

inline bool Coordinator::destroy_entity(Entity entity)
{
	try
	{
		mEntityManager->destroy_entity(entity);
		mComponentsManager->entity_destroyed(entity);
		mSystemManager->entity_destroyed(entity);
	}
	catch (std::runtime_error& error)
	{
		std::cout << error.what() << std::endl;
		return false;
	}

	return true;
}

inline Signature Coordinator::get_entity_signature(Entity entity)
{
	return mEntityManager->get_signature(entity);
}

template<class T>
inline void Coordinator::register_component()
{
	mComponentsManager->register_component<T>();
}

template <class T>
void Coordinator::add_component(Entity entity, T component)
{
	mComponentsManager->add_component(entity, component);

	auto signature = mEntityManager->get_signature(entity);
	signature.set(mComponentsManager->get_component_type<T>(), true);
	mEntityManager->set_signature(entity, signature);

	mSystemManager->entity_signature_changed(entity, signature);
}

template <class T>
void Coordinator::remove_component(Entity entity)
{
	mComponentsManager->remove_component<T>(entity);

	auto signature = mEntityManager->get_signature(entity);
	signature.set(mComponentsManager->get_component_type<T>(), false);
	mEntityManager->set_signature(entity, signature);

	mSystemManager->entity_signature_changed(entity, signature);
}

template <class T>
T& Coordinator::get_component(Entity entity)
{
	return mComponentsManager->get_component<T>(entity);
}

template<class T>
inline ComponentType Coordinator::get_component_type()
{
	return mComponentsManager->get_component_type<T>();
}

template <class T>
std::shared_ptr<T> Coordinator::register_system()
{
	return mSystemManager->register_system<T>();
}

template<class T>
inline void Coordinator::set_system_signature(Signature signature)
{
	mSystemManager->set_signature<T>(signature);
}