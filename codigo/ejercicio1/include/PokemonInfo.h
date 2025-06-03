#pragma once
#include <iostream>
#include <string>
#include <array>
#include <map>
#include "Pokemon.h"
using namespace std;

class PokemonInfo{
    private:
        string tipoPokemon;
        string descripcion;
        // MAP -> UN KEY A UN VALUE
        // MULTIMAP NO -> PARA NO TENER dos ataques con distintos daños
        map<string, int> ataquesDisponiblesPorNivel;
        // sabemos que para alcanzar cada nivel se necesita una exoeriencia fija -> cada posicion del array es la experiencia para el nivel, respectivamente
        array<int, 3> experienciaProximoNivel;


    public:
        PokemonInfo() = default;
        PokemonInfo(string tipo, string des, map<string, int> ataques, array<int, 3> experiencia);

        string getTipoPokemon();
        string getDescripcion();

        map<string, int> getAtaques();
        array<int, 3> getExperiencia();

        void imprimirPokemonInfo(const string& nombrePokemon, int experiencia);

        void serializar(ofstream& out) const;
        void deserializar(ifstream& in);

        ~PokemonInfo() = default;
};