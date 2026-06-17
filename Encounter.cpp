#include "Encounter.h"
#include "Enemy.h"
#include <iostream>
#include <random>

using namespace std;

int getValidatedChoice(const string& prompt, int min, int max, int saveChoice = 0, int quitChoice = 9) {
    int choice;
    while (true) {
        cout << prompt;
        if (cin >> choice) {
            if ((choice >= min && choice <= max) || choice == saveChoice || choice == quitChoice) {
                return choice;
            }
        }
        cout << "\n[Error] Invalid input. Please enter a valid number from the menu.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

int displayMenuAndGetChoice() {
    cout << "\n[1] FIGHT  [2] ITEM  [3] FLEE  [0] SAVE GAME  [9] GIVE UP\n";
    return getValidatedChoice("> ", 1, 3);
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
            cout << "[" << i << "] " << *item << endl;
        }
    }

    int choice = getValidatedChoice("Enter the number of the item to use (or 9 to cancel): ", 0, player.itemCount() - 1, -1, 9);

    if (choice != 9) {
        int healedAmount = player.applyItem(choice);
        cout << "\nYou patched yourself up for " << healedAmount << " HP!" << endl;
        cout << "Current HP: " << player.getHp() << " / " << player.getBaseHp() << endl;
    } else {
        cout << "\nYou decided to save your items for later." << endl;
    }
}

int EnemyEncounter::execute(Player& player) {
    // 1. Setup Random Generation for the Enemy
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> chance100(1, 100);
    uniform_int_distribution<int> hpDist(35, 90);
    uniform_int_distribution<int> dmgDist(8, 20);
    uniform_int_distribution<int> typeDist(0, 7);

    // 2. Instantiate the Enemy
    Enemy enemy(static_cast<Enemy::Type>(typeDist(rng)), hpDist(rng), dmgDist(rng));

    cout << "\n--- ENEMY ENCOUNTER ---" << endl;
    cout << "A " << enemy.getName() << " blocks your path!" << endl;

    // 3. Combat Loop (Checks BOTH player and enemy health)
    while (player.isAlive() && enemy.isAlive()) {
        cout << "\n[" << enemy.getName() << " HP: " << enemy.getHp() << "]  |  [Your HP: " << player.getHp() << "]" << endl;

        // Flee logic check
        if (enemy.isFleeThreshold() && chance100(rng) <= 10) {
            cout << "The " << enemy.getName() << " panics and flees into the shadows!" << endl;
            return 1;
        }

        int choice = displayMenuAndGetChoice();

        if (choice == 0) return 0; // Trigger Save
        if (choice == 9) return 9; // Trigger Game Over

        if (choice == 1) { // FIGHT
            cout << "\nYou attack for " << player.getDamage() << " damage!" << endl;
            enemy.takeDamage(player.getDamage());
            player.recordDamageDealt(player.getDamage());

            if (enemy.isAlive()) {
                cout << "The " << enemy.getName() << " attacks back!" << endl;
                player.takeDamage(enemy.getDamage());

                if (player.getBuddy().getType() == BuddyType::ENZO) {
                    cout << "Enzo distracts the enemy! Damage was reduced." << endl;
                }
            }
        }
        else if (choice == 2) { // ITEM
            handleItemMenu(player);
        }
        else if (choice == 3) { // FLEE
            cout << "You managed to run away!" << endl;
            return 1;
        }
    }

    if (!player.isAlive()) return 9; // Game Over

    // 4. Victory Sequence
    cout << "\n*** You defeated the " << enemy.getName() << "! ***" << endl;
    player.recordEnemySlain();
    player.boostDamage();
    cout << "Your combat experience grows. Base Damage increased to " << player.getDamage() << "!" << endl;

    // 10% Chance for Enzo/Enemy to drop an item
    if (chance100(rng) <= 10 || player.getBuddy().hasDropBonus()) {
        cout << "You found something on the ground!" << endl;
        uniform_int_distribution<int> itemTypeDist(0, 2);
        uniform_int_distribution<int> healDist(25, 50);
        player.addItem(make_unique<Item>("Strange Remedy", "Heals wounds", healDist(rng), static_cast<Item::Type>(itemTypeDist(rng))));
    }

    return 1;
}

int ItemEncounter::execute(Player& player) {
    cout << "\n--- ITEM DISCOVERY ---" << endl;
    cout << "You rummage through an abandoned concession stand..." << endl;

    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> healDist(25, 50);

    player.addItem(make_unique<Item>("First Aid Kit", "Heals HP", healDist(rng), Item::Type::MEDKIT));
    cout << "You found a First Aid Kit and stored it in your inventory!" << endl;
    return 1;
}

int SafehouseEncounter::execute(Player& player) {
    cout << "\n--- SAFEHOUSE ---" << endl;
    cout << "You found a secure security booth. Do you want to rest?" << endl;
    cout << "[1] Yes (Restore HP to 100)\n[2] No (Search for an item)\n";

    int choice = getValidatedChoice("> ", 1, 2);

    if (choice == 1) {
        player.heal(100);
        cout << "You feel fully rested. HP restored to " << player.getHp() << "." << endl;
    } else {
        cout << "You scrounged around and found extra supplies!" << endl;

        random_device rd;
        mt19937 rng(rd());
        uniform_int_distribution<int> healDist(25, 50);

        // FIXED: Adding the item if the player searches
        player.addItem(make_unique<Item>("Stash Bandages", "Heals HP", healDist(rng), Item::Type::BANDAGES));
    }
    return 1;
}

int SpecialEncounter::execute(Player& player) {
    cout << "\n--- STRANGE LEVER ---" << endl;
    cout << "You and " << player.getBuddy().getName() << " find a rusty lever on the wall. Pull it?" << endl;
    cout << "[1] YES\n[2] NO\n";

    int choice = getValidatedChoice("> ", 1, 2);

    if (choice == 1) {
        cout << "A trapdoor opens! You fall into a pit and die." << endl;
        player.takeDamage(999); // Instakill
        return 9;
    } else {
        cout << "You wisely ignore the lever and keep walking." << endl;
        return 1;
    }
}

int EndgameEncounter::execute(Player& player) {
    cout << "\n--- FINAL BOSS ---" << endl;
    cout << "Gloop steps out from the shadows. 'It ends here,' he says." << endl;

    if (player.getBuddy().getType() == BuddyType::GLOOP) {
        cout << "Your buddy slot is now empty! Gloop has betrayed you." << endl;
        player.dismissBuddy();
    }

    int gloopHP = 120;

    while (player.isAlive() && gloopHP > 0) {
        cout << "\n[Gloop HP: " << gloopHP << "]  |  [Your HP: " << player.getHp() << "]" << endl;
        int choice = displayMenuAndGetChoice();

        if (choice == 0) return 0;
        if (choice == 9) return 9;

        if (choice == 1) {
            cout << "\nYou strike Gloop for " << player.getDamage() << " damage!" << endl;
            gloopHP -= player.getDamage();

            if (gloopHP > 0) {
                cout << "Gloop hits you back!" << endl;
                player.takeDamage(20);
            }
        }
        else if (choice == 2) {
            handleItemMenu(player);
        }
        else if (choice == 3) {
            cout << "There is no running from Gloop." << endl;
        }
    }

    if (!player.isAlive()) return 9;

    cout << "\n*** You defeated Gloop! You survived the Abandoned Theme Park! ***" << endl;
    return 9;
}