#pragma once
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Bitacora.h"
using namespace std;

class SistemaCombate {
public:
    static bool combat(Jugador& jugador, Enemigos& enemigo, Bitacora& bitacora) {
        cout << "\n=== Combate contra: " << enemigo.getNombre() << " ===\n";
        cout << enemigo << "\n";
        bitacora.datos("Combate iniciado contra " + enemigo.getNombre());

        while (jugador.siguePartida() && enemigo.siguePartida()) {
            cout << "\n" << jugador << "\n";
            cout << "[1] Atacar  [2] Usar curativo  [3] Correr\n> ";
            int opcion;
            cin >> opcion;

            if (opcion == 1) {
                enemigo.tomaDamage(jugador.getAtaque());
                cout << "Le hiciste " << jugador.getAtaque()
                     << " de dano a " << enemigo.getNombre()
                     << ". HP enemigo: " << enemigo.getHp() << "\n";
                bitacora.datos("Jugador ataca a " + enemigo.getNombre()
                               + " por " + to_string(jugador.getAtaque()));

                if (enemigo.siguePartida()) {
                    jugador.tomaDamage(enemigo.getAtaque());
                    cout << enemigo.getNombre() << " te ataco por "
                         << enemigo.getAtaque() << ". Tu HP: "
                         << jugador.getHp() << "\n";
                    bitacora.datos(enemigo.getNombre() + " golpea al jugador por "
                                   + to_string(enemigo.getAtaque()));
                }

            } else if (opcion == 2) {
                jugador.usarSanador();

            } else {
                cout << "Escapaste del combate.\n";
                bitacora.datos("Jugador escapo de " + enemigo.getNombre());
                return false;
            }
        }

        if (jugador.siguePartida()) {
            cout << "\nVenciste a " << enemigo.getNombre() << "!\n";
            jugador.ganaExperiencia(enemigo.getExp());
            bitacora.datos("Jugador derroto a " + enemigo.getNombre()
                           + ". +" + to_string(enemigo.getExp()) + " experiencia");
            return true;
        }

        bitacora.datos("Jugador fue derrotado por " + enemigo.getNombre());
        return false;
    }
};
