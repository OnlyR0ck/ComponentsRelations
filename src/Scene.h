#pragma once

#include <unordered_map>
#include <memory>
#include "../src/Core/Coordinator.hpp"
#include "../src/Components/Components.hpp"
#include "../src/Menu.h"
#include <iomanip>

class Scene
{
private:
	std::unordered_map<Entity, const char*> mLivingEntities_;
	std::unique_ptr<Coordinator> mCoordinator_;
	static Scene* instance;
	Entity selectedEntity;
	Scene();
public:
	Scene(const Scene& other) = delete;
	Scene& operator=(const Scene& other) = delete;

	//Menu and other USER STUFF + register systems and components
	void start();

	static Scene* get_instance();

	void show_entities();
	void create_entity();
	void select_entity();
	void remove_entity();
	Signature get_entity_signature();
	void rename_entity();

	void show_components();
	void add_component();
	void remove_component();

	~Scene() = default;
};