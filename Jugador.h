#include "Inventario.h"
#include "Objetos.h"
#include "SistemaGeneral.h"
#pragma once


class Jugador :SistemaGeneral{
private:
    string nombre;
    int hp;
    int nivel;
    int experiencia;
    int ataque;
    int resetHP;
    Inventario<Objetos*> *inventario;
public:
    Jugador(string nombre, int hp, Inventario<Objetos*> *invent)
    {
        this->nombre = nombre;
        this->hp = hp;
        this->inventario = invent;
    }
    void agregarObjeto(Objetos* obj) {
        inventario->agregar(obj);
    }
    void tomarDamage(int damage) {
        hp -= damage;
    }
    void sanarDamage(int damage)
    {
        hp += damage;
    }
    void obtenerExperienciaYNivel(int cantidadExp)
    {
        experiencia +=cantidadExp;
        if (experiencia>=50)
        {
            experiencia-=50;
            nivel++;
            ataque +=5;
            resetHP +=5;
            hp=resetHP;
            cout<<"Nuevo nivel de"<<nombre<<"has subido al"<<endl;
            cout<<"Tu vide se reseteo"<<endl;


        }

    }

    string getNombre()
    {
        return nombre;
    }
    int getHp()
    {
        return hp;
    }
    int getNivel()
    {
        return nivel;
    }
    int getExperiencia()
    {
        return experiencia;
    }
    int getAtaque()
    {
        return ataque;
    }

    bool siguePartida()
    {
        return hp>0;
    }



};



