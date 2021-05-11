cmake_minimum_required(VERSION 3.17)
project(ComponentsRelations)

set(CMAKE_CXX_STANDARD 17)

add_executable(ComponentsRelations
        src/main.cpp
        src/Components/Components.hpp
        src/Users.cpp
        src/Users.h
        src/Database.cpp
        src/Database.h
        src/Menu.cpp
        src/Menu.h
        src/Math/Math.cpp
        src/Math/Math.h
        src/Core/Definitions.hpp
        src/Core/ComponentsManager.hpp
        src/Core/ComponentArray.hpp
        src/Core/EntityManager.hpp
        src/Core/Coordinator.hpp
        src/Core/System.hpp
        src/Core/SystemManager.hpp
        src/Scene.cpp
        src/Scene.h
        )