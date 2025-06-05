#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

class Dron{
    private:
        int id;
        array<mutex, 5> zonas;

};
