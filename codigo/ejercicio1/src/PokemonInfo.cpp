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

// serializa un objeto PokemonInfo a un archivo binario
// guarda: tipo, descripcion, ataques (nombre y daño), y experiencia necesaria por nivel
void PokemonInfo::serializar(ofstream& out) const{
    // ---  Serializar tipoPokemon ---
    size_t lenTipo = tipoPokemon.size();
    out.write(reinterpret_cast<char*>(&lenTipo), sizeof(lenTipo));
    out.write(tipoPokemon.c_str(), lenTipo);

    // --- Serializar descripcion ---
    size_t lenDesc = descripcion.size();
    out.write(reinterpret_cast<char*>(&lenDesc), sizeof(lenDesc));
    out.write(descripcion.c_str(), lenDesc);

    // --- Serializar map de ataques (clave: nombre, valor: daño) ---
    size_t cantidadAtaques = ataquesDisponiblesPorNivel.size();
    out.write(reinterpret_cast<char*>(&cantidadAtaques), sizeof(cantidadAtaques));

    for (const auto& [nombre, danio] : ataquesDisponiblesPorNivel) {
        size_t lenNombre = nombre.size();
        out.write(reinterpret_cast<char*>(&lenNombre), sizeof(lenNombre));
        out.write(nombre.c_str(), lenNombre);
        out.write(reinterpret_cast<const char*>(&danio), sizeof(danio));
    }

    // --- Serializar array de experiencia por nivel ---
    for (int exp : experienciaProximoNivel) {
        out.write(reinterpret_cast<char*>(&exp), sizeof(exp));
    }
}

// deserializa un objeto PokemonInfo desde un archivo binario
// reconstruye: tipo, descripcion, map de ataques y array de experiencia
void PokemonInfo::deserializar(ifstream& in) {
    // --- Leer tipoPokemon ---
    size_t lenTipo;
    in.read(reinterpret_cast<char*>(&lenTipo), sizeof(lenTipo));
    tipoPokemon.resize(lenTipo); // para reservar espacio en el string antes de leer los caracteres desde el archivo binario
    in.read(&tipoPokemon[0], lenTipo);

    // --- Leer descripcion ---
    size_t lenDesc;
    in.read(reinterpret_cast<char*>(&lenDesc), sizeof(lenDesc));
    descripcion.resize(lenDesc);
    in.read(&descripcion[0], lenDesc);

    // --- Leer map de ataques ---
    size_t cantidadAtaques;
    in.read(reinterpret_cast<char*>(&cantidadAtaques), sizeof(cantidadAtaques));
    ataquesDisponiblesPorNivel.clear(); // para vaciar el map antes de cargar nuevos datos desde el archivo binario

    for (size_t i = 0; i < cantidadAtaques; ++i) {
        size_t lenNombre;
        in.read(reinterpret_cast<char*>(&lenNombre), sizeof(lenNombre));

        string nombre(lenNombre, ' ');
        in.read(&nombre[0], lenNombre);

        int danio;
        in.read(reinterpret_cast<char*>(&danio), sizeof(danio));

        ataquesDisponiblesPorNivel[nombre] = danio;
    }

    // --- Leer array de experiencia por nivel ---
    for (int& exp : experienciaProximoNivel) {
        in.read(reinterpret_cast<char*>(&exp), sizeof(exp));
    }
}