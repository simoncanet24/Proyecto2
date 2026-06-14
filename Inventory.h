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

    // Moves the element at 'index' out of the vector and returns it.
    // The slot is erased — the vector shrinks by one.
    // Throws std::out_of_range on invalid index.
    T remove(int index) {
        if (index < 0 || index >= static_cast<int>(items.size()))
            throw out_of_range("Inventory::remove — index out of range.");

        // Move item out first, leaving a moved-from (null) unique_ptr in place.
        T item = std::move(items[index]);
        // Erasing a moved-from unique_ptr is safe — it just removes a null slot.
        items.erase(items.begin() + index);
        return item;   // NRVO / move-return to caller
    }

    // Returns a const reference for read-only inspection — no ownership transfer.
    // For  T = unique_ptr<Item>: use  *inv.peek(i)  or  inv.peek(i)->method().
    // Throws std::out_of_range on invalid index.
    const T& peek(int index) const {
        if (index < 0 || index >= static_cast<int>(items.size()))
            throw out_of_range("Inventory::peek — index out of range.");
        return items[index];
    }

    // ── Queries ───────────────────────────────────────────────────────────────
    bool isEmpty()     const { return items.empty(); }
    bool isFull()      const { return static_cast<int>(items.size()) >= capacity; }
    int  size()        const { return static_cast<int>(items.size()); }
    int  getCapacity() const { return capacity; }

    // ── Iterator support (enables range-based for and <algorithm>) ────────────
    typename vector<T>::iterator       begin()        { return items.begin();  }
    typename vector<T>::iterator       end()          { return items.end();    }
    typename vector<T>::const_iterator begin()  const { return items.cbegin(); }
    typename vector<T>::const_iterator end()    const { return items.cend();   }
};