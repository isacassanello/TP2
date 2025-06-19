#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
using namespace std;

extern mutex mutex_cout; // se utiliza mutex para que no se superpongan los mensajes

class Dron{
    private:
        unsigned int id;

        // las zonas las hago referencias para que todas los drones vean que se bloqueo
        mutex& zona_izq;
        mutex& zona_der;

    public:
        Dron();
        Dron(unsigned int id, mutex& izq, mutex& der);

        // functor, permite que una instancia de dron se ejecute como un hilo
        void operator()();

        ~Dron() = default;
};