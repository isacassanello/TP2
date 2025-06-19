#include "../include/dron.h"

int main(){
    const int N = 5;
    vector<thread> drones; // vector para almacenar los hilos de cada dron 
    vector<mutex> zonas(N); // se utiliza un vector de mutex para bloquear las zonas de manera independiente 

    // se lanza un hilo por cada dron
    for (int i = 0; i < N; i++){
        int zona_izq = i;
        int zona_der = (i + 1) % N;
        // se crea un hilo con el comportamiento del dron, pasandole las zonas que necesita
        drones.emplace_back(Dron(i, zonas[zona_izq], zonas[zona_der]));
    }

    // espera a que todos los drones finalicen 
    for (auto& t: drones) t.join();

    {
        // mutex para evitar superposicion de cout
        lock_guard<mutex> lock_cout(mutex_cout);
        cout << "Todos los drones alcanzaron los 10 metros de altura" << endl;  
    }

    return 0;
}