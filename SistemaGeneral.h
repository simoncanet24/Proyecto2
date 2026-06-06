#pragma once
#include <iostream>
#include <string>
using namespace std;

class SistemaGeneral {
protected:
    string nombre;
    int hp;
    int ataque;

public:
    // Constructor por defecto
    SistemaGeneral() : nombre("Desconocido"), hp(100), ataque(10) {}

    // Constructor parametrizado — se usa lista de inicializacion para evitar shadowing
    SistemaGeneral(const string& nombre, int hp, int ataque)
        : nombre(nombre), hp(hp), ataque(ataque) {}

    virtual ~SistemaGeneral() = default;

    string getNombre() const { return nombre; }
    int getHp()        const { return hp; }
    int getAtaque()    const { return ataque; }

    void setHp(int nuevoHp) { this->hp = nuevoHp; }

    // Recibir dano
    void tomaDamage(int damage) { hp -= damage; }

    bool siguePartida() const { return hp > 0; }

    friend ostream& operator<<(ostream& os, const SistemaGeneral& e) {
        os << "[" << e.nombre << "] HP: " << e.hp << " | ATK: " << e.ataque;
        return os;
    }
};
