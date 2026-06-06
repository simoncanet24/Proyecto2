#include <iostream>
#include <string>
#include <vector>
#include "Archivos.h"
#include "SistemaCombate.h"
#include "Reporte.h"
#include "Bitacora.h"
using namespace std;

int main() {
    // --- Carga de datos desde archivos ---
    Jugador*          jugador  = Archivos::descargarJugador("jugador.txt");
    vector<Enemigos*> enemigos = Archivos::descargarEnemigos("enemigos.txt");
    vector<Objetos*>  objetos  = Archivos::descargarObjetos("objetos.txt");

    Bitacora bitacora;
    bitacora.datos("Partida iniciada.");

    // Agrega los objetos cargados al inventario del jugador
    for (auto* obj : objetos)
        jugador->agregarObjeto(obj);

    // --- Intro ---
    cout << "\nTe despiertas en la calle de una ciudad mientras llueve.\n";
    cout << "No sabes quien eres ni donde estas.\n\n";
    cout << "Que deberia de hacer?\n";
    cout << " [1] Gritar por ayuda\n";
    cout << " [2] Caminar por la calle\n> ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        cout << "\nParece que no hay nadie por las calles. Solo se escuchan las gotas de lluvia.\n";
        bitacora.datos("Jugador grito por ayuda.");
    } else {
        cout << "\nCaminas por las calles pero no ves a nadie, solo un gato al que llevas a un lugar seguro.\n";
        bitacora.datos("Jugador camino por la calle.");
    }

    // --- Combates ---
    bool vivoAlFinal = true;
    for (auto* enemigo : enemigos) {
        bool resultado = SistemaCombate::combat(*jugador, *enemigo, bitacora);
        if (!resultado && !jugador->siguePartida()) {
            vivoAlFinal = false;
            break;
        }
    }

    // --- Final ---
    if (vivoAlFinal) {
        cout << "\nSobreviviste la aventura. Nivel final: " << jugador->getNivel() << "\n";
        bitacora.datos("Jugador completo la aventura.");
    } else {
        cout << "\nFuiste derrotado. Fin del juego.\n";
        bitacora.datos("Partida terminada en derrota.");
    }

    // --- Archivos de salida ---
    bitacora.save("bitacora.txt");

    Reporte reporte("reporte.txt");
    reporte.generarReporte(*jugador, bitacora);

    cout << "\nReporte y bitacora guardados.\n";
    cout << "\nPresiona ENTER para salir...";
    cin.ignore();
    cin.get();

    // Liberar memoria
    delete jugador;
    for (auto* e : enemigos) delete e;
    for (auto* o : objetos)  delete o;

    return 0;
}
