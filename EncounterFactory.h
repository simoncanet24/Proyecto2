//
// Created by simon on 6/7/2026.
//
#ifndef PROYECTO2_ENCOUNTERFACTORY_H
#define PROYECTO2_ENCOUNTERFACTORY_H
#include <memory>
#include <random>
#include "Encounter.h"
#include "Player.h"

using namespace std;

class EncounterFactory {
private:
    static mt19937 rng;
    static bool safehouseUsed;

public:
    static unique_ptr<Encounter> createNext(int turnCount, const Player& player);
};

#endif //PROYECTO2_ENCOUNTERFACTORY_H
