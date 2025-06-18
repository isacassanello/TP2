#include "../include/pokemon.h"

Pokemon::Pokemon(const string& n, unsigned int e) : nombre(n), experiencia(e) {}

string Pokemon::getNombre() const{ return nombre; }

unsigned int Pokemon::getExperiencia() const{ return experiencia; }

bool Pokemon::operator==(const Pokemon& other) const{
    return nombre == other.nombre; // solo comparamos por nombre 
}

void Pokemon::imprimirPokemon() const{
    cout << "Nombre: " << nombre << ", Experiencia: " << experiencia;
}

// serializa el objeto Pokemon a un archivo binario
// escribe el nombre (con su longitud) y la experiencia del Pokemon
void Pokemon::serializar(ofstream& out) const{
    size_t len = nombre.size(); // guardo la longitud del nombre para saber cuantos caracteres hay que leer luego
    out.write(reinterpret_cast<char*>(&len), sizeof(len));
    out.write(nombre.c_str(), len); // escribe los caracteres del nombre
    out.write(reinterpret_cast<const char*>(&experiencia), sizeof(experiencia)); // escribe la experiencia
} 

// deserializa un objeto Pokemon desde un archivo binario
// reconstruye el nombre y la experiencia leyendo del archivo
void Pokemon::deserializar(ifstream& in) {
    size_t len;
    in.read(reinterpret_cast<char*>(&len), sizeof(len)); // lee la longitud del nombre
    nombre.resize(len); // redimensiona el string
    in.read(&nombre[0], len);  // lee el nombre
    in.read(reinterpret_cast<char*>(&experiencia), sizeof(experiencia)); // lee la experiencia
}