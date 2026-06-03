#include <iostream>
#include <fstream>
#pragma once
#include <vector>
using namespace std;

class Bitacora {
private:
vector<string> eventos;
public:
    void datos(const string& dato)
    {
        eventos.push_back(dato);
    }
    void save(const string& filename)
    {
        ofstream file(filename);
        for (auto& e: eventos)
        {
            file << e << endl;
        }
    }

};



