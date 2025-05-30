#include "../headers/Pokemon.h"


Pokemon::Pokemon(const std::string& n, int e) : nombre(n), experiencia(e) {}

string Pokemon::getNombre() const { return nombre; }

int Pokemon::getExperiencia() { return experiencia; }

bool Pokemon::operator==(const Pokemon& other) const {
    return nombre == other.nombre; // solo comparamos por nombre como dice el enunciado
}

void Pokemon::imprimirPokemon() {
    cout << "Nombre: " << nombre << ", Experiencia: " << experiencia;
}