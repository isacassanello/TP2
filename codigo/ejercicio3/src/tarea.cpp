#include <iostream>
#include <queue>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>
#include <string> 
#include <vector>
using namespace std; 

struct Tarea{
    private: 
        int idSensor; 
        int idTarea;
        string descripcionTarea;

    public: 
        Tarea() = default;
        Tarea(int idSensor, int idTarea, const string& descripcionTarea) : idSensor(idSensor), idTarea(idTarea) , descripcionTarea(descripcionTarea) {}

        //void imprimir() const {cout << descripcionTarea << endl;}
        int getIdSensor() const {return idSensor;}
        int getIdTarea() const {return idTarea;}
        string getDescripcion() const {return descripcionTarea;}
};

queue<Tarea> tareasCompartidas;
mutex mutexCola; //protege el acceso a la cola (para que dos threads no accedan a la cola al mismo tiempo)
mutex mutexCout; //para que los threads no escriban al mismo tiempo y no se mezclen los msj
atomic<int> sensoresActivos =0; //indica cuantos sensores estan activos - (atomic hace que no pueda ser interrumpida por otros threads)
int idTareasTotales = 0; //contador de cuantas tareas fueron creadas 



void crearTarea(int idSensor){
    this_thread::sleep_for(chrono::milliseconds(175)); //espera 175ms para generar la tarea 

    Tarea tarea;
    //scope nuevo
    {  
        lock_guard<mutex> lock(mutexCola);  //avisa al resto de sensores (threads) que solo esta trabajando el (el restp para)
        int idTarea = idTareasTotales++;  //cambia el id de la tarea  
        string descripcion = "El id de esta tarea es " + to_string(idTarea) ; //en la descripcion de la tarea tiene que estar su id actual
        tarea = Tarea(idSensor,idTarea,descripcion);
        tareasCompartidas.push(tarea);
    }
    {
        lock_guard<mutex> lock(mutexCout); 
        cout << "El sensor " << idSensor << " ,genero la tarea " << tarea.getIdTarea() << ": "<< tarea.getDescripcion();
    }
}

void sensor(int idSensor, int cantidadTareas){ //cada sensor crea n tareas llamando a creartarea()
    for (int i = 0; i < cantidadTareas; i++){
        crearTarea(idSensor);
    }
    --sensoresActivos;
}

void robot(int idRobot){
    while (true) //robot funcionar hasta que ya no queden tareas por hacer 
    Tarea tarea;
    bool tareaObtenida = false; //saber si se logro sacar una tarea de la cola 

    {
        lock_guard<mutex> lock(mutexCola);
        if(!tareasCompartidas.empty()){
            tarea = tareasCompartidas.front();  //NOO SE PORQUEEEE (XQ ESTA AFUERA DEL SCOPE??)
            tareasCompartidas.pop(); //saca la tarea si ya la use
            tareaObtenida = true;
        } else if (sensoresActivos == 0){ //COMO MANEJO CUANDO HAY SENSORES ACTIVOS PERO ESTA TEMPRALMENTE VACIA 
            break;
        }
    }

    if (tareaObtenida){
        this_thread::sleep_for(chrono::milliseconds(250)); //El procesamiento de cada tarea por parte de un robot debe tomar 250 ms.
        {
            lock_guard<mutex> lock(mutexCout);
            cout << "El robot con id " << idRobot << " esta procesando la tarea " << tarea.getIdTarea() << " del sensor " << tarea.getIdSensor() << " : " << tarea.getDescripcion() << endl;
        }
    }
    {
        lock_guard<mutex> lock(mutexCout);
        cout << "El Robot " << idRobot << "Finalizo su trabajo" << endl;
    }
    
}


//========================= MAIN ======================= 
int main(){ 
    
}


