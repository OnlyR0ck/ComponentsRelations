#include "Scene.h"

Scene* Scene::instance = nullptr;

inline Scene::Scene()
{
	mCoordinator_ = std::make_unique<Coordinator>();
	mCoordinator_->init();
	instance = new Scene();
}

Scene* Scene::get_instance()
{
	if (instance == nullptr)instance = new Scene();

	return instance;
}

void Scene::show_entities()
{
	for (auto const& pair : mLivingEntities_)
	{
		const Entity entityID = pair.first;
		const char* entityName = pair.second;

		std::cout << "ID: " << entityID << ". " << entityName << std::endl;
	}
}

void Scene::create_entity()
{
	char* name = nullptr;

	std::cout << "Введите название сущности: ";
	std::cin >> name;

	Entity entity = mCoordinator_->create_entity();
	
	if (entity != -1)
	{
		mLivingEntities_.insert({ entity,name });
	}
	else
	{
		std::cout << "Ошибка создания сущности." << std::endl;
	}
}

void Scene::select_entity()
{
	Menu entityMenu;

	show_entities();

	std::cout << "\nВведите ID сущности: ";
	std::cin >> selectedEntity;

	if (mLivingEntities_.find(selectedEntity) == mLivingEntities_.end())
	{
		std::cout << "Сущности с таким ID не существует." << std::endl;
		return;
	}

	entityMenu.add([] {instance->add_component(); }, "Добавить компонент.");
	entityMenu.add([] {instance->remove_component(); }, "Удалить компонент.");
	entityMenu.add([] {instance->show_components(); }, "Просмотреть компоненты.");
	entityMenu.add([] {instance->rename_entity(); }, "Переименовать сущность.");
}

void Scene::remove_entity()
{
	Entity entity;

	show_entities();

	std::cout << "\nВведите ID сущности для удаления: ";
	std::cin >> entity;

	if (mCoordinator_->destroy_entity(entity))
	{
		std::cout << "Сущность с ID: " << entity << " успешно удалена." << std::endl;
	}
}

Signature Scene::get_entity_signature()
{
	return mCoordinator_->get_entity_signature(selectedEntity);
}

void Scene::rename_entity()
{
	char* newName = nullptr;

	std::cout << "Введите новое имя сущности: ";
	std::cin >> newName;

	auto nodeHandler = mLivingEntities_.extract(selectedEntity);
	nodeHandler.mapped() = newName;

	mLivingEntities_.insert(std::move(nodeHandler));
}

void Scene::show_components()
{
	int count = 0;
	Signature signature = mCoordinator_->get_entity_signature(selectedEntity);

	ComponentType componentType = mCoordinator_->get_component_type<Transform>();

	if (signature[componentType] == 1)
	{
		std::cout << ++count << ". Transform." << std::endl;
	}

	componentType = mCoordinator_->get_component_type<RigidBody>();

	if (signature[componentType] == 1)
	{
		std::cout << ++count << ". Rigidbody." << std::endl;
	}

	componentType = mCoordinator_->get_component_type<BoxCollider>();

	if (signature[componentType] == 1)
	{
		std::cout << ++count << ". BoxCollider." << std::endl;
	}

	componentType = mCoordinator_->get_component_type<MeshRenderer>();

	if (signature[componentType] == 1)
	{
		std::cout << ++count << ". MeshRenderer." << std::endl;
	}
}

void Scene::add_component()
{
	int count = 0;
	Menu menu;

	menu.add([]
		{
			instance->mCoordinator_->add_component(get_instance()->selectedEntity, Transform {});

		}, "Добавить Transform.");

	menu.add([]
		{
			instance->mCoordinator_->add_component(get_instance()->selectedEntity, RigidBody {});

		}, "Добавить Rigidbody.");

	menu.add([]
		{
			instance->mCoordinator_->add_component(get_instance()->selectedEntity, BoxCollider {});

		}, "Добавить BoxCollider.");

	menu.add([]
		{
			instance->mCoordinator_->add_component(get_instance()->selectedEntity, MeshRenderer {});

		}, "Добавить MeshRenderer.");

	menu.start();
}

void Scene::remove_component()
{
	Menu menu;

	int count = 0;
	Signature signature = mCoordinator_->get_entity_signature(selectedEntity);

	ComponentType componentType = mCoordinator_->get_component_type<Transform>();

	if (signature[componentType] == 1)
	{
		menu.add([]
			{
				instance->mCoordinator_->remove_component<Transform>(instance->selectedEntity);

			}, "Удалить Transform.");
	}

	componentType = mCoordinator_->get_component_type<RigidBody>();

	if (signature[componentType] == 1)
	{
		menu.add([]
			{
				instance->mCoordinator_->remove_component<RigidBody>(instance->selectedEntity);

			}, "Удалить Rigidbody.");
	}

	componentType = mCoordinator_->get_component_type<BoxCollider>();

	if (signature[componentType] == 1)
	{
		menu.add([]
			{
				instance->mCoordinator_->remove_component<BoxCollider>(instance->selectedEntity);

			}, "Удалить BoxCollider.");
	}

	componentType = mCoordinator_->get_component_type<MeshRenderer>();

	if (signature[componentType] == 1)
	{
		menu.add([]
			{
				instance->mCoordinator_->remove_component<MeshRenderer>(instance->selectedEntity);

			}, "Удалить MeshRenderer.");
	}

	menu.start();
}
