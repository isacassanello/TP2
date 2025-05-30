#include "../headers/Pokedex.h"


void Pokedex::agregarPokemon(const Pokemon& p, const PokemonInfo& info){
    pokedex[p] = info;
}

void Pokedex::mostrarTodos(){
    if (pokedex.empty()) {
        cout << "El pokedex esta vacio";
    }

    for (auto& poke : pokedex){
        poke.second.imprimirPokemonInfo();
    }
}

void Pokedex::mostrar(const Pokemon& p){
    auto aBuscar = pokedex.find(p);
    if (aBuscar != pokedex.end()){
        cout << "Informacion de " << p.getNombre() << ": " << endl;
        aBuscar->second.imprimirPokemonInfo();
    } else {
        cout << "¡Pokemon desconocido!" << endl;
    }
}