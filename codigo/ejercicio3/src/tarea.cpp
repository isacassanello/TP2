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

struct Tarea{
    private: 
        int idSensor; 
        int idTarea;
        string descripcionTarea;

    public: 
        Tarea() = default;
        Tarea(int idSensor, int idTarea, const string& descripcionTarea) : idSensor(idSensor), idTarea(idTarea) , descripcionTarea(descripcionTarea) {}

        // void imprimir() const {cout << descripcionTarea << endl;}
        int getIdSensor() const {return idSensor;}
        int getIdTarea() const {return idTarea;}
        string getDescripcion() const {return descripcionTarea;}
};

queue<Tarea> tareasCompartidas;
mutex mutexCola; // protege el acceso a la cola (para que dos threads no accedan a la cola al mismo tiempo)
mutex mutexCout; // para que los threads no escriban al mismo tiempo y no se mezclen los msj
condition_variable cvTareas; // para que los robots espren si no hay tareas y todavia hay sensores activos

atomic<int> sensoresActivos = 0; // indica cuantos sensores estan activos - (atomic hace que no pueda ser interrumpida por otros threads)
atomic<int> idTareasTotales = 0; // contador de cuantas tareas fueron creadas  - el atomic para q dos sensores no lo lean y escriban al mismo tiempo

// prodcutor
void crearTarea(int idSensor){
    this_thread::sleep_for(chrono::milliseconds(175)); //espera 175ms para generar la tarea 

    Tarea tarea;
    //scope nuevo
    {  
        lock_guard<mutex> lock(mutexCola);  //avisa al resto de sensores (threads) que solo esta trabajando el (el restp para)
        int idTarea = idTareasTotales++;  //cambia el id de la tarea  
        string descripcion = "Tarea " + to_string(idTarea); //en la descripcion de la tarea tiene que estar su id actual
        tarea = Tarea(idSensor, idTarea, descripcion);
        tareasCompartidas.push(tarea);
    }
    {
        lock_guard<mutex> lock(mutexCout); 
        cout << "El sensor " << idSensor << ", genero: " << tarea.getDescripcion() << endl;
    }

    cvTareas.notify_all(); // notificar a robots que hay una nueva tarea
}

void sensor(int idSensor, int cantidadTareas){ //cada sensor crea n tareas llamando a creartarea()
    for (int i = 0; i < cantidadTareas; i++){
        crearTarea(idSensor);
    }
    --sensoresActivos;
    cvTareas.notify_all(); // avisar a los robots en caso de que esten esperando
}

// consumidor --> revisar esta funcion
void robot(int idRobot){
    while (true){ //robot funciona hasta que ya no queden tareas por hacer 
        Tarea tarea;
        {
            unique_lock<mutex> lock(mutexCola); // lo cambie porque use el condition_variable
            cvTareas.wait(lock, [] {return !tareasCompartidas.empty() || sensoresActivos == 0;}); 

            if (tareasCompartidas.empty()){
                if (sensoresActivos == 0) break;
                else continue;
            }

            tarea = tareasCompartidas.front();  
            tareasCompartidas.pop(); //saca la tarea si ya la use
        }

        {
            lock_guard<mutex> lock(mutexCout);
            cout << "El robot con id " << idRobot << " esta procesando: " << tarea.getDescripcion() << " creada por el sensor " << tarea.getIdSensor() << endl;
        }

        this_thread::sleep_for(chrono::milliseconds(250)); //El procesamiento de cada tarea por parte de un robot debe tomar 250 ms.
    }

    {
        lock_guard<mutex> lock(mutexCout);
        cout << "El Robot " << idRobot << " Finalizo su trabajo" << endl;
    }
    
}

//========================= MAIN ======================= 
int main(){ 
    cout << "\n------------------------------------------------------------------" << endl;
    // test de 3 sensores x 9 tareas c/u y 3 robots
    const int numSensores = 3;
    const int numRobots = 3; 
    const int tareasSensor = 9; 

    sensoresActivos = numSensores; 
    vector<thread> hilosSensores, hilosRobots;

    for (int i = 1; i <= numSensores; i++){
        hilosSensores.push_back(thread(sensor, i, tareasSensor));
    }

    for (int i = 1; i <= numRobots; i++){
        hilosRobots.push_back(thread(robot, i)); 
    }

    for (auto& t : hilosSensores) t.join(); 
    for (auto& t : hilosRobots) t.join();

    {
        lock_guard<mutex> lock(mutexCout);
        cout << "Todos los sensores y robots terminaron correctamente" << endl;
    }

    cout << "------------------------------------------------------------------\n" << endl;

    return 0;
}