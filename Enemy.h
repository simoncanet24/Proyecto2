#pragma once
#include <array>
#include <string>
#include "BaseEntity.h"
using namespace std;


class Enemy : public BaseEntity {
public:
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
    int  maxHp;
    Type type;

public:
    Enemy(Type t, int hp, int dmg)
        : BaseEntity(TYPE_NAMES[static_cast<int>(t)], hp, dmg),
          maxHp(hp),
          type(t) {}

    Type getType()  const { return type;  }
    int  getMaxHp() const { return maxHp; }
    bool isFleeThreshold() const {
        return hp * 10 <= maxHp;
    }
};