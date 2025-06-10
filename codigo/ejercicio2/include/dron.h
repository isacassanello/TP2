#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

/*
    - Cada dron debe tomar control de dos zonas: la de su izquierda (i) y la de su derecha ((i+4)%5) 

    - Usamos mutexes para representar las zonas compartidas.

    - Cada dron es un hilo (thread) que:
        - Espera a poder bloquear las dos zonas con lock()
        - Despega (simulado con sleep_for(5s))
        - Libera las zonas (al salir del lock_guard)
*/

// PREGUNTAR SI PUEDE ESTAR EN EL SCOPE GLOBAL
extern mutex mutex_cout; // para que no se superpongan los mensajes en pantalla

class Dron{
    private:
        int id;
        // & porque todas las instancias de Dron deben compartir zonas comunes
        mutex& zona_izq;
        mutex& zona_der;

    public:
        Dron();
        Dron(int id, mutex& izq, mutex& der);

        // functor
        void operator()();

        ~Dron() = default;
};
