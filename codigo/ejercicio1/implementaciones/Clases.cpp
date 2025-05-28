#include "Clases.h"

Pokemon::Pokemon(const std::string& n, int e) : nombre(n), experiencia(e) {}

string Pokemon::getNombre() { return nombre; }

int Pokemon::getExperiencia() { return experiencia; }

void Pokemon::imprimir() {
    cout << "Nombre: " << nombre << ", Experiencia: " << experiencia;
}

