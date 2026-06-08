#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Player.h"

using namespace std;

class DataManager {
public:

    // Saves the current state to PLAYER.txt, ENEMIES.txt, and ITEMS.txt
    static void saveGame(const Player& player, int turnCount);

    // Attempts to load the game state. Returns true if successful, false if no file exists.
    static bool loadGame(Player& player, int& turnCount);

    // Generates the final_log.txt file upon game over or victory
    static void saveFinalLog(const Player& player, int turnCount);
};

inline void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
}
