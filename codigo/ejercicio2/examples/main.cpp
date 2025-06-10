#include "../include/dron.h"

mutex mutex_cout;

int main(){
    const int N = 5;
    vector<thread> drones;
    vector<mutex> zonas(N);

    for (int i = 0; i < N; i++){
        int zona_izq = i;
        int zona_der = (i + 1) % N;
        drones.emplace_back(Dron(i, zonas[zona_izq], zonas[zona_der]));
    }

    for (auto& t: drones) t.join();

    {
        lock_guard<mutex> lock_cout(mutex_cout);
        cout << "Todos los drones alcanzaron los 10 metros de altura" << endl;  
    }

    return 0;
}