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

	std::cout << "������� �������� ��������: ";
	std::cin >> name;

	Entity entity = mCoordinator_->create_entity();
	
	if (entity != -1)
	{
		mLivingEntities_.insert({ entity,name });
	}
	else
	{
		std::cout << "������ �������� ��������." << std::endl;
	}
}

void Scene::select_entity()
{
	Menu entityMenu;

	show_entities();

	std::cout << "\n������� ID ��������: ";
	std::cin >> selectedEntity;

	if (mLivingEntities_.find(selectedEntity) == mLivingEntities_.end())
	{
		std::cout << "�������� � ����� ID �� ����������." << std::endl;
		return;
	}

	entityMenu.add([] {instance->add_component(); }, "�������� ���������.");
	entityMenu.add([] {instance->remove_component(); }, "������� ���������.");
	entityMenu.add([] {instance->show_components(); }, "����������� ����������.");
	entityMenu.add([] {instance->rename_entity(); }, "������������� ��������.");
}

void Scene::remove_entity()
{
	Entity entity;

	show_entities();

	std::cout << "\n������� ID �������� ��� ��������: ";
	std::cin >> entity;

	if (mCoordinator_->destroy_entity(entity))
	{
		std::cout << "�������� � ID: " << entity << " ������� �������." << std::endl;
	}
}

Signature Scene::get_entity_signature()
{
	return mCoordinator_->get_entity_signature(selectedEntity);
}

void Scene::rename_entity()
{
	char* newName = nullptr;

	std::cout << "������� ����� ��� ��������: ";
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

		}, "�������� Transform.");

	menu.add([]
		{
			instance->mCoordinator_->add_component(get_instance()->selectedEntity, RigidBody {});

		}, "�������� Rigidbody.");

	menu.add([]
		{
			instance->mCoordinator_->add_component(get_instance()->selectedEntity, BoxCollider {});

		}, "�������� BoxCollider.");

	menu.add([]
		{
			instance->mCoordinator_->add_component(get_instance()->selectedEntity, MeshRenderer {});

		}, "�������� MeshRenderer.");

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

			}, "������� Transform.");
	}

	componentType = mCoordinator_->get_component_type<RigidBody>();

	if (signature[componentType] == 1)
	{
		menu.add([]
			{
				instance->mCoordinator_->remove_component<RigidBody>(instance->selectedEntity);

			}, "������� Rigidbody.");
	}

	componentType = mCoordinator_->get_component_type<BoxCollider>();

	if (signature[componentType] == 1)
	{
		menu.add([]
			{
				instance->mCoordinator_->remove_component<BoxCollider>(instance->selectedEntity);

			}, "������� BoxCollider.");
	}

	componentType = mCoordinator_->get_component_type<MeshRenderer>();

	if (signature[componentType] == 1)
	{
		menu.add([]
			{
				instance->mCoordinator_->remove_component<MeshRenderer>(instance->selectedEntity);

			}, "������� MeshRenderer.");
	}

	menu.start();
}
