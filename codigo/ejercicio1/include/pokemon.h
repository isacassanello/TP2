#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Pokemon{
    private:
        string nombre;
        unsigned int experiencia;

    public:
        Pokemon() = default;               
        Pokemon(const string& n, unsigned int e);        

        // metodos getter para acceder a los atributos privados desde fuera de la clase
        string getNombre() const;
        unsigned int getExperiencia() const;

        // sobrecarga para comparar en unordered_map -> comparacion de dos Pokemon por su nombre y experiencia
        bool operator==(const Pokemon& other) const;

        void imprimirPokemon() const;

        // metodos para guardar (serializar) o leer (deserializar) los datos del Pokemon en/desde un archivo binario
        void serializar(ofstream& out) const;
        void deserializar(ifstream& in);

        ~Pokemon() = default;
};