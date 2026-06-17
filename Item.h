#pragma once
#include <iostream>
#include <string>
using namespace std;


class Item {
public:
    enum class Type { MEDKIT, BANDAGES, HEALING_HERB };

private:
    string name;
    string description;
    int    healPercent;
    Type   type;

public:
    Item(const string& name, const string& desc, int healPercent, Type type)
        : name(name), description(desc), healPercent(healPercent), type(type) {}

    string getName()        const { return name;        }
    string getDescription() const { return description; }
    int    getHealPercent() const { return healPercent; }
    Type   getType()        const { return type;        }

    friend ostream& operator<<(ostream& os, const Item& i) {
        os << i.name
           << "  [" << i.healPercent << "% HP]  — "
           << i.description;
        return os;
    }
};