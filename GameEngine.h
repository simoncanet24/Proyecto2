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

    int getIntInput(const string& prompt);
    void printBootNarration();
    void selectBuddy();
    void gameLoop();
    void gameOver();

public:

    GameEngine();
    void run();
};


#endif //PROYECTO2_GAMEENGINE_H
