#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Pokemon{
    private:
        string nombre;
        int experiencia;

    public:
        Pokemon() = default;
        Pokemon(const string& n, int e);

        // getters
        string getNombre() const;
        int getExperiencia()const;

        // Sobrecarga para comparar en unordered_map
        bool operator==(const Pokemon& other) const;

        void imprimirPokemon();

        void serializar(ofstream& out) const;
        void deserializar(ifstream& in);

        ~Pokemon() = default;
};

// Cuando usás un std::unordered_map, el compilador necesita una función hash para calcular en qué casillero de la tabla colocar cada clave.
// entonces necesitás #include <functional> porque std::hash está definido ahí.