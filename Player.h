#pragma once
#include <algorithm>   // std::min, std::max
#include <memory>      // std::unique_ptr
#include <vector>
#include <string>
#include "BaseEntity.h"
#include "Item.h"
#include "Inventory.h"
using namespace std;




enum class BuddyType { NONE, ENZO, GLOOP };


class Buddy {
    BuddyType type;
    string    name;

public:

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

    int filterDamage(int incomingDmg) const {
        if (type == BuddyType::ENZO)
            return static_cast<int>(incomingDmg * 0.75);
        return incomingDmg;
    }

    bool hasDropBonus() const { return type == BuddyType::ENZO; }
};

class Player : public BaseEntity {
public:

    struct Stats {
        int            enemiesSlain         = 0;
        int            encountersCompleted  = 0;
        int            totalDamageDealt     = 0;
        int            totalHealingReceived = 0;
        vector<string> encounterLog;
    };

private:
    int                         baseHp;
    Buddy                       buddy;
    Inventory<unique_ptr<Item>> inventory;
    Stats                       stats;

public:
    Player(const string& name, int hp, int dmg,
           BuddyType buddyType = BuddyType::NONE)
        : BaseEntity(name, hp, dmg),
          baseHp(hp),
          buddy(buddyType),
          inventory(4) {}


    void takeDamage(int dmg) override {
        int effective = buddy.filterDamage(dmg);
        BaseEntity::takeDamage(effective);
    }

    int heal(int amount) {
        int before = hp;
        hp = min(hp + amount, baseHp);
        return hp - before;
    }

    void setHp(int HP) { hp = min(HP, baseHp); }

    void boostDamage() {
        damage = max(damage + 1, static_cast<int>(damage * 1.05));
    }

    void dismissBuddy() { buddy = Buddy(BuddyType::NONE); }

    void setBuddy(BuddyType t) { buddy = Buddy(t); }

    void addItem(unique_ptr<Item> item) {
        inventory.add(std::move(item));
    }

    int applyItem(int index) {
        auto item    = inventory.remove(index);
        int  healAmt = (item->getHealPercent() * baseHp) / 100;
        int  actual  = heal(healAmt);
        stats.totalHealingReceived += actual;
        return actual;
    }

    const Item* peekItem(int index) const {
        if (index < 0 || index >= inventory.size()) return nullptr;
        return inventory.peek(index).get();   // .get() = non-owning view
    }

    bool hasItems()  const { return !inventory.isEmpty(); }
    int  itemCount() const { return inventory.size(); }

    void recordEnemySlain()                  { ++stats.enemiesSlain; }
    void recordDamageDealt(int dmg)          { stats.totalDamageDealt += dmg; }
    void recordEncounter(const string& label) {
        ++stats.encountersCompleted;
        stats.encounterLog.push_back(label);
    }

    int          getBaseHp()  const { return baseHp; }
    const Buddy& getBuddy()   const { return buddy;  }
    const Stats& getStats()   const { return stats;  }

    const Inventory<unique_ptr<Item>>& getInventory() const { return inventory; }
};