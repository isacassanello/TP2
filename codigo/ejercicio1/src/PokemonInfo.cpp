#include "../include/PokemonInfo.h"

PokemonInfo::PokemonInfo(string tipo, string des, map<string, int> ataques, array<int, 3> experiencia)
    : tipoPokemon(tipo), descripcion(des), ataquesDisponiblesPorNivel(ataques), experienciaProximoNivel(experiencia) {}

string PokemonInfo::getTipoPokemon() { return tipoPokemon; }

string PokemonInfo::getDescripcion() { return descripcion; }

map<string, int> PokemonInfo::getAtaques() { return ataquesDisponiblesPorNivel; }

array<int, 3> PokemonInfo::getExperiencia() { return experienciaProximoNivel; }

void PokemonInfo::imprimirPokemonInfo(const string& nombrePokemon, int experiencia){
    cout << "Nombre: " << nombrePokemon << endl;
    cout << "Experiencia: " << experiencia << endl;
    cout << "Tipo: " << tipoPokemon << endl;
    cout << "Descripcion: " << descripcion << endl;

    cout << "Ataques disponibles por nivel:" << endl;
    for (const auto& ataque : ataquesDisponiblesPorNivel) {
        cout << "  - " << ataque.first << ": " << ataque.second << " daño" << endl;
    }

    cout << "Experiencia necesaria por nivel: ";
    for (int exp : experienciaProximoNivel) {
        cout << exp << " ";
    }
    cout << endl;
}