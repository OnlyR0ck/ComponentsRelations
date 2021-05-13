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

}
