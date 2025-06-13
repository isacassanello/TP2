#pragma once
#include <iostream>
#include <string>
#include <array>
#include <map>
#include "pokemon.h"
using namespace std;

class PokemonInfo{
    private:
        string tipoPokemon;
        string descripcion;

        // mapea nombres de ataques a un valor entero de daño
        map<string, int> ataquesDisponiblesPorNivel;
        
        // array fijo de 3 elementos que indica la experiencia requerida para alcanzar cada uno de los niveles 1, 2 y 3
        array<int, 3> experienciaProximoNivel;

    public:
        PokemonInfo() = default;
        PokemonInfo(string tipo, string des, map<string, int> ataques, array<int, 3> experiencia);

        // metodos getter para acceder a los atributos privados desde fuera de la clase
        string getTipoPokemon();
        string getDescripcion();
        map<string, int> getAtaques();
        array<int, 3> getExperiencia();

        void imprimirPokemonInfo(const string& nombrePokemon, int experiencia);

        // metodos para guardar (serializar) o leer (deserializar) los datos del Pokemon en/desde un archivo binario
        void serializar(ofstream& out) const;
        void deserializar(ifstream& in);

        ~PokemonInfo() = default;
};