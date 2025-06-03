#pragma once
#include <unordered_map>
#include <functional>
#include "Pokemon.h"
#include "PokemonInfo.h"

// hash asociado a Pokemon, usando solo el nombre
struct PokemonHash {
    size_t operator()(const Pokemon& p) const {
        return hash<string>()(p.getNombre());
    }
};

/*
hash<string>:
Es un "functor" o objeto función que sabe cómo transformar un std::string en un número entero (size_t) 
de forma única y reproducible. Es decir: si le pasás "Pikachu", siempre va a devolver el mismo número hash.

"Usá la función hash estándar para strings y aplicala al nombre del Pokémon".
*/

class Pokedex{
    private:
        unordered_map<Pokemon, PokemonInfo, PokemonHash> pokedex;
        string nombreArchivo;
    
    public:
        Pokedex() = default;

        // metodo para agregar un pokemon al pokedex
        void agregarPokemon(const Pokemon& p, const PokemonInfo& info);

        Pokedex(const string& archivo); // nuevo

        void mostrarTodos();
        
        void mostrar(const Pokemon& p);

        void serializar() const;
        void deserializar();

        ~Pokedex() = default;
};