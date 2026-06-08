#include <iostream>
#include <string>
#include <random>
#include "Player.h"
#include "EncounterFactory.h"
#include "DataManager.h"

using namespace std;

int main() {
    // 1. Initial Setup & Random DMG roll
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> dmgDist(10, 30);

    int initialDamage = dmgDist(rng);
    Player player("Survivor", 100, initialDamage);

    // 2. Boot Narration
    cout << "======================================================\n";
    cout << "               ABANDONED THEME PARK                   \n";
    cout << "======================================================\n";
    cout << "You wake up on the cracked asphalt of an old theme park.\n";
    cout << "The rides are rusted. The mascots look... wrong.\n";
    cout << "Your Base HP: 100 | Your Base Damage: " << initialDamage << "\n\n";

    // 3. Buddy Selection
    cout << "Before you start walking, two strange figures approach you.\n";
    cout << "Who do you want to tag along with?\n";
    cout << "[1] Enzo (Provides 25% damage reduction and finds items)\n";
    cout << "[2] Gloop (Just kind of stares at you. No buffs.)\n> ";

    int buddyChoice;
    cin >> buddyChoice;

    if (buddyChoice == 1) {
        player.setBuddy(BuddyType::ENZO);
        cout << "\nEnzo nods. You feel safer already.\n";
    } else {
        player.setBuddy(BuddyType::GLOOP);
        cout << "\nGloop smiles weirdly. Let's hope he's useful.\n";
    }

    // 4. Main Game Loop
    int turnCount = 0;
    bool gameRunning = true;

    while (gameRunning && player.isAlive()) {
        cout << "\n------------------------------------------------------\n";
        cout << "You stand at a fork in the park paths.\n";
        cout << "Type 'left' or 'right' to choose a route.\n> ";

        string route;
        cin >> route; // Accepts input, ignores case sensitivity context for simplicity

        turnCount++;

        // Generate and execute the encounter
        auto encounter = EncounterFactory::createNext(turnCount, player);
        int result = encounter->execute(player);

        // Handle Encounter Results
        if (result == 0) {
            DataManager::saveGame(player, turnCount);
            turnCount--; // Don't count a save action as progressing deeper into the park
        }
        else if (result == 9) {
            gameRunning = false; // Player chose to GIVE UP or Game Over triggered
        }
    }

    // 5. Game Over / Final Log Execution
    if (!player.isAlive()) {
        cout << "\n*** YOU DIED ***\n";
    } else {
        cout << "\n*** YOU GAVE UP (OR WON) ***\n";
    }

    DataManager::saveFinalLog(player, turnCount);

    cout << "\nPress ENTER to exit...";
    cin.ignore(); // Clear buffer
    cin.get();    // Wait for keypress

    return 0; // Smart pointers automatically clean up memory here!
}