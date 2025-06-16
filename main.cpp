#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <unistd.h> 

//COMPATIBILIDAD LINUX/WINDOWS
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

//FUNCIONES PARA COMPATIBILIDAD LINUX/WINDOWS
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");   
    #else
        system("clear"); 
    #endif
}

void pausa(int segundos) {
    #ifdef _WIN32
        Sleep(segundos * 1000); 
    #else
        sleep(segundos);        
    #endif
}


struct Jugador{
    string nombre;
    int dinero;

    int tirarDado(){
        cout << "....Lanzando el dado....\n";
        pausa(1);
        return 1 + rand() % 6;
    }

    bool apostar(int cantidad){

        if (cantidad <= this->dinero){

            this->dinero -= cantidad;
            return true;
        }
         
        cout << this ->nombre << " no tiene suficiente dinero.\n";
        return false;
    }

    void ganar(int cantidad){
        this->dinero += cantidad;
    }

};

int leerApuesta(string mensaje, string error = "Entrada inválida. Por favor ingresa un número entero mayor a 0.\n") {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;

        if (cin.fail() || valor < 0)  {
            cin.clear();                 
            cin.ignore(1000, '\n');      
            cout << error;
        } else {
            cin.ignore(1000, '\n');  
            return valor;
        }
    }
}

vector<Jugador> infoJugadores(int numJugadores, int apuestaIn){
    vector<Jugador> Jugadores;


    for (int i=1; i <= numJugadores; i++){
        Jugador j;

        cout << "\nNombre del jugador #"<< i << ": ";
        getline(cin, j.nombre);

        j.dinero = leerApuesta("Dinero del jugador #" + to_string(i) + ": ");

        if (j.dinero < apuestaIn){

            cout <<j.nombre << " no tiene dinero suficiente para jugar\n";
            cout << j.nombre << " fue expulsado/a de la mesa\n";
            numJugadores--;
            i--;
        }else {

            Jugadores.push_back(j);
        }
    };

    return Jugadores;
}




void banner(){
    cout << "*********************************\n";
    cout << "*        LA GUAYABITA           *\n";
    cout << "*   ---------------------       *\n";
    cout << "*  ¡Apuesta   y  diviértete!    *\n";
    cout << "*********************************\n\n";
}


int indiceTurnoInicial(vector<Jugador> Jugadores){

    string enter;
    vector<int> indices;
    vector<int> indicesEmpatados;
    int valorMayor = 0;
    int valorDado = 0;

    for (size_t i = 0; i < Jugadores.size(); i++) {
        indices.push_back(i);
    }

    while (true){

        valorMayor = 0;

        for(int id : indices){
            cout << endl << endl <<Jugadores[id].nombre << " presiona ENTER para girar el dado.";
            getline(cin, enter);
            valorDado = Jugadores[id].tirarDado();
            cout << Jugadores[id].nombre << " saco un " << valorDado << " en su lanzamiento.";
            if (valorDado > valorMayor){
                indicesEmpatados.clear();
                indicesEmpatados.push_back(id);
                valorMayor = valorDado;
            }else if (valorDado == valorMayor){
                indicesEmpatados.push_back(id);
            }
        }

        if(indicesEmpatados.size() == 1){
            return indicesEmpatados[0];
        }else{
            cout << "\n\n\n### DESEMPATE ###";
            indices = indicesEmpatados;
        }

    }
    
}


int main(){

    srand(time(0));
    int numeroJugadores = 4;
    int apuestaInicial = 100;
    vector<Jugador> Jugadores ={
        {"Cristian", 5000},
        {"Fernando", 6000},
        {"Muñoz", 5000},
        {"Martinez", 5000}
    };

//REGISTRO DE USUARIOS Y APUESTA INICIAL
/*
    banner();
    do {
        numeroJugadores = leerApuesta("Digite el número de jugadores (2-4): ", 
                                    "Entrada inválida. Ingresa un número válido.\n");

        if (numeroJugadores < 2 || numeroJugadores > 4) {
            cout << "El número debe estar entre 2 y 4.\n";
        }
    } while (numeroJugadores < 2 || numeroJugadores > 4);

    apuestaInicial = leerApuesta("\nDigite la cantidad de la apuesta inicial: ");
    Jugadores = infoJugadores(numeroJugadores, apuestaInicial);

    if (Jugadores.size() < 2) {
        cout << "\nNo hay suficientes jugadores para iniciar la partida.\n";
        return 0;
    }

    cout << "\n....Iniciando juego....\n";
    pausa(2);
    limpiarPantalla();
*/
//INICIO DE LA GUAYABITA

    banner();
    cout << "Jugadores:\n";
    for (size_t i = 0; i < Jugadores.size(); i++){ 
        cout << "Jugador #" << i + 1 << endl;
        cout << "Nombre: " << Jugadores[i].nombre << endl;
        cout << "Dinero: " << Jugadores[i].dinero << endl;

    }

    //SELECCION DE TURNO
    int turnoInicial = indiceTurnoInicial(Jugadores);
    cout << endl << endl << Jugadores[turnoInicial].nombre << " empieza tirando.";
    //APUESTAS
    //int mesa = 0;
    return 0;
}