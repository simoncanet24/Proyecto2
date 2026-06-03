#include<iostream>
#include<string>
#include"Jugador.h"
using namespace std;
#include "Bitacora.h"
#include<fstream>


class Reporte {
    string file;
    public:
    explicit Reporte(string file);
    void generarReporte(const Jugador& jugador,const Bitacora& bitacora)
    {
        ofstream f(file);
        if (!f.is_open())
            throw runtime_error("Error al abrir el archivo");
        f<<"Reporte de la Partida---------------------"<<endl;
        f<<"Nombre del Jugador"<<jugador.getNombre()<<endl<<"\n";
        f<<"Nivel"<<jugador.getNivel()<<endl<<"\n";
        f<<"Experiencia"<<jugador.getExperiencia()<<endl<<"\n";


        f<<"Nivel de Ataque"<<jugador.getAtaque()<<endl<<"\n";
        f<<"Final"<<jugador.siguePartida()<<endl<<"\n";
    }

};



