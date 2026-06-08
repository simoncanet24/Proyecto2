//
// Created by simon on 6/8/2026.
//

#include "GameEngine.h"
#include "EncounterFactory.h"
#include "DataManager.h"
#include <iostream>
#include <random>
#include <algorithm> // for std::transform

using namespace std;

// Helper to generate the initial 10-30 damage before constructing the Player
int generateInitialDamage() {
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> dmgDist(10, 30);
    return dmgDist(rng);
}

GameEngine::GameEngine()
    : player("Survivor", 100, generateInitialDamage()), turnCount(0), gameRunning(true) {}

int GameEngine::getIntInput(const string& prompt) {
    int choice;
    while (true) {
        cout << prompt;
        if (cin >> choice) {
            return choice;
        } else {
            cout << "\n[Error] Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

void GameEngine::printBootNarration() {
    cout << "======================================================\n";
    cout << "               ABANDONED THEME PARK                   \n";
    cout << "======================================================\n";
    cout << "You wake up on the cracked asphalt of an old theme park.\n";
    cout << "The rides are rusted. The mascots look... wrong.\n";
    cout << "Your Base HP: 100 | Your Base Damage: " << player.getDamage() << "\n\n";
}

void GameEngine::selectBuddy() {
    cout << "Before you start walking, two strange figures approach you.\n";
    cout << "Who do you want to tag along with?\n";
    cout << "[1] Enzo (Provides 25% damage reduction and finds items)\n";
    cout << "[2] Gloop (Just kind of stares at you. No buffs.)\n";

    int buddyChoice = getIntInput("> ");

    if (buddyChoice == 1) {
        player.setBuddy(BuddyType::ENZO);
        cout << "\nEnzo nods. You feel safer already.\n";
    } else {
        player.setBuddy(BuddyType::GLOOP);
        cout << "\nGloop smiles weirdly. Let's hope he's useful.\n";
    }
}

void GameEngine::gameLoop() {
    while (gameRunning && player.isAlive()) {
        string route;

        // Loop ensures input validation for the route
        while (true) {
            cout << "\n------------------------------------------------------\n";
            cout << "You stand at a fork in the park paths.\n";
            cout << "Type 'left' or 'right' to choose a route.\n> ";
            cin >> route;

            // Make case-insensitive conversion to lowercase
            for (char &c : route) c = tolower(c);

            if (route == "left" || route == "right") {
                break; // Valid input received
            }
            cout << "\n[Error] Invalid direction! The dark mist prevents you from going that way.\n";
        }

        turnCount++;

        // Generate the encounter
        auto encounter = EncounterFactory::createNext(turnCount, player);

        // --- SYLLABUS TOPIC USE: DOWNCASTING ---
        // We evaluate the abstract Encounter pointer back to its concrete type
        // using dynamic_cast to build the narrative history log.
        string encounterDesc = "encountered an anomaly";
        if (dynamic_cast<EnemyEncounter*>(encounter.get())) {
            encounterDesc = "fought an enemy";
        } else if (dynamic_cast<ItemEncounter*>(encounter.get())) {
            encounterDesc = "found an item";
        } else if (dynamic_cast<SafehouseEncounter*>(encounter.get())) {
            encounterDesc = "found a safehouse";
        } else if (dynamic_cast<SpecialEncounter*>(encounter.get())) {
            encounterDesc = "encountered a strange lever";
        } else if (dynamic_cast<EndgameEncounter*>(encounter.get())) {
            encounterDesc = "faced the final boss Gloop";
        }

        int result = encounter->execute(player);

        if (result == 0) {
            DataManager::saveGame(player, turnCount);
            turnCount--; // Don't progress depth on game save
        }
        else {
            // Record this journey path only if a genuine step forward occurred
            player.recordEncounter("went " + route + " -> " + encounterDesc);

            if (result == 9) {
                gameRunning = false;
            }
        }
    }
}

void GameEngine::gameOver() {
    if (!player.isAlive()) {
        cout << "\n*** YOU DIED ***\n";
    } else {
        cout << "\n*** YOU GAVE UP (OR WON) ***\n";
    }

    DataManager::saveFinalLog(player, turnCount);

    cout << "\nPress ENTER to exit...";
    cin.ignore(10000, '\n');
    cin.get();
}

void GameEngine::run() {
    printBootNarration();
    selectBuddy();
    gameLoop();
    gameOver();
}