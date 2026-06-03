#include <iostream>
using namespace std;
#pragma once

class SistemaGeneral {
protected:
    string nombre;
    int hp;
    int ataque;
public:
    SistemaGeneral() {
        nombre = "Jugador";
        hp = 100;
        ataque = 10;
    }
    SistemaGeneral(string nombre, int hp, int ataque)
    {
        nombre = nombre;
        hp = hp;
        ataque = ataque;
    }
    virtual ~SistemaGeneral()=default;
    const string getNombre()
    {
        return nombre;
    }
    int getHp()
    {
        return hp;
    }
    int getAtaque()
    {
        return ataque;
    }
    void setHp(int hp)
    {
        this->hp = hp;
    }
    bool siguePartida()
    {
        return hp>0;
    }

};



