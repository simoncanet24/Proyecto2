#pragma once
#include "SistemaGeneral.h"

class Enemigos : public SistemaGeneral {
private:
    int expRecompensa; // experiencia que da al ser derrotado

public:
    Enemigos(const string& nombre, int hp, int ataque, int exp)
        : SistemaGeneral(nombre, hp, ataque), expRecompensa(exp) {}

    int getExp() const { return expRecompensa; }
};
