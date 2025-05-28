#pragma once
#include <iostream>
#include <string>
using namespace std;

class Pokemon{
    private:
        string nombre;
        int experiencia;

    public:
        Pokemon(const string& n, int e);

        // getters
        string getNombre();
        int getExperiencia();

        void imprimir();
};

class PokemonInfo{
    
};