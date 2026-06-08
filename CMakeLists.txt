cmake_minimum_required(VERSION 3.20)
project(Proyecto2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proyecto2
        main.cpp
        BaseEntity.h
        Player.h
        Enemy.h
        Item.h
        Inventory.h
        DataManager.h
        Encounter.cpp
        Encounter.h
        EncounterFactory.cpp
        EncounterFactory.h
        DataManager.cpp
)
