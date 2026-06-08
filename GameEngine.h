//
// Created by simon on 6/8/2026.
//

#ifndef PROYECTO2_GAMEENGINE_H
#define PROYECTO2_GAMEENGINE_H
#include <string>
#include "Player.h"

using namespace std;

class GameEngine {
private:
    Player player;
    int turnCount;
    bool gameRunning;

    // Internal helper methods
    int getIntInput(const string& prompt);
    void printBootNarration();
    void selectBuddy();
    void gameLoop();
    void gameOver();

public:
    // Constructor initializes the player and game state
    GameEngine();

    // The single public method called by main.cpp
    void run();
};


#endif //PROYECTO2_GAMEENGINE_H
