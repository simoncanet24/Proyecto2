//
// Created by simon on 6/7/2026.
//

#include "Encounter.h"
#include <iostream>
#include <random>

using namespace std;

// Helper function for the Pokemon-style menu
int displayMenuAndGetChoice() {
    int choice;
    cout << "\n[1] FIGHT  [2] ITEM  [3] FLEE  [0] SAVE GAME  [9] GIVE UP\n> ";
    cin >> choice;
    return choice;
}

void handleItemMenu(Player& player) {
    if (!player.hasItems()) {
        cout << "\nYou reach into your pockets... but you don't have any items." << endl;
        return;
    }

    cout << "\n--- INVENTORY ---" << endl;
    for (int i = 0; i < player.itemCount(); i++) {
        const Item* item = player.peekItem(i);
        if (item) {
            // This automatically triggers the operator<< overload from Item.h
            cout << "[" << i << "] " << *item << endl;
        }
    }
    cout << "Enter the number of the item to use (or -1 to cancel): ";

    int choice;
    cin >> choice;

    if (choice >= 0 && choice < player.itemCount()) {
        int healedAmount = player.applyItem(choice);
        cout << "\nYou patched yourself up for " << healedAmount << " HP!" << endl;
        cout << "Current HP: " << player.getHp() << " / " << player.getBaseHp() << endl;
    } else {
        cout << "\nYou decided to save your items for later." << endl;
    }
}

// --- ENEMY ENCOUNTER ---
int EnemyEncounter::execute(Player& player) {
    cout << "\n--- ENEMY ENCOUNTER ---" << endl;
    cout << "A twisted theme park mascot blocks your path!" << endl;

    // Standard loop for the encounter
    while (player.getHp() > 0) {
        int choice = displayMenuAndGetChoice();

        if (choice == 0) return 0; // Trigger Save
        if (choice == 9) return 9; // Trigger Game Over

        if (choice == 1) { // FIGHT
            cout << "You attack the enemy!" << endl;
            // Add damage logic here

            cout << "The enemy attacks back!" << endl;
            int incomingDamage = 15; // Example flat damage, replace with enemy DMG

            // Buddy Modifier Logic
            if (player.getBuddy().getType() == BuddyType::ENZO) {
                cout << "Enzo distracts the enemy! Damage reduced by 25%." << endl;
                incomingDamage = static_cast<int>(incomingDamage * 0.75);
            }

            player.takeDamage(incomingDamage);
            cout << "Your HP is now: " << player.getHp() << endl;

            // Break loop if enemy defeated
            // if (enemyHP <= 0) break;
        }
        else if (choice == 2) { // ITEM
            handleItemMenu(player);
        }
        else if (choice == 3) { // FLEE
            cout << "You managed to run away!" << endl;
            return 1; // Continue game
        }
    }

    if (player.getHp() <= 0) return 9; // Game Over
    return 1; // Continue game
}

// --- ITEM ENCOUNTER ---
int ItemEncounter::execute(Player& player) {
    cout << "\n--- ITEM DISCOVERY ---" << endl;
    cout << "You rummage through an abandoned concession stand..." << endl;
    cout << "You found a First Aid Kit!" << endl;

    // player.addItem(make_unique<Item>("First Aid Kit", "Heals HP", 35));
    return 1;
}

// --- SAFEHOUSE ENCOUNTER ---
int SafehouseEncounter::execute(Player& player) {
    cout << "\n--- SAFEHOUSE ---" << endl;
    cout << "You found a secure security booth. Do you want to rest?" << endl;
    cout << "[1] Yes (Restore HP to 100)\n[2] No (Search for an item)\n> ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        player.heal(100);
        cout << "You feel fully rested. HP restored to 100." << endl;
    } else {
        cout << "You found some extra supplies instead!" << endl;
        // player.addItem(...);
    }
    return 1;
}

// --- SPECIAL ENCOUNTER ---
int SpecialEncounter::execute(Player& player) {
    cout << "\n--- STRANGE LEVER ---" << endl;
    cout << "You and " << player.getBuddy().getName() << " find a rusty lever on the wall. Pull it?" << endl;
    cout << "[1] YES\n[2] NO\n> ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        cout << "A trapdoor opens! You fall into a pit and die." << endl;
        player.takeDamage(999); // Instakill
        return 9; // Game Over
    } else {
        cout << "You wisely ignore the lever and keep walking." << endl;
        return 1;
    }
}

// --- ENDGAME ENCOUNTER ---
int EndgameEncounter::execute(Player& player) {
    cout << "\n--- FINAL BOSS ---" << endl;
    cout << "Gloop steps out from the shadows. 'It ends here,' he says." << endl;

    if (player.getBuddy().getType() == BuddyType::GLOOP) {
        cout << "Your buddy slot is now empty! Gloop has betrayed you." << endl;
        player.dismissBuddy();
    }

    // Similar combat loop to EnemyEncounter, but specifically for Gloop (120 HP)
    int gloopHP = 120;

    while (player.getHp() > 0 && gloopHP > 0) {
        int choice = displayMenuAndGetChoice();

        if (choice == 0) return 0;
        if (choice == 9) return 9;

        if (choice == 1) {
            cout << "You strike Gloop!" << endl;
            gloopHP -= 20; // Example player damage

            if (gloopHP > 0) {
                cout << "Gloop hits you back!" << endl;
                player.takeDamage(20);
            }
        }
        else if (choice == 2) { // ITEM
            handleItemMenu(player);
        }
        else if (choice == 3) {
            cout << "There is no running from Gloop." << endl;
        }
    }

    if (player.getHp() <= 0) return 9;

    cout << "You defeated Gloop! You survived the Abandoned Theme Park!" << endl;
    return 9; // Triggers the final log/game over state in a victorious way
}