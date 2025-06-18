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

        // mapea nombres de ataques a un valor entero (positivo) de daño
        map<string, unsigned int> ataquesDisponiblesPorNivel;
        
        // array fijo de 3 elementos que indica la experiencia (numero entero positivo) requerida para alcanzar cada uno de los niveles 1, 2 y 3
        array<unsigned int, 3> experienciaProximoNivel;

    public:
        PokemonInfo() = default;
        PokemonInfo(const string& tipo, const string& des, const map<string, unsigned int>& ataques, const array<unsigned int, 3>& experiencia);
    
        // metodos getter para acceder a los atributos privados desde fuera de la clase
        string getTipoPokemon() const;
        string getDescripcion() const;
        map<string, unsigned int> getAtaques() const;
        array<unsigned int, 3> getExperiencia() const;

        void imprimirPokemonInfo(const string& nombrePokemon, unsigned int experiencia) const;

        // metodos para guardar (serializar) o leer (deserializar) los datos del Pokemon en/desde un archivo binario
        void serializar(ofstream& out) const;
        void deserializar(ifstream& in);

        ~PokemonInfo() = default;
};