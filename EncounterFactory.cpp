#include "EncounterFactory.h"

mt19937 EncounterFactory::rng(random_device{}());
bool EncounterFactory::safehouseUsed = false;

unique_ptr<Encounter> EncounterFactory::createNext(int turnCount, const Player& player) {
    uniform_int_distribution<int> dist100(1, 100);
    int roll = dist100(rng);

    // --- 1. ENDGAME ENCOUNTER LOGIC ---
    if (turnCount >= 10 && roll <= 90) {
        return make_unique<EndgameEncounter>();
    } else if (turnCount >= 7 && turnCount < 10 && roll <= 40) {
        return make_unique<EndgameEncounter>();
    }

    // --- 2. STANDARD ENCOUNTER PROBABILITIES ---
    int currentHP = player.getHp();
    int itemChance = (currentHP < 50) ? 50 : 20; // High chance if HP < 50

    roll = dist100(rng); // Re-roll for standard encounters

    if (roll <= itemChance) {
        return make_unique<ItemEncounter>();
    }
    else if (!safehouseUsed && roll <= (itemChance + 5)) {
        // 5% chance for safehouse, only if not used yet
        safehouseUsed = true;
        return make_unique<SafehouseEncounter>();
    }
    else if (roll <= (itemChance + 5 + 15)) {
        // 15% chance for special encounter
        return make_unique<SpecialEncounter>();
    }
    else {
        // Remaining probability defaults to an Enemy Encounter
        return make_unique<EnemyEncounter>();
    }
}
