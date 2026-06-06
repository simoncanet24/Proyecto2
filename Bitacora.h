#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Bitacora {
private:
    vector<string> eventos;

public:
    void datos(const string& dato) {
        eventos.push_back(dato);
    }

    void save(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open())
            throw runtime_error("No se pudo abrir el archivo de bitacora: " + filename);
        for (const auto& e : eventos)
            file << e << "\n";
    }

    const vector<string>& getEventos() const { return eventos; }
};
