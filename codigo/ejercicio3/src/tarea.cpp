#include <iostream>
#include <queue>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>
#include <string> 
#include <vector>
#include <condition_variable>
using namespace std; 

//Estructura que respresenta una tarea generada por un sensor
struct Tarea{
    private: 
        int idSensor; 
        int idTarea;
        string descripcionTarea;

    public: 
        Tarea() = default;
        Tarea(int idSensor, int idTarea, const string& descripcionTarea) : idSensor(idSensor), idTarea(idTarea) , descripcionTarea(descripcionTarea) {}

        int getIdSensor() const {return idSensor;}
        int getIdTarea() const {return idTarea;}
        string getDescripcion() const {return descripcionTarea;}
};

queue<Tarea> tareasCompartidas;
mutex mutexCola; // protege el acceso a la cola
mutex mutexCout; // mutex para evitar superposicion de mensajes por consola
condition_variable cvTareas; // variable de condicion par notificar a los robots cuando hay nuevas tareas

atomic<int> sensoresActivos = 0; // contador que indica la cantidad de sensores activos
atomic<int> idTareasTotales = 0; // contador de tareas generadas

//funcion que crea una tarea y la agrega a la cola compartida 
void crearTarea(int idSensor){
    this_thread::sleep_for(chrono::milliseconds(175)); //espera 175ms para generar la tarea 

    Tarea tarea;
    {  
        lock_guard<mutex> lock(mutexCola);  //bloqueo el acceso a la cola para que evitar un race condition
        int idTarea = idTareasTotales++;  // asigna una id unico a la tarea
        string descripcion = "Tarea " + to_string(idTarea); 
        tarea = Tarea(idSensor, idTarea, descripcion);
        tareasCompartidas.push(tarea);
    }
    {
        lock_guard<mutex> lock(mutexCout); //bloqueo para que no se superpongan los cout
        cout << "El sensor " << idSensor << ", genero: " << tarea.getDescripcion() << endl;
    }

    cvTareas.notify_all(); // notifica a los robots que hay una nueva tarea
}


//cada sensor crea una cantidad fija de tareas 
void sensor(int idSensor, int cantidadTareas){ 
    for (int i = 0; i < cantidadTareas; i++){
        crearTarea(idSensor);
    }
    --sensoresActivos; //informa que este sensor termino
    cvTareas.notify_all(); // notifica por si hay robots esperando
}

//funcion ejecutada por cada robot para procesar tareas de la cola
void robot(int idRobot){
    while (true){  
        Tarea tarea;
        {
            //uso variable condicional  para controlar cuando terminan de trabajar todas las tareas
            unique_lock<mutex> lock(mutexCola); 
            //espera mientras no haya tareas, salvo que no haya sensores activos
            cvTareas.wait(lock, [] {return !tareasCompartidas.empty() || sensoresActivos == 0;}); 

            if (tareasCompartidas.empty()){
                if (sensoresActivos == 0) break; //si no hay tareas ni sensores activos, termina
                else continue;
            }

            tarea = tareasCompartidas.front();  
            tareasCompartidas.pop(); 
        }

        {
            lock_guard<mutex> lock(mutexCout);
            cout << "El robot con id " << idRobot << " esta procesando: " << tarea.getDescripcion() << " creada por el sensor " << tarea.getIdSensor() << endl;
        }

        this_thread::sleep_for(chrono::milliseconds(250)); // simula el tiempo de procesamiento
    }

    {
        lock_guard<mutex> lock(mutexCout);
        cout << "El Robot " << idRobot << " Finalizo su trabajo" << endl;
    }
    
}

int main(){ 
    cout << "\n------------------------------------------------------------------" << endl;
    const int numSensores = 3;
    const int numRobots = 3; 
    const int tareasSensor = 9; 

    sensoresActivos = numSensores; 
    vector<thread> hilosSensores, hilosRobots;  

    //guardo todos los threads en los vectores de arriba para despues poder usar el join
    for (int i = 1; i <= numSensores; i++){
        hilosSensores.push_back(thread(sensor, i, tareasSensor));
    }

    for (int i = 1; i <= numRobots; i++){
        hilosRobots.push_back(thread(robot, i)); 
    }

    //espera a que todos los sensores terminen
    for (auto& t : hilosSensores) t.join(); 
    //espera a que todos los robots terminen
    for (auto& t : hilosRobots) t.join();

    {
        lock_guard<mutex> lock(mutexCout);
        cout << "Todos los sensores y robots terminaron correctamente" << endl;
    }

    cout << "------------------------------------------------------------------\n" << endl;

    return 0;
}