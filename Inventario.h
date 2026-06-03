#include <iostream>
#include <string>
#include <vector>
using namespace std;
#pragma once

template <typename T>

class Inventario {
private:
    vector<T> objetos;
    int capacidad;
public:
    Inventario(int capacidad) {
        this->capacidad = capacidad;
    }
    void agregar(T objeto) {
        if (objetos.size() < capacidad) {
            objetos.push_back(objeto);
        } else {
            cout << "Inventario lleno. No se puede agregar el objeto." << endl;
        }
    }
    void eliminar(int index) {
        if (index >= 0 && index < objetos.size()) {
            objetos.erase(objetos.begin() + index);
        } else {
            cout << "Índice inválido. No se puede eliminar el objeto." << endl;
        }
    }
    T getObjeto(int index) {
        if (index >= 0 && index < objetos.size()) {
            return objetos[index];
        } else {
            cout << "Índice inválido. No se puede obtener el objeto." << endl;
            return nullptr; // o algún valor predeterminado
        }
    }

    T& operator[](int index)
    {
        if (index >= 0 && index < objetos.size())
        {
            throw out_of_range("Cantidad de objetos no valido");
        }
    }

    bool isEmpty() const{return objetos.empty();}
    bool isFull() const{return objetos.size() >= capacidad;}
    int tam() const{return objetos.size();}

    typename vector<T>::iterator begin(){return objetos.begin();}
    typename vector<T>::iterator end(){return objetos.end();}



};



