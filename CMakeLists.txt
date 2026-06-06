cmake_minimum_required(VERSION 3.20)
project(Proyecto2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proyecto2
        main.cpp
        SistemaGeneral.h
        SistemaGeneral.cpp
        Jugador.h
        Jugador.cpp
        Enemigos.h
        Enemigos.cpp
        Objetos.h
        Objetos.cpp
        Inventario.h
        Inventario.cpp
        Bitacora.h
        Bitacora.cpp
        Archivos.h
        Archivos.cpp
        Reporte.h
        Reporte.cpp
        SistemaCombate.h
        SistemaCombate.cpp
)
