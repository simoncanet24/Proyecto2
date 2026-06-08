#pragma once
#include <vector>
#include <memory>      // std::move (via <utility>), unique_ptr used by callers
#include <stdexcept>   // std::out_of_range
#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// Inventory<T>
//
// A fixed-capacity sequential container, primarily intended to hold
// std::unique_ptr<Item>.  Generalised as a template so any T can be stored
// (Generic Programming topic), but the entire API is designed around the
// move-only ownership semantics of unique_ptr.
//
//  add(T)        — transfers ownership IN  (caller must std::move a unique_ptr)
//  remove(int)   — transfers ownership OUT (returns T by value via move)
//  peek(int)     — const ref for inspection; no ownership changes hands
//
// Why the three-method split?
//   Separating "look" (peek) from "take" (remove) prevents accidental ownership
//   transfers during display loops, and makes call sites self-documenting.
//
// Iterator support lets range-based for loops work:
//   for (const auto& item : inventory) { cout << *item; }
// ─────────────────────────────────────────────────────────────────────────────
template <typename T>
class Inventory {
    vector<T> items;
    int       capacity;

public:
    explicit Inventory(int cap) : capacity(cap) {}

    // ── Core operations ───────────────────────────────────────────────────────

    // Transfers ownership of 'item' into the inventory.
    // For  T = unique_ptr<Item>: caller writes  inventory.add(std::move(ptr));
    // Returns false and prints a warning if the inventory is already full.
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