#include "Scene.h"

Scene* Scene::instance = nullptr;

inline Scene::Scene() = default;

void Scene::start(User user)
{
	mCoordinator_ = std::make_unique<Coordinator>();
	mCoordinator_->init();

	Menu menu;

	menu.add([] {instance->create_entity(); }, "Создать сущность.");
	menu.add([] {instance->show_entities(); }, "Просмотреть сущности.");
	menu.add([] {instance->select_entity(); }, "Выбрать сущность.");
	menu.add([] {instance->remove_entity(); }, "Удалить сущность.");

	if(user.get_permissions() == admin)
	{
		init_users();
		menu.add([] {instance->show_users(); }, "Показать всех пользователей.");
		menu.add([] {instance->remove_user(); }, "Удалить пользователя.");
		menu.add([] {instance->sort_users_by_name(); }, "Отсортировать в алфавитном порядке.");
		menu.add([] {instance->filter_user_list(); }, "Фильтрация пользователей по первой букве.");
	}

	menu.start();
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
		const Entity entity_id = pair.first;
		std::string entity_name = pair.second;

		std::cout << "ID: " << entity_id << ". " << entity_name << std::endl;
	}
}

void Scene::create_entity()
{
	std::string name;

	std::cout << "Введите имя сущности: ";
	std::cin >> name;
	Entity entity = mCoordinator_->create_entity();

	if (entity != -1)
	{
		mLivingEntities_.insert({ entity,name });
	}
	else
	{
		std::cout << "Не удалось создать сущность." << std::endl;
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
		std::cout << "Сущность с данным ID не зарегистрирована." << std::endl;
		return;
	}

	entityMenu.add([] {instance->add_component(); }, "Добавить компонент.");
	entityMenu.add([] {instance->remove_component(); }, "Удалить компонент.");
	entityMenu.add([] {instance->show_components(); }, "Показать компоненты.");
	entityMenu.add([] {instance->select_component(); }, "Выбрать компонент.");
	entityMenu.add([] {instance->rename_entity(); }, "Переименовать сущность.");

	entityMenu.start();
}

void Scene::remove_entity()
{
	Entity entity;

	show_entities();

	std::cout << "\nВведите ID сущности для удаления: ";
	std::cin >> entity;

	if (mLivingEntities_.find(entity) == mLivingEntities_.end())
	{
		std::cout << "Сущности с данным ID не существует" << std::endl;
	}

	if (mCoordinator_->destroy_entity(entity))
	{
		std::cout << "Сущность с ID: " << entity << " успешно уничтожена." << std::endl;
		mLivingEntities_.erase(entity);
	}
}

Signature Scene::get_entity_signature()
{
	return mCoordinator_->get_entity_signature(selectedEntity);
}

void Scene::rename_entity()
{
	std::string newName;

	std::cout << "Введите новое имя сущности: ";
	std::cin >> newName;

	auto nodeHandler = mLivingEntities_.extract(selectedEntity);
	nodeHandler.mapped() = newName.c_str();

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

void Scene::select_component()
{
	Menu menu;

	Signature signature = mCoordinator_->get_entity_signature(selectedEntity);

	ComponentType componentType = mCoordinator_->get_component_type<Transform>();

	if (signature[componentType] == 1)
	{
		menu.add([]
			{
				Menu cMenu;

				cMenu.add([]
					{

						instance->mCoordinator_->get_component<Transform>(instance->selectedEntity).about();

					}, "Вывести информацию о полях компонента.");

				cMenu.add([]
					{

						instance->mCoordinator_->get_component<Transform>(instance->selectedEntity).change_params();

					}, "Изменить поля компонента.");

				cMenu.start();

			}, "Transform.");

	}

	componentType = mCoordinator_->get_component_type<RigidBody>();

	if (signature[componentType] == 1)
	{
		menu.add([]
			{
				Menu cMenu;

				cMenu.add([]
					{

						instance->mCoordinator_->get_component<RigidBody>(instance->selectedEntity).about();

					}, "Вывести информацию о полях компонента.");

				cMenu.add([]
					{

						instance->mCoordinator_->get_component<RigidBody>(instance->selectedEntity).change_params();

					}, "Изменить поля компонента.");

				cMenu.start();

			}, "Rigidbody.");
	}

	componentType = mCoordinator_->get_component_type<BoxCollider>();

	if (signature[componentType] == 1)
	{
		menu.add([]
			{
				Menu cMenu;

				cMenu.add([]
					{

						instance->mCoordinator_->get_component<BoxCollider>(instance->selectedEntity).about();

					}, "Вывести информацию о полях компонента.");

				cMenu.add([]
					{

						instance->mCoordinator_->get_component<BoxCollider>(instance->selectedEntity).change_params();

					}, "Изменить поля компонента.");

				cMenu.start();

			}, "BoxCollider.");
	}

	componentType = mCoordinator_->get_component_type<MeshRenderer>();

	if (signature[componentType] == 1)
	{
		menu.add([]
			{
				Menu cMenu;

				cMenu.add([]
					{

						instance->mCoordinator_->get_component<MeshRenderer>(instance->selectedEntity).about();

					}, "Вывести информацию о полях компонента.");

				cMenu.add([]
					{

						instance->mCoordinator_->get_component<MeshRenderer>(instance->selectedEntity).change_params();

					}, "Изменить поля компонента.");

				cMenu.start();

			}, "MeshRenderer.");
	}

	menu.start();
}

void Scene::init_users()
{
	User user;
	
	std::ifstream fin(database_file);
	try
	{
		if (fin.fail())
		{
			throw std::runtime_error("Произошла ошибка открытия файла:  ");
		}
	}
	catch (std::runtime_error& ex)
	{
		std::cout << ex.what() << database_file << std::endl;
		return;
	}


	while (fin.good())
	{
		fin >> user;
		usersList_.push_back(user);
	}
}


void Scene::show_users()
{		
	for (auto const& i : usersList_)
	{
		printf("Логин: %s Пароль(хеш): %s\n", i.get_name().c_str(), i.get_password().c_str());
	}
}

void Scene::remove_user()
{
	std::string name;
	show_users();

	std::cout << "Введите имя пользователя: ";
	std::cin >> name;

	for (auto i = usersList_.begin(); i != usersList_.end(); ++i)
	{
		if (i->get_name() == name)
		{
			usersList_.erase(i);
			std::cout << "Удаление выполнено успешно!" << std::endl;

			update_file();
			
			return;
		}
	}

	std::cout << "Пользователя с таким логином не существует" << std::endl;
}

void Scene::update_file()
{
	std::ofstream fout(database_file, std::ios::trunc);

	if(fout.bad())
	{
		throw std::runtime_error("Ошибка открытия файла базы данных!");
	}
	
	for(auto&  i : usersList_)
	{
		fout << i;
	}
}

void Scene::sort_users_by_name()
{
	std::sort(usersList_.begin(), usersList_.end(), user_compare);
	show_users();
}

void Scene::filter_user_list()
{
	char character;
	std::cout << "Вывести пользователей на букву: ";
	std::cin.ignore(100, '\n');
	std::cin.get(character);

	for(auto const& i : usersList_)
	{
		if(i.get_name()[0] == character)
		{
			printf("Логин: %s Пароль(хеш): %s\n", i.get_name().c_str(), i.get_password().c_str());
		}
	}
}

bool user_compare(User first, User second)
{
	if (std::strcmp(first.get_name().c_str(), second.get_name().c_str()) < 0) return true;
	return false;
}
