#include "funciones.h"
#include "utilidades.h"
#include <iostream>
#include <limits>

int leerApuesta(string mensaje, string error, int apuestaInicial){
    int valor;

    while (true) {
        cout << mensaje;
        cin >> valor;

        if (cin.fail() || valor < apuestaInicial)  {

            cin.clear();                 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');     
            cout << error;

        } else {                 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');     
            return valor;
        }
    }
}

vector<Jugador> infoJugadores(int numJugadores, int apuestaInicial){
    vector<Jugador> Jugadores;


    for (int i=1; i <= numJugadores; i++){
        Jugador j;
        
        cout << "\nNombre del jugador #"<< i << ": ";
        getline(cin, j.nombre);

        j.dinero = leerApuesta("Dinero del jugador #" + to_string(i) + " (Minimo: " + to_string(2 * apuestaInicial) + " $): ");

        if (j.dinero < (2 * apuestaInicial)){

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
            i--;
            pausa(4);
        }
    }

}



void banner(bool jugadores, vector<Jugador> Jugadores, int mesa){
    cout << "*********************************\n";
    cout << "*        LA GUAYABITA           *\n";
    cout << "*   ---------------------       *\n";
    cout << "*  ¡Apuesta   y  diviértete!    *\n";
    cout << "*********************************\n\n";

    if (jugadores){
        cout << "Dinero en la mesa: " << mesa << "$" << endl;
        for (size_t i = 0; i < Jugadores.size(); i++){ 

            cout << "#" << i + 1  << " " << Jugadores[i].nombre << "  -  Saldo Actual: " << Jugadores[i].dinero  << "$"<< endl;

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
