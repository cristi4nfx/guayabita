#include "jugador.h"
#include "funciones.h"
#include "utilidades.h"
#include <iostream>
#include <limits>

/*
    VALORES PARA PRUEBAS

    int numeroJugadores = 3;
    int apuestaInicial = 100;
    vector<Jugador> Jugadores ={
        {"Cristian", 5000},
        {"Fernando", 6000},
        {"Muñoz", 5000}
    };
*/

int main(){

    srand(time(0));
    int numeroJugadores;
    int apuestaInicial;
    vector<Jugador> Jugadores;

//REGISTRO DE USUARIOS Y APUESTA INICIAL

///*
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
//*/


//INICIO DE LA GUAYABITA 

    banner(true, Jugadores);
    apuestasIniciales(Jugadores, apuestaInicial);

    //SELECCION DE TURNO

    int turnoInicial = indiceTurnoInicial(Jugadores);
    cout << endl << endl << Jugadores[turnoInicial].nombre << " empieza tirando.\n";
    pausa(4);

    //APUESTAS
    int mesa = apuestaInicial * numeroJugadores;
    string enter;
    int primerGiro;
    int segundoGiro;
    int apuesta;

    
    while (true){
        limpiarJugadores(Jugadores, apuestaInicial);
        limpiarPantalla();
        banner(true, Jugadores, mesa);

        if (Jugadores.size() < 2) {
                
            cout << "\nNo hay suficientes jugadores para seguir con la partida.\n";
            return 0;
        }

        for (size_t i = 0; i < Jugadores.size(); i++){

            size_t indiceCircular = (i + turnoInicial) % Jugadores.size() ;
            cout << endl << endl <<Jugadores[indiceCircular].nombre << " presiona ENTER para girar el dado.";
            getline(cin, enter);
            primerGiro = Jugadores[indiceCircular].tirarDado();
            cout << Jugadores[indiceCircular].nombre << " saco un " << primerGiro << " en su lanzamiento.";

            if (!(primerGiro == 1 || primerGiro == 6)){

                cout << endl <<Jugadores[indiceCircular].nombre << " que deseas apostar?:\n"
                      <<"1. Apuesta inicial (" << apuestaInicial << "$)\n"
                      <<"2. Apostar otra cantidad.\n"
                      <<"Seleccione una opcion (1-2): ";

                while (!(cin >> apuesta) || (apuesta != 1 && apuesta !=2)){

                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n!ERROR! Selecciona una opción adecuada.";
                    cout << endl <<Jugadores[indiceCircular].nombre << " que deseas apostar?:\n"
                     <<"1. Apuesta inicial (" << apuestaInicial << "$)\n"
                     <<"2. Apostar otra cantidad.\n"
                     <<"Seleccione una opción (1-2): ";
                     
                }

                if (apuesta == 1){

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    apuesta = apuestaInicial;
                    Jugadores[indiceCircular].apostar(apuestaInicial);

                }else{ //apuesta == 2

                    apuesta = leerApuesta("\nDigite la cantidad que quiera apostar (mayor o igual a la apuesta inicial(" + to_string(apuestaInicial) + "$) y menor a lo que hay en la mesa (" + to_string(mesa) + "$)), ten en cuenta tu saldo actual (" + to_string(Jugadores[indiceCircular].dinero) + "$) :",
                                        "Apuesta inválida. Por favor ingresa un valor mayor o igual a " + to_string(apuestaInicial) + "$.\n", apuestaInicial);

                    while (apuesta < 0 || apuesta > mesa || apuesta > Jugadores[indiceCircular].dinero){

                        apuesta = leerApuesta("\nDigite la cantidad que quiera apostar (mayor o igual a la apuesta inicial(" + to_string(apuestaInicial) + "$) y menor a lo que hay en la mesa (" + to_string(mesa) + "$)), ten en cuenta tu saldo actual (" + to_string(Jugadores[indiceCircular].dinero) + "$) :",
                                          "Apuesta inválida. Por favor ingresa un valor mayor o igual  a " + to_string(apuestaInicial) + "$.\n", apuestaInicial);
                    }

                    apuesta = Jugadores[indiceCircular].apostar(apuesta);
                }

                cout << endl << endl <<Jugadores[indiceCircular].nombre << " presiona ENTER para girar el dado.";
                getline(cin, enter);
                segundoGiro = Jugadores[indiceCircular].tirarDado();
                cout << Jugadores[indiceCircular].nombre << " saco un " << segundoGiro << " en su lanzamiento.\n";
                
                if (segundoGiro > primerGiro){

                    cout << "¡Ganaste la apuesta¡\n";
                    mesa -= apuesta;
                    Jugadores[indiceCircular].ganar(2 * apuesta);

                }else{

                    cout << "¡Perdiste la apuesta¡\n";
                    mesa += apuesta;

                }

                if (mesa == 0 || mesa < apuestaInicial){

                    pausa(2);
                    limpiarPantalla();
                    banner(true, Jugadores, mesa);
                    cout << "\nLa mesa no puede seguir pagando las apuestas, inicia una nueva partida!.\n";

                    return 0;
                }

            } else {

                cout << "\nTienes que dar a la mesa obligatoriamente la apuesta inicial :( \n";
                Jugadores[indiceCircular].apostar(apuestaInicial);
                mesa += apuestaInicial;

            }

        }

        pausa(4);
    }
    
    
    return 0;
}