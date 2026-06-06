#pragma once
#include <iostream>
#include <string>
using namespace std;

class Objetos {
private:
    string nombre;
    string descripcion;
    int valorSanacion; // cuanto sana al usarse

public:
    Objetos(const string& nombre, const string& desc, int sanacion)
        : nombre(nombre), descripcion(desc), valorSanacion(sanacion) {}

    string getNombre()      const { return nombre; }
    string getDescripcion() const { return descripcion; }
    int getValorSanacion()  const { return valorSanacion; }

    friend ostream& operator<<(ostream& os, const Objetos& o) {
        os << o.nombre << " (" << o.descripcion << ", +" << o.valorSanacion << " HP)";
        return os;
    }
};

