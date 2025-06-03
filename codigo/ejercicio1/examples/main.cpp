#include "../include/Pokemon.h"
#include "../include/PokemonInfo.h"
#include "../include/Pokedex.h"

int main(){
    cout << "\n -------------------------------------------------" << endl;
    
    // El nombre del archivo debe ser pasado al constructor sobrecargado.
    Pokedex miPokedex("pokedex_data.bin");

    // muestro los datos cargados desde archivo
    cout << "\n====== Pokedex cargado desde archivo ======" << endl;
    miPokedex.mostrarTodos();

    // caso 1
    Pokemon squirtle("Squirtle", 100);
    PokemonInfo infoSquirtle("Agua", "Una tortuga pequeña que lanza chorros de agua.",  
                {{"Pistola Agua", 4}, {"Hidrobomba", 6}, {"Danza Lluvia", 5}}, 
                {0, 400, 1000});  
    
    // caso 2
    Pokemon bulbasaur("Bulbasaur", 270); 
    PokemonInfo infoBulbasaur("Planta", "Tiene una semilla en su lomo que crece con el tiempo", 
                {{"Latigazo", 4}, {"Hoja Afilada", 6}, {"Rayo Solar", 5}}, 
                {0, 300, 1100});

    // caso 3
    Pokemon charmander("Charmander", 633);
    PokemonInfo infoCharmander("Fuego", "Una lagartija con una llama en su cola", 
                {{"Ascuas", 4}, {"Lanzallamas", 6}, {"Giro Fuego", 5}}, 
                {0, 250, 1300});

    // caso 4 para probar funcion mostrar()
    Pokemon pikachu("Pikachu", 390); 

    // agregar los 3 pokemons (si ya estan, los pisa y reserializa todo)
    miPokedex.agregarPokemon(squirtle, infoSquirtle);
    miPokedex.agregarPokemon(bulbasaur, infoBulbasaur);
    miPokedex.agregarPokemon(charmander, infoCharmander);

    cout << "\n====== Pokedex luego de agregar los Pokemon ======" << endl;
    miPokedex.mostrarTodos();

    cout << "\n====== Busqueda individual ======" << endl;
    miPokedex.mostrar(squirtle);
    miPokedex.mostrar(pikachu);

    cout << "\n -------------------------------------------------" << endl;

    return 0;
}