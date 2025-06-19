#ifndef FUNCIONES_H
#define FUNCIONES_H

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

    int apostar(int cantidad){

        if (cantidad <= this->dinero){

            this->dinero -= cantidad;
            return cantidad;
        }
         
        cout << this ->nombre << " no tiene suficiente dinero para apostar esa cantidad.\n";
        return 0;
    }

    void apuestaInicial(int cantidad){
        this->dinero -= cantidad;
    }

    void ganar(int cantidad){
        this->dinero += cantidad;
    }

};

int leerApuesta(string mensaje, string error = "Entrada inválida. Por favor ingresa un número entero mayor a 0.\n", int apuestaInicial = 0){
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;

        if (cin.fail() || valor < apuestaInicial)  {

            cin.clear();                 
            cin.ignore();      
            cout << error;

        } else {
            return valor;
        }
    }
}

vector<Jugador> infoJugadores(int numJugadores, int apuestaIn){
    vector<Jugador> Jugadores;


    for (int i=1; i <= numJugadores; i++){
        Jugador j;

        cout << "\nNombre del jugador #"<< i << ": ";
        cin.clear();
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

void limpiarJugadores(vector<Jugador>& Jugadores, int apuestaInicial){

    for (size_t i = 0; i < Jugadores.size(); i++){

        if (Jugadores[i].dinero < apuestaInicial){

            cout << endl << endl << Jugadores[i].nombre << " no tiene dinero suficiente para jugar\n"; 
            cout << Jugadores[i].nombre << " salio del juego\n";
            Jugadores.erase(Jugadores.begin() + i);
        }

    }

}



void banner(bool jugadores = false, vector<Jugador> Jugadores = {}, int mesa = 0){
    cout << "*********************************\n";
    cout << "*        LA GUAYABITA           *\n";
    cout << "*   ---------------------       *\n";
    cout << "*  ¡Apuesta   y  diviértete!    *\n";
    cout << "*********************************\n\n";

    if (jugadores){
        cout << "Dinero en la mesa: " << mesa << endl;
        for (size_t i = 0; i < Jugadores.size(); i++){ 

            cout << "#" << i + 1  << " " << Jugadores[i].nombre << "  -  Saldo Actual: " << Jugadores[i].dinero << endl;

        }

    }
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
            cin.clear();
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

void apuestasIniciales(vector<Jugador>& Jugadores, int apuestaInicial){

    for(size_t i = 0; i < Jugadores.size(); i++){
        Jugadores[i].apuestaInicial(apuestaInicial);
    }

}

#endif