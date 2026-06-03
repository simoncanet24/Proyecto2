#include <iostream>
#include "Jugador.h"
#include "Enemigos.h"
#include "Bitacora.h"
using namespace std;

class SistemaCombate {
    bool combat(Jugador& jugador, Enemigos enemigos, Bitacora& bitacora) {
        cout << "\n Combate: " << enemigos.getNombre() << "\n";
        cout << enemigos << "\n";
        bitacora.datos("Combate iniciado contra " + enemigos.getNombre());

        while (jugador.siguePartida() && enemigos.siguePartida()) {
            cout << jugador << "\n";
            cout << "[1] Atacar  [2] Usar curativo  [3] Correr\n> ";
            int opcion;
            cin >> opcion;

            if (opcion == 1) {
                enemigos.tomaDamage(jugador.getAtaque());
                cout << "Le hiciste " << jugador.getAtaque()
                          << " de damage a " << enemigos.getNombre()
                          << ". HP: " << enemigos.getHp() << "\n";
                bitacora.datos("Jugador ataca a " + enemigos.getNombre()
                         + " por " + to_string(jugador.getAtaque()));

                if (enemigos.siguePartida()) {
                    jugador.tomaDamage(enemigos.getAtaque());
                    cout << enemigos.getNombre()
                              << enemigos.getAtaque() << ". Tu quito:  "
                              << enemigos.getHp() << "\n";
                    bitacora.datos(enemigos.getNombre() + " golpea al jugador por "
                             + to_string(enemigos.getAtaque()));
                }

            } else if (opcion == 2) {
                jugador.usarSanador();

            } else {
                cout << "Escapaste \n";
                bitacora.datos("Jugador escapo de " + enemigos.getNombre());
                return false;
            }
        }

        if (jugador.siguePartida()) {
            cout << "\nVenciste a " << enemigos.getNombre() << "!\n";
            jugador.ganaExperiencia(enemigos. ());
            bitacora.datos("Jugador derroto a " + enemigos.getNombre()
                     + ". +" + to_string(enemigos.getExp()) + " experiencia ");
            return true;
        }

        bitacora.datos("Jugador fue derrotado por " + enemigos.getNombre());
        return false;
    }
};