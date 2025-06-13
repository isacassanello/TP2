#include "../include/pokedex.h"

void Pokedex::agregarPokemon(const Pokemon& p, const PokemonInfo& info){
    pokedex[p] = info;

    // si se cargo desde archivo (nombreArchivo no vacio), se guarda todo el contenido nuevamente
    if (!nombreArchivo.empty()) {
        ofstream out(nombreArchivo, ios::binary);
        serializar(); // guardamos siempre si se cargo desde archivo
        out.close();
    }
}

// al crear el pokedex con un archivo asociado, automaticamente se cargan los datos del archivo
Pokedex::Pokedex(const string& archivo)
    : nombreArchivo(archivo) {
    ifstream in(nombreArchivo, ios::binary);
    deserializar();
}

// imprime todos los Pokemon y su informacion
void Pokedex::mostrarTodos(){
    if (pokedex.empty()) {
        cout << "El pokedex esta vacio" << endl;
    }
    for (auto& poke : pokedex){
        cout << "\n------------------------" << endl;
        poke.second.imprimirPokemonInfo(poke.first.getNombre(), poke.first.getExperiencia());
        cout << "------------------------" << endl;

    }
}

// busca un Pokemon especifico y lo imprime
void Pokedex::mostrar(const Pokemon& p){
    auto aBuscar = pokedex.find(p);
    if (aBuscar != pokedex.end()){
        cout << "\n------------------------" << endl;
        cout << "Informacion de " << p.getNombre() << ": " << endl;
        aBuscar->second.imprimirPokemonInfo(p.getNombre(), p.getExperiencia());
        cout << "------------------------" << "\n" << endl;
    } else {
        cout << "¡Pokemon desconocido!" << endl;
    }
}

// serializa el contenido completo del pokedex a un archivo binario
// guarda primero la cantidad total de entradas, luego cada Pokemon y su info asociada
void Pokedex::serializar() const{
    ofstream out(nombreArchivo, ios::binary);

    // guarda cuantos elementos tiene la pokedex, para saber cuantos leer al deserializar
    size_t cantidad = pokedex.size();
    out.write(reinterpret_cast<char*>(&cantidad), sizeof(cantidad));
    
    // recorre todo el map y serializa cada entrada
    for (const auto& [poke, info] : pokedex) {
        poke.serializar(out); // guarda nombre y experiencia del Pokemon
        info.serializar(out); // guarda tipo, descripcion, ataques y experiencia por nivel
    } 
    out.close();
}

// deserializa el contenido del archivo binario para reconstruir el pokedex completo
// lee primero la cantidad total de entradas, y luego esa cantidad de pares Pokemon + PokemonInfo
void Pokedex::deserializar() {
    ifstream in(nombreArchivo, ios::binary);
    if (!in) return;

    // lee la cantidad total de elementos guardados en el archivo
    size_t cantidad = 0;
    in.read(reinterpret_cast<char*>(&cantidad), sizeof(cantidad));
    
    // lee esa cantidad de Pokemon + info uno por uno
    for (size_t i = 0; i < cantidad; ++i) {
        Pokemon p;
        PokemonInfo info;
        p.deserializar(in); // lee los datos del Pokemon
        info.deserializar(in); // lee los datos de su informacion
        pokedex[p] = info; // inserta en el map
    }
    in.close();
}