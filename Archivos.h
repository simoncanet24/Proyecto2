#include <iostream>
#include <ranges>
#include <vector>
#include "Jugador.h"
using namespace std;

class Archivos {
static Jugador descargarJugador(const string& file){
    ifstream archivo(file);
    if (!archivo.is_open()) {
        throw runtime_error("No se pudo abrir el archivo: " + file);
    }
};



