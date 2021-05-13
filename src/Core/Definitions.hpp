#pragma once

#include<bitset>
#include <cstdint>

#pragma region file constants

inline const char* component_arrays = "ComponentArrays.txt";
inline const char* registered_components = "RegisteredComponents.txt";
inline const char* signatures = "signatures.txt";

#pragma endregion 

#pragma region ECS

using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 1000;
using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_ENTITIES>;

#pragma endregion 