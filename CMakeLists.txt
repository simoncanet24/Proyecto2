cmake_minimum_required(VERSION 3.20)
project(Proyecto2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proyecto2
        main.cpp
        BaseEntity.h
        BaseEntity.cpp
        Player.h
        Player.cpp
        Enemy.h
        Enemy.cpp
        Item.h
        Item.cpp
        Inventory.h
        Inventory.cpp
        Bitacora.h
        Bitacora.cpp
        Archivos.h
        Archivos.cpp
        Reporte.h
        Reporte.cpp
        SistemaCombate.h
        SistemaCombate.cpp
)
