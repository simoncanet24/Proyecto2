#pragma once
#include "SistemaGeneral.h"
#include "Inventario.h"
#include "Objetos.h"

class Jugador : public SistemaGeneral {
private:
    int nivel;
    int experiencia;
    int hpBase;
    Inventario<Objetos*>* inventario;

public:
    Jugador(const string& nombre, int hp, int ataque, Inventario<Objetos*>* invent)
        : SistemaGeneral(nombre, hp, ataque),
          nivel(1), experiencia(0), hpBase(hp),
          inventario(invent) {}

    void agregarObjeto(Objetos* obj) {
        inventario->agregar(obj);
    }

    // Usa el primer curativo disponible en el inventario
    void usarSanador() {
        if (inventario->isEmpty()) {
            cout << "No tienes curativos en el inventario." << endl;
            return;
        }
        Objetos* obj = inventario->getObjeto(0);
        hp += obj->getValorSanacion();
        cout << "Usaste " << obj->getNombre() << " y recuperaste "
             << obj->getValorSanacion() << " HP. HP actual: " << hp << endl;
        inventario->eliminar(0);
    }

    // Gana experiencia y sube de nivel si llega a 50
    void ganaExperiencia(int cantidad) {
        experiencia += cantidad;
        if (experiencia >= 50) {
            experiencia -= 50;
            nivel++;
            ataque += 5;
            hpBase += 5;
            hp = hpBase;
            cout << nombre << " subio al nivel " << nivel << "!" << endl;
            cout << "Tu vida se reseteo a " << hp << " HP." << endl;
        }
    }

    int getNivel()      const { return nivel; }
    int getExperiencia() const { return experiencia; }

    // Muestra el inventario
    void mostrarInventario() const {
        if (inventario->isEmpty()) {
            cout << "Inventario vacio." << endl;
            return;
        }
        cout << "--- Inventario de " << nombre << " ---" << endl;
        for (int i = 0; i < inventario->tam(); i++) {
            cout << "  [" << i << "] " << *inventario->getObjeto(i) << endl;
        }
    }
};
