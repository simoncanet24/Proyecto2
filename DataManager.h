#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Player.h"

using namespace std;

class DataManager {
public:

    static void saveGame(const Player& player, int turnCount);
    static bool loadGame(Player& player, int& turnCount);
    static void saveFinalLog(const Player& player, int turnCount);
};

inline void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
}
