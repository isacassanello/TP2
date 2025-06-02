#include "../include/Pokemon.h"
#include "../include/PokemonInfo.h"
#include "../include/Pokedex.h"

int main(){
    Pokedex miPokedex;

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

    miPokedex.agregarPokemon(squirtle, infoSquirtle);
    miPokedex.agregarPokemon(bulbasaur, infoBulbasaur);
    miPokedex.agregarPokemon(charmander, infoCharmander);

    miPokedex.mostrarTodos();

    miPokedex.mostrar(squirtle);
    miPokedex.mostrar(pikachu);

    return 0;
}