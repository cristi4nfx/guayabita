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

int tirarDado(){
    return 1 + rand() % 6;
}

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

struct Jugador{
    string nombre;
    int dinero;
};

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


int main(){

    srand(time(0));
    int numeroJugadores;
    int apuestaInicial;
    vector<Jugador> Jugadores;

//REGISTRO DE USUARIOS Y APUESTA INICIAL

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

    cout << "\nIniciando juego ....\n";
    pausa(2);
    limpiarPantalla();

//INICIO DE LA GUAYABITA

    banner();
    cout << "Jugadores:\n";
    for (size_t i = 0; i < Jugadores.size(); i++){ 
        cout << "\nJugador #" << i + 1 << endl;
        cout << "Nombre: " << Jugadores[i].nombre << endl;
        cout << "Dinero: " << Jugadores[i].dinero << endl;

    }

    
    return 0;
}