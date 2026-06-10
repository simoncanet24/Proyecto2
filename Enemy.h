#pragma once
#include <array>
#include <string>
#include "BaseEntity.h"
using namespace std;


// ─────────────────────────────────────────────────────────────────────────────
// Enemy
//
// A hostile entity encountered in the abandoned theme park.
// HP and damage are provided externally (EncounterFactory randomises them
// in [35, 90] and [8, 20] respectively) — Enemy itself is just the data.
//
// Eight named archetypes are enumerated so EncounterFactory can select one
// at random and construct the right name automatically.
//
// Flee threshold:
//   isFleeThreshold() returns true when HP ≤ 10% of starting HP.
//   The actual 10% flee roll is performed inside EnemyEncounter, keeping
//   random-number logic centralised there rather than scattered in Entity classes.
// ─────────────────────────────────────────────────────────────────────────────
class Enemy : public BaseEntity {
public:
    // Eight archetypes for the abandoned-park setting.
    // Explicit integral values guarantee TYPE_NAMES array indices stay in sync.
    enum class Type {
        PHANTOM_CLOWN    = 0,
        RUSTED_AUTOMATON = 1,
        LOST_SOUL        = 2,
        CARNIVAL_SPECTER = 3,
        SHADOW_PUPPETEER = 4,
        HOLLOW_MANNEQUIN = 5,
        MIRROR_WRAITH    = 6,
        DECREPIT_JESTER  = 7
    };

    // Parallel name table — index matches the enum's underlying int value.
    // constexpr + inline definition (C++17/20) avoids a separate .cpp definition.
    static constexpr array<const char*, 8> TYPE_NAMES = {
        "Phantom Clown",
        "Rusted Automaton",
        "Lost Soul",
        "Carnival Specter",
        "Shadow Puppeteer",
        "Hollow Mannequin",
        "Mirror Wraith",
        "Decrepit Jester"
    };

private:
    int  maxHp;  // retained to compute the 10% flee threshold without float division
    Type type;

public:
    // 'hp' and 'dmg' are supplied by EncounterFactory with randomised values.
    Enemy(Type t, int hp, int dmg)
        : BaseEntity(TYPE_NAMES[static_cast<int>(t)], hp, dmg),
          maxHp(hp),
          type(t) {}

    // ── Accessors ─────────────────────────────────────────────────────────────
    Type getType()  const { return type;  }
    int  getMaxHp() const { return maxHp; }

    // True when remaining HP ≤ 10% of starting HP (integer arithmetic, no floats).
    // EnemyEncounter calls this each turn to decide whether to attempt a flee roll.
    bool isFleeThreshold() const {
        return hp * 10 <= maxHp;
    }
};