#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template <typename T>
class Inventario {
private:
    vector<T> objetos;
    int capacidad;

public:
    explicit Inventario(int capacidad) : capacidad(capacidad) {}

    void agregar(T objeto) {
        if ((int)objetos.size() < capacidad) {
            objetos.push_back(objeto);
        } else {
            cout << "Inventario lleno. No se puede agregar el objeto." << endl;
        }
    }

    void eliminar(int index) {
        if (index >= 0 && index < (int)objetos.size()) {
            objetos.erase(objetos.begin() + index);
        } else {
            cout << "Indice invalido. No se puede eliminar el objeto." << endl;
        }
    }

    // Retorna puntero nulo solo si T es un tipo puntero; para tipos valor lanza excepcion
    T getObjeto(int index) {
        if (index >= 0 && index < (int)objetos.size()) {
            return objetos[index];
        }
        throw out_of_range("Indice invalido en getObjeto.");
    }

    // operator[] — lanza excepcion si el indice esta fuera de rango (logica corregida)
    T& operator[](int index) {
        if (index < 0 || index >= (int)objetos.size()) {
            throw out_of_range("Indice fuera de rango en Inventario.");
        }
        return objetos[index];
    }

    bool isEmpty() const { return objetos.empty(); }
    bool isFull()  const { return (int)objetos.size() >= capacidad; }
    int  tam()     const { return (int)objetos.size(); }

    typename vector<T>::iterator begin() { return objetos.begin(); }
    typename vector<T>::iterator end()   { return objetos.end(); }
};
