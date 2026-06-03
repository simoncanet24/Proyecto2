cmake_minimum_required(VERSION 4.2)
project(Proyecto2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proyecto2 main.cpp
        Inventario.cpp
        Inventario.h
        Jugador.cpp
        Jugador.h
        Objetos.cpp
        Objetos.h
        Enemigos.cpp
        Enemigos.h
        Reporte.cpp
        Reporte.h
        Bitacora.cpp
        Bitacora.h
        SistemaGeneral.cpp
        SistemaGeneral.h
        Archivos.cpp
        Archivos.h
)
target_include_directories(Proyecto2 PRIVATE include)

target_link_libraries(Proyecto2 winmm)
