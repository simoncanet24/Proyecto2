#pragma once
#include <algorithm>   // std::min, std::max
#include <memory>      // std::unique_ptr
#include <vector>
#include <string>
#include "BaseEntity.h"
#include "Item.h"
#include "Inventory.h"
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// BuddyType enum  (defined at file scope so DataManager can reference it
//                  without pulling in the full Player class)
// ─────────────────────────────────────────────────────────────────────────────
enum class BuddyType { NONE, ENZO, GLOOP };


// ─────────────────────────────────────────────────────────────────────────────
// Buddy  — aggregate companion (Delegate Pattern)
//
// Owned by value inside Player — no heap allocation, no pointer needed.
// Encapsulates ALL buddy-specific logic so Player methods stay clean:
//
//   filterDamage()  — Enzo reduces incoming damage by 25%.
//   hasDropBonus()  — Enzo grants an item-drop chance after enemy fights.
//
// Gloop has no buffs or drops; it exists for narrative and becomes the
// ENDGAME boss regardless of whether it is the player's current buddy.
// ─────────────────────────────────────────────────────────────────────────────
class Buddy {
    BuddyType type;
    string    name;

public:
    // Default-constructible to NONE so Player can reset the buddy slot.
    explicit Buddy(BuddyType buddyType = BuddyType::NONE) : type(buddyType) {
        switch (type) {
            case BuddyType::ENZO:  name = "Enzo";  break;
            case BuddyType::GLOOP: name = "Gloop"; break;
            default:               name = "None";  break;
        }
    }

    BuddyType getType()   const { return type; }
    string    getName()   const { return name; }
    bool      isPresent() const { return type != BuddyType::NONE; }

    // Returns effective incoming damage after buddy-specific reduction.
    // Enzo: 25% less damage (multiply by 0.75).  Others: no change.
    int filterDamage(int incomingDmg) const {
        if (type == BuddyType::ENZO)
            return static_cast<int>(incomingDmg * 0.75);
        return incomingDmg;
    }

    // Enzo grants a bonus item-drop roll at the end of each enemy encounter.
    bool hasDropBonus() const { return type == BuddyType::ENZO; }
};


// ─────────────────────────────────────────────────────────────────────────────
// Player
//
// Rule of Five note:
//   Inventory<unique_ptr<Item>> is move-only, so the compiler implicitly
//   deletes Player's copy constructor and copy assignment — which is correct;
//   duplicating a player and its entire item inventory would be a logic error.
//   Move constructor and move assignment are compiler-generated (= default).
//   No user-defined destructor is needed; smart pointers clean themselves up.
// ─────────────────────────────────────────────────────────────────────────────
class Player : public BaseEntity {
public:
    // Accumulated run statistics — written to PLAYER.txt and final_log.txt.
    struct Stats {
        int            enemiesSlain         = 0;
        int            encountersCompleted  = 0;
        int            totalDamageDealt     = 0;
        int            totalHealingReceived = 0;
        vector<string> encounterLog;   // e.g. "ENEMY: Lost Soul", "SAFEHOUSE", ...
    };

private:
    int                         baseHp;      // ceiling for heal(); never changes after init
    Buddy                       buddy;       // aggregate — no pointer needed
    Inventory<unique_ptr<Item>> inventory;   // owns all items exclusively
    Stats                       stats;

public:
    // 'dmg' is randomised in [10, 30] by DataManager before construction.
    // 'buddyType' defaults to NONE and is set after the intro buddy-selection.
    Player(const string& name, int hp, int dmg,
           BuddyType buddyType = BuddyType::NONE)
        : BaseEntity(name, hp, dmg),
          baseHp(hp),
          buddy(buddyType),
          inventory(4) {}    // README: at most 4 collectible items per run

    // ── Combat ───────────────────────────────────────────────────────────────

    // Overrides BaseEntity::takeDamage to route incoming damage through
    // Buddy::filterDamage() before applying it.  Enemy::takeDamage uses the
    // base version (no reduction).  This is the key polymorphic split.
    void takeDamage(int dmg) override {
        int effective = buddy.filterDamage(dmg);
        BaseEntity::takeDamage(effective);
    }

    // Restores HP up to baseHp ceiling.  Returns actual amount healed.
    int heal(int amount) {
        int before = hp;
        hp = min(hp + amount, baseHp);
        return hp - before;
    }

    // Increases damage by ~5% (minimum +1) after defeating an enemy.
    // Uses integer arithmetic to keep type safety clean.
    void boostDamage() {
        damage = max(damage + 1, static_cast<int>(damage * 1.05));
    }

    // Clears the buddy slot — called by EndgameEncounter when Gloop is current buddy.
    void dismissBuddy() { buddy = Buddy(BuddyType::NONE); }

    // Replaces the buddy — used during the intro buddy-selection encounter.
    void setBuddy(BuddyType t) { buddy = Buddy(t); }

    // ── Inventory ────────────────────────────────────────────────────────────

    // Transfers ownership of 'item' into the inventory.
    // Call site:  player.addItem(make_unique<Item>(...));
    void addItem(unique_ptr<Item> item) {
        inventory.add(std::move(item));
    }

    // Consumes the item at 'index': removes it from inventory, heals the player,
    // updates healing stat, and returns the actual HP restored.
    // Throws std::out_of_range if index is invalid (caught in EncounterSystem).
    int applyItem(int index) {
        auto item    = inventory.remove(index);           // unique_ptr moved out
        int  healAmt = (item->getHealPercent() * baseHp) / 100;
        int  actual  = heal(healAmt);
        stats.totalHealingReceived += actual;
        return actual;
    }   // item destroyed here — no raw delete needed

    // Non-owning raw pointer for display purposes (e.g., printing the item menu).
    // Returns nullptr if 'index' is out of range — callers check before using.
    const Item* peekItem(int index) const {
        if (index < 0 || index >= inventory.size()) return nullptr;
        return inventory.peek(index).get();   // .get() = non-owning view
    }

    bool hasItems()  const { return !inventory.isEmpty(); }
    int  itemCount() const { return inventory.size(); }

    // ── Stats recording ───────────────────────────────────────────────────────

    void recordEnemySlain()                  { ++stats.enemiesSlain; }
    void recordDamageDealt(int dmg)          { stats.totalDamageDealt += dmg; }
    void recordEncounter(const string& label) {
        ++stats.encountersCompleted;
        stats.encounterLog.push_back(label);
    }

    // ── Accessors ─────────────────────────────────────────────────────────────

    int          getBaseHp()  const { return baseHp; }
    const Buddy& getBuddy()   const { return buddy;  }
    const Stats& getStats()   const { return stats;  }

    // Const inventory access — allows EncounterFactory / DataManager to iterate
    // items without being able to modify ownership.
    const Inventory<unique_ptr<Item>>& getInventory() const { return inventory; }
};