//
// Created by simon on 6/7/2026.
//

#ifndef PROYECTO2_ENCOUNTER_H
#define PROYECTO2_ENCOUNTER_H

#include <iostream>
#include "Player.h"
using namespace std;

class Encounter {
public:
    virtual ~Encounter() = default;

    // Returns status code to the main loop:
    // 1 = Continue, 0 = Save Game, 9 = Game Over / Give Up
    virtual int execute(Player& player) = 0;
};

class EnemyEncounter : public Encounter {
public:
    int execute(Player& player) override;
};

class ItemEncounter : public Encounter {
public:
    int execute(Player& player) override;
};

class SafehouseEncounter : public Encounter {
public:
    int execute(Player& player) override;
};

class SpecialEncounter : public Encounter {
public:
    int execute(Player& player) override;
};

class EndgameEncounter : public Encounter {
public:
    int execute(Player& player) override;
};

#endif //PROYECTO2_ENCOUNTER_H
