cmake_minimum_required(VERSION 4.2)
project(Proyecto2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proyecto2
        main.cpp
        Jugador.h
        Jugador.cpp
        Enemigo.h
        Enemigo.cpp
        Inventario.h
        Inventario.cpp
        Bitacora.h
        Bitacora.cpp
        Archivo.h
        Archivo.cpp
        Reporte.h
        Reporte.cpp
        SistemaCombate.cpp
        SistemaCombate.h
)