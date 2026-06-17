#pragma once
#include <vector>
#include <memory>      // std::move (via <utility>), unique_ptr used by callers
#include <stdexcept>   // std::out_of_range
#include <iostream>
using namespace std;


template <typename T>
class Inventory {
    vector<T> items;
    int       capacity;

public:
    explicit Inventory(int cap) : capacity(cap) {}

    bool add(T item) {
        if (static_cast<int>(items.size()) >= capacity) {
            cout << "[Inventory] Full — item was not added.\n";
            return false;
        }
        items.push_back(std::move(item));
        return true;
    }

    T remove(int index) {
        if (index < 0 || index >= static_cast<int>(items.size()))
            throw out_of_range("Inventory::remove — index out of range.");

        T item = std::move(items[index]);
        items.erase(items.begin() + index);
        return item;
    }

    const T& peek(int index) const {
        if (index < 0 || index >= static_cast<int>(items.size()))
            throw out_of_range("Inventory::peek — index out of range.");
        return items[index];
    }

    bool isEmpty()     const { return items.empty(); }
    bool isFull()      const { return static_cast<int>(items.size()) >= capacity; }
    int  size()        const { return static_cast<int>(items.size()); }
    int  getCapacity() const { return capacity; }

    typename vector<T>::iterator       begin()        { return items.begin();  }
    typename vector<T>::iterator       end()          { return items.end();    }
    typename vector<T>::const_iterator begin()  const { return items.cbegin(); }
    typename vector<T>::const_iterator end()    const { return items.cend();   }
};