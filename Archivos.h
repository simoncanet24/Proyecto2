#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Jugador.h"
#include "Enemigos.h"
#include "Objetos.h"
#include "Inventario.h"
using namespace std;

// Formato jugador.txt:
//   nombre|hp|ataque
//   Ejemplo: Kai|100|10
//
// Formato enemigos.txt (una linea por enemigo):
//   nombre|hp|ataque|exp
//   Ejemplo: Lobo|40|8|20
//
// Formato objetos.txt (una linea por objeto):
//   nombre|descripcion|sanacion
//   Ejemplo: Pocion|Recupera vida|30

class Archivos {
public:
    // Carga el jugador desde archivo. Si falla, devuelve uno por defecto.
    static Jugador* descargarJugador(const string& filename) {
        ifstream f(filename);
        auto* inv = new Inventario<Objetos*>(5);

        if (!f.is_open()) {
            cerr << "[Archivos] No se encontro " << filename
                 << ". Se usara jugador por defecto.\n";
            return new Jugador("Heroe", 100, 10, inv);
        }

        string linea;
        if (getline(f, linea)) {
            istringstream ss(linea);
            string nombre, hpStr, atkStr;
            if (getline(ss, nombre, '|') &&
                getline(ss, hpStr,  '|') &&
                getline(ss, atkStr, '|'))
            {
                return new Jugador(nombre, stoi(hpStr), stoi(atkStr), inv);
            }
        }
        cerr << "[Archivos] Formato invalido en " << filename
             << ". Se usara jugador por defecto.\n";
        return new Jugador("Heroe", 100, 10, inv);
    }

    // Carga lista de enemigos desde archivo.
    static vector<Enemigos*> descargarEnemigos(const string& filename) {
        vector<Enemigos*> lista;
        ifstream f(filename);
        if (!f.is_open()) {
            cerr << "[Archivos] No se encontro " << filename << ".\n";
            return lista;
        }
        string linea;
        while (getline(f, linea)) {
            if (linea.empty()) continue;
            istringstream ss(linea);
            string nombre, hpStr, atkStr, expStr;
            if (getline(ss, nombre, '|') &&
                getline(ss, hpStr,  '|') &&
                getline(ss, atkStr, '|') &&
                getline(ss, expStr, '|'))
            {
                lista.push_back(new Enemigos(nombre, stoi(hpStr),
                                             stoi(atkStr), stoi(expStr)));
            }
        }
        return lista;
    }

    // Carga lista de objetos desde archivo.
    static vector<Objetos*> descargarObjetos(const string& filename) {
        vector<Objetos*> lista;
        ifstream f(filename);
        if (!f.is_open()) {
            cerr << "[Archivos] No se encontro " << filename << ".\n";
            return lista;
        }
        string linea;
        while (getline(f, linea)) {
            if (linea.empty()) continue;
            istringstream ss(linea);
            string nombre, desc, sanStr;
            if (getline(ss, nombre, '|') &&
                getline(ss, desc,   '|') &&
                getline(ss, sanStr, '|'))
            {
                lista.push_back(new Objetos(nombre, desc, stoi(sanStr)));
            }
        }
        return lista;
    }
};
