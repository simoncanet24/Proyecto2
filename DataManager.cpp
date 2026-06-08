//
// Created by simon on 6/8/2026.
//
#include "DataManager.h"

void DataManager::saveGame(const Player& player, int turnCount) {
    // --- SAVE PLAYER DATA ---
    try {
        ofstream playerFile;
        // Enable exceptions for file streams
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

    // --- SAVE ENEMIES DATA ---
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
        // Enable exceptions to immediately catch missing or corrupted files
        playerFile.exceptions(ifstream::failbit | ifstream::badbit);
        playerFile.open("PLAYER.txt");

        string dummy, buddyName;
        int loadedHp, loadedDmg;

        // Skip the header string: "--- PLAYER SAVE DATA ---"
        getline(playerFile, dummy);

        // Read specific formatted values
        playerFile >> dummy >> loadedHp;        // Reads: "HP:" [value]
        playerFile >> dummy >> loadedDmg;       // Reads: "DMG:" [value]
        playerFile >> dummy >> buddyName;       // Reads: "Buddy:" [value]
        playerFile >> dummy >> dummy >> turnCount; // Reads: "Turn" "Count:" [value]

        playerFile.close();

        // 1. Determine Buddy Type
        BuddyType loadedBuddy = BuddyType::NONE;
        if (buddyName == "Enzo") loadedBuddy = BuddyType::ENZO;
        else if (buddyName == "Gloop") loadedBuddy = BuddyType::GLOOP;

        // 2. Reconstruct the Player Object
        // We initialize with a max base HP of 100, then safely set their current wounded HP
        player = Player("Survivor", 100, loadedDmg, loadedBuddy);
        player.setHp(loadedHp);

        cout << "\n[System] PLAYER.txt loaded successfully! Welcome back." << endl;
        return true;

    } catch (const ifstream::failure& e) {
        // This safely triggers if PLAYER.txt doesn't exist yet
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
        logFile << "========================================\n";

        logFile.close();
        cout << "\n[System] Final report successfully written to final_log.txt\n";
    } catch (const ofstream::failure& e) {
        cerr << "\n[Critical Error] Could not write final_log.txt: " << e.what() << "\n";
    }
}