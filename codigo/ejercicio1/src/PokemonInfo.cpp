#include "../include/pokemonInfo.h"

PokemonInfo::PokemonInfo (const string& tipo, const string& des, const map<string, unsigned int>& ataques, const array<unsigned int, 3>& experiencia)
    : tipoPokemon(tipo), descripcion(des), ataquesDisponiblesPorNivel(ataques), experienciaProximoNivel(experiencia) {}

string PokemonInfo::getTipoPokemon() const{ return tipoPokemon; }

string PokemonInfo::getDescripcion() const{ return descripcion; }

map<string, unsigned int> PokemonInfo::getAtaques() const{ return ataquesDisponiblesPorNivel; }

array<unsigned int, 3> PokemonInfo::getExperiencia() const{ return experienciaProximoNivel; }

// imprime toda la informacion del Pokemon (tipo, ataques, experiencia por nivel)
void PokemonInfo::imprimirPokemonInfo(const string& nombrePokemon, unsigned int experiencia) const{
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
    // serializa tipoPokemon
    size_t lenTipo = tipoPokemon.size();
    out.write(reinterpret_cast<char*>(&lenTipo), sizeof(lenTipo));
    out.write(tipoPokemon.c_str(), lenTipo);

    // serializa descripcion 
    size_t lenDesc = descripcion.size();
    out.write(reinterpret_cast<char*>(&lenDesc), sizeof(lenDesc));
    out.write(descripcion.c_str(), lenDesc);

    // serializa la cantidad de ataques
    size_t cantidadAtaques = ataquesDisponiblesPorNivel.size();
    out.write(reinterpret_cast<char*>(&cantidadAtaques), sizeof(cantidadAtaques));

    // serializa cada ataque: nombre + daño
    for (const auto& [nombre, danio] : ataquesDisponiblesPorNivel) {
        size_t lenNombre = nombre.size();
        out.write(reinterpret_cast<char*>(&lenNombre), sizeof(lenNombre));
        out.write(nombre.c_str(), lenNombre);
        out.write(reinterpret_cast<const char*>(&danio), sizeof(danio));
    }

    // serializa experiencia por nivel (3 niveles)
    for (int exp : experienciaProximoNivel) {
        out.write(reinterpret_cast<char*>(&exp), sizeof(exp));
    }
}

// deserializa un objeto PokemonInfo desde un archivo binario
// reconstruye: tipo, descripcion, map de ataques y array de experiencia
void PokemonInfo::deserializar(ifstream& in) {
    // lee tipoPokemon 
    size_t lenTipo;
    in.read(reinterpret_cast<char*>(&lenTipo), sizeof(lenTipo));
    tipoPokemon.resize(lenTipo); // para reservar espacio en el string antes de leer los caracteres desde el archivo binario
    in.read(&tipoPokemon[0], lenTipo);

    // lee descripcion 
    size_t lenDesc;
    in.read(reinterpret_cast<char*>(&lenDesc), sizeof(lenDesc));
    descripcion.resize(lenDesc);
    in.read(&descripcion[0], lenDesc);

    // lee cantidad de ataques 
    size_t cantidadAtaques;
    in.read(reinterpret_cast<char*>(&cantidadAtaques), sizeof(cantidadAtaques));
    ataquesDisponiblesPorNivel.clear(); // para vaciar el map antes de cargar nuevos datos desde el archivo binario

    // lee cada ataque
    for (size_t i = 0; i < cantidadAtaques; ++i) {
        size_t lenNombre;
        in.read(reinterpret_cast<char*>(&lenNombre), sizeof(lenNombre));

        string nombre(lenNombre, ' ');
        in.read(&nombre[0], lenNombre);

        int danio;
        in.read(reinterpret_cast<char*>(&danio), sizeof(danio));

        ataquesDisponiblesPorNivel[nombre] = danio;
    }

    // lee el array de experiencia por nivel 
    for (unsigned int& exp : experienciaProximoNivel) {
        in.read(reinterpret_cast<char*>(&exp), sizeof(exp));
    }
}