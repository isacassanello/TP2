#pragma once
#include <unordered_map>
#include <functional>
#include "pokemon.h"
#include "pokemonInfo.h"

// functor que define como obtener el hash de un Pokemon
// usa solo el nombre del Pokemon como clave de hash, ignorando la experiencia (por eso dos Pokemon con distinto nivel pero mismo nombre son tratados igual en la pokedex)
struct PokemonHash {
    size_t operator()(const Pokemon& p) const {
        return hash<string>()(p.getNombre());
    }
};

/*
ESTO METERLO EN EL INFORME

hash<string>:
Es un "functor" que sabe cómo transformar un std::string en un número entero (size_t) 
de forma única y reproducible. Es decir: si le pasás "Pikachu", siempre va a devolver el mismo número hash.

"Usá la función hash estándar para strings y aplicala al nombre del Pokémon".
*/

class Pokedex{
    private:
        // contenedor principal -> asocia un Pokemon (clave) con su PokemonInfo (valor)
        unordered_map<Pokemon, PokemonInfo, PokemonHash> pokedex;
        
        // nombre del archivo donde se guarda o carga la informacion
        string nombreArchivo;
    
    public:
        Pokedex() = default;

        // metodo para agregar un Pokemon y su info al pokedex
        void agregarPokemon(const Pokemon& p, const PokemonInfo& info);

        // constructor sobrecargado que inicializa la pokedex desde un archivo (carga automatica = deserializacion)
        Pokedex(const string& archivo); 

        // imprime todos los Pokemon cargados en la pokedex, recorriendo el unordered_map
        void mostrarTodos();
        
        // muestra la informacion de un Pokemon especifico si este en la pokedex
        void mostrar(const Pokemon& p);

        // serializa (guarda) y deserializa (carga) la pokedex entera en un archivo binario
        // esto permite que al reiniciar el programa se recupere el estado anterior
        void serializar() const;
        void deserializar();

        ~Pokedex() = default;
};