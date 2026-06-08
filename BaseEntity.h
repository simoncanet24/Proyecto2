#pragma once
#include <iostream>
#include <string>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// BaseEntity
//
// Shared state and core combat interface for every combatant in the park.
// Player and Enemy derive from this via public inheritance (upcasting).
//
// Design notes:
//   • takeDamage() is virtual so Player can override it to pass incoming
//     damage through its Buddy's damage-reduction filter before applying it.
//     (Open/Closed Principle — adding Buddy behaviour without touching Enemy.)
//   • The virtual destructor satisfies the Rule of Five's first obligation
//     when a class is used polymorphically; the remaining four operations
//     are left to the compiler (all members are trivially copyable/movable).
//   • 'hp' is protected — derived classes (Player) may clamp or reset it
//     directly without exposing a public setter to unrelated code.
// ─────────────────────────────────────────────────────────────────────────────
class BaseEntity {
protected:
    string name;
    int    hp;
    int    damage;

public:
    // Default: used when DataManager falls back to safe defaults on corrupt save.
    BaseEntity()
        : name("Unknown"), hp(100), damage(10) {}

    BaseEntity(const string& name, int hp, int damage)
        : name(name), hp(hp), damage(damage) {}

    // Virtual destructor — required for correct polymorphic deletion.
    virtual ~BaseEntity() = default;

    // ── Accessors ─────────────────────────────────────────────────────────────
    string getName()   const { return name;   }
    int    getHp()     const { return hp;     }
    int    getDamage() const { return damage; }

    // Hard lower-bound of 0 — HP should never go negative.
    void setHp(int newHp) { hp = (newHp > 0) ? newHp : 0; }

    // Declared virtual: Player overrides this to apply Buddy damage reduction.
    virtual void takeDamage(int dmg) {
        hp -= dmg;
        if (hp < 0) hp = 0;
    }

    bool isAlive() const { return hp > 0; }

    // Operator overload — used by SistemaCombate-equivalent classes and in
    // Player::operator<<, allowing  cout << player  anywhere.
    friend ostream& operator<<(ostream& os, const BaseEntity& e) {
        os << "[" << e.name << "]"
           << "  HP: "  << e.hp
           << "  |  DMG: " << e.damage;
        return os;
    }
};