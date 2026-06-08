#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Player.h"
#include "Bitacora.h"
using namespace std;

class Reporte {
private:
    string file;

public:
    explicit Reporte(const string& filename) : file(filename) {}

    void generarReporte(const Jugador& jugador, const Bitacora& bitacora) const {
        ofstream f(file);
        if (!f.is_open())
            throw runtime_error("Error al abrir el archivo de reporte: " + file);

        f << "========================================\n";
        f << "       REPORTE FINAL DE LA PARTIDA      \n";
        f << "========================================\n";
        f << "Nombre del Jugador : " << jugador.getNombre()      << "\n";
        f << "Nivel              : " << jugador.getNivel()        << "\n";
        f << "Experiencia        : " << jugador.getExperiencia()  << "\n";
        f << "HP final           : " << jugador.getHp()           << "\n";
        f << "Ataque             : " << jugador.getAtaque()       << "\n";
        f << "Resultado          : " << (jugador.siguePartida() ? "Sobrevivio" : "Derrota") << "\n";
        f << "\n--- Bitacora de eventos ---\n";
        for (const auto& e : bitacora.getEventos())
            f << "  - " << e << "\n";
        f << "========================================\n";
    }
};
