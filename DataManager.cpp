//
// Created by simon on 6/8/2026.
//
#include "DataManager.h"


void DataManager::saveGame(const Player& player, int turnCount) {
    try {
        ofstream playerFile;
        playerFile.exceptions(ofstream::failbit | ofstream::badbit);
        playerFile.open("PLAYER.txt");

        playerFile << "--- PLAYER SAVE DATA ---\n";
        playerFile << "HP: " << player.getHp() << "\n";
        playerFile << "DMG: " << player.getDamage() << "\n";
        playerFile << "Buddy: " << player.getBuddy().getName() << "\n";
        playerFile << "Turn Count: " << turnCount << "\n";

        playerFile.close();
        cout << "[System] PLAYER.txt saved successfully.\n";
    } catch (const ofstream::failure& e) {
        cerr << "[Error] Failed to save PLAYER.txt: " << e.what() << "\n";
    }
    try {
        ofstream enemyFile;
        enemyFile.exceptions(ofstream::failbit | ofstream::badbit);
        enemyFile.open("ENEMIES.txt");

        enemyFile << "--- ENEMY TRACKER ---\n";
        enemyFile << "Since encounters are dynamically generated, the park is full of threats.\n";
        enemyFile << "Enemies Defeated So Far: " << player.getStats().enemiesSlain << "\n";

        enemyFile.close();
        cout << "[System] ENEMIES.txt saved successfully.\n";
    } catch (const ofstream::failure& e) {
        cerr << "[Error] Failed to save ENEMIES.txt: " << e.what() << "\n";
    }
}

bool DataManager::loadGame(Player& player, int& turnCount) {
    try {
        ifstream playerFile;
        playerFile.exceptions(ifstream::failbit | ifstream::badbit);
        playerFile.open("PLAYER.txt");

        string dummy, buddyName;
        int loadedHp, loadedDmg;
        getline(playerFile, dummy);
        playerFile >> dummy >> loadedHp;
        playerFile >> dummy >> loadedDmg;
        playerFile >> dummy >> buddyName;
        playerFile >> dummy >> dummy >> turnCount;

        playerFile.close();

        BuddyType loadedBuddy = BuddyType::NONE;
        if (buddyName == "Enzo") loadedBuddy = BuddyType::ENZO;
        else if (buddyName == "Gloop") loadedBuddy = BuddyType::GLOOP;

        player = Player("Survivor", 100, loadedDmg, loadedBuddy);
        player.setHp(loadedHp);

        cout << "\n[System] PLAYER.txt loaded successfully! Welcome back." << endl;
        return true;

    } catch (const ifstream::failure& e) {
        cerr << "\n[System] No valid save file found. Starting a fresh game..." << endl;
        return false;
    }
}

void DataManager::saveFinalLog(const Player& player, int turnCount) {
    try {
        ofstream logFile;
        logFile.exceptions(ofstream::failbit | ofstream::badbit);
        logFile.open("final_log.txt");

        logFile << "========================================\n";
        logFile << "       FINAL MATCH REPORT LOG           \n";
        logFile << "========================================\n";
        logFile << "Final Status: " << (player.isAlive() ? "Survived" : "Deceased") << "\n";
        logFile << "Buddy Chosen: " << player.getBuddy().getName() << "\n";
        logFile << "Total Encounters Survived: " << turnCount << "\n";
        logFile << "Total Enemies Slain: " << player.getStats().enemiesSlain << "\n";
        logFile << "Total Damage Dealt: " << player.getStats().totalDamageDealt << "\n";
        logFile << "Total Healing Received: " << player.getStats().totalHealingReceived << "\n";

        logFile << "\n--- JOURNEY HISTORY ---\n";
        if (player.getStats().encounterLog.empty()) {
            logFile << "No steps taken.\n";
        } else {
            for (const auto& logEntry : player.getStats().encounterLog) {
                logFile << logEntry << "\n";
            }
        }

        logFile << "========================================\n";

        logFile.close();
        cout << "\n[System] Final report successfully written to final_log.txt\n";

    } catch (const ifstream::failure& e) {
        cerr << "[Error] Failed to write final_log.txt: " << e.what() << "\n";
    }
}