#include "../include/dron.h"

// mutex por defecto compartidos por los drones creados con el constructor por defecto
static mutex default_mutex_izq;
static mutex default_mutex_der;
Dron::Dron() : id(0), zona_izq(default_mutex_izq), zona_der(default_mutex_der) {}

Dron::Dron(int id, mutex& izq, mutex& der) : id(id), zona_izq(izq), zona_der(der) {}

void Dron::operator()(){
    {
        // protege el acceso a cout para que no se superpongan los mensajes 
        lock_guard<mutex> lock_cout(mutex_cout);
        cout << "Dron " << id << " esperando para despegar" << endl;
    }

    // bloqueo ambos mutex sin riesgo de deadlock
    // 'reserva' sus zonas para el despegue
    lock(zona_izq, zona_der);
    // no uso unique_lock porque no quiero lockearlo ni deslockearlo manualmente
    lock_guard<mutex> lock_izq(zona_izq, adopt_lock);
    lock_guard<mutex> lock_der(zona_der, adopt_lock);

    {
        lock_guard<mutex> lock_cout(mutex_cout);
        cout << "Dron " << id << " despegando..." << endl;  
    }

    // simulacion del tiempo de despegue 
    this_thread::sleep_for(chrono::seconds(5));

    {
        lock_guard<mutex> lock_cout(mutex_cout);
        cout << "Dron " << id << " alcanzo altura de 10m" << endl;  
    }
}