#pragma once

#include <algorithm>
#include <unordered_map>
#include <memory>
#include <iostream>
#include <iomanip>
#include <string>
#include "Database.h"
#include "../src/Core/Coordinator.hpp"
#include "../src/Components/Components.hpp"
#include "../src/Menu.h"
#include "Users.h"

class Scene
{
private:
	std::unordered_map<Entity, std::string> mLivingEntities_;
	std::unique_ptr<Coordinator> mCoordinator_;
	std::vector<User> usersList_;
	static Scene* instance;
	Entity selectedEntity;
	Scene();
public:
	Scene(const Scene& other) = delete;
	Scene& operator=(const Scene& other) = delete;

	//Menu and other USER STUFF + register systems and components
	void start(User user);

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
	void select_component();

	void init_users();
	void show_users();
	void remove_user();
	void update_file();
	void sort_users_by_name();
	void filter_user_list();
	

	~Scene() = default;
};

bool user_compare(User first, User second);