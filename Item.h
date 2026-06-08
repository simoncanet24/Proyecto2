#pragma once
#include <iostream>
#include <string>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// Item
//
// A consumable healing item the player can find during encounters.
// There are three archetypes (MEDKIT, BANDAGES, HEALING_HERB).
//
// Design notes:
//   • The actual HP restored is NOT stored here as an absolute value.
//     Instead, healPercent (25–50) is stored and the real amount is computed
//     by Player::applyItem() as  (healPercent * Player::baseHp) / 100.
//     This keeps Items independent of any particular player's stats and lets
//     the same item scale correctly after a save/reload (Data Persistence).
//   • Instances are managed exclusively via std::unique_ptr<Item> — Item has
//     no knowledge of this; ownership is the Inventory template's concern.
// ─────────────────────────────────────────────────────────────────────────────
class Item {
public:
    enum class Type { MEDKIT, BANDAGES, HEALING_HERB };

private:
    string name;
    string description;
    int    healPercent;  // randomised in [25, 50] at construction time
    Type   type;

public:
    Item(const string& name, const string& desc, int healPercent, Type type)
        : name(name), description(desc), healPercent(healPercent), type(type) {}

    // ── Accessors ─────────────────────────────────────────────────────────────
    string getName()        const { return name;        }
    string getDescription() const { return description; }
    int    getHealPercent() const { return healPercent; }
    Type   getType()        const { return type;        }

    // Format example: "Medkit  [38% HP] — Military-grade first aid kit"
    friend ostream& operator<<(ostream& os, const Item& i) {
        os << i.name
           << "  [" << i.healPercent << "% HP]  — "
           << i.description;
        return os;
    }
};