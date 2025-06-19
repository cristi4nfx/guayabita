#include "funciones.h"

int main(){

    srand(time(0));
    int numeroJugadores = 3;
    int apuestaInicial = 100;
    vector<Jugador> Jugadores ={
        {"Cristian", 5000},
        {"Fernando", 6000},
        {"Muñoz", 5000}
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
        limpiarPantalla();
        banner(true, Jugadores, mesa);
        if (Jugadores.size() < 2) {
                
            cout << "\nNo hay suficientes jugadores para seguir con la partida.\n";
            return 0;
        }

        for (size_t i = 0; i < Jugadores.size(); i++){

            size_t indiceCircular = (i + turnoInicial) % Jugadores.size() ;
            cout << endl << endl <<Jugadores[indiceCircular].nombre << " presiona ENTER para girar el dado.";
            cin.clear();
            getline(cin, enter);
            primerGiro = Jugadores[indiceCircular].tirarDado();
            cout << Jugadores[indiceCircular].nombre << " saco un " << primerGiro << " en su lanzamiento.";
            
            if (Jugadores[indiceCircular].dinero < apuestaInicial){

                cout << Jugadores[indiceCircular].nombre << " no tienes suficiente dinero para dar la apuesta inicial.";
                Jugadores.erase(Jugadores.begin() + indiceCircular);
                cout << Jugadores[indiceCircular].nombre << " fue expulsado de la mesa.";
                continue;
            }


            if (!(primerGiro == 1 || primerGiro == 6)){

                cout << endl <<Jugadores[indiceCircular].nombre << " que deseas apostar?:\n"
                     <<"1. Apuesta inicial (" << apuestaInicial << "$)\n"
                     <<"2. Apostar otra cantidad.\n"
                     <<"Seleccione una opcion (1-2): ";
                cin >> apuesta;

                if (apuesta == 1){

                    apuesta = apuestaInicial;
                    Jugadores[indiceCircular].apostar(apuestaInicial);

                }else{
                    apuesta = leerApuesta("Digite la cantidad que quiera apostar (mayor o igual a la apuesta inicial y menor a lo que hay en la mesa), ten en cuenta tu saldo actual: ",
                                        "Apuesta inválida. Por favor ingresa un valor mayor a " + to_string(apuestaInicial) + "$.\n", apuestaInicial);

                    apuesta = Jugadores[indiceCircular].apostar(apuesta);

                    if (apuesta == 0){

                        apuesta = leerApuesta("Digite la cantidad que quiera apostar (mayor o igual a la apuesta inicial y menor a lo que hay en la mesa), ten en cuenta tu saldo actual: ",
                                          "Apuesta inválida. Por favor ingresa un valor mayor a " + to_string(apuestaInicial) + "$.\n", apuestaInicial);
                    }
                }

                cout << endl << endl <<Jugadores[indiceCircular].nombre << " presiona ENTER para girar el dado.";
                cin.clear();
                cin.ignore();
                getline(cin, enter);
                segundoGiro = Jugadores[indiceCircular].tirarDado();
                cout << Jugadores[indiceCircular].nombre << " saco un " << segundoGiro << " en su lanzamiento.\n";
                
                if (segundoGiro > primerGiro){
                    cout << "¡Ganaste la apuesta¡\n";
                    mesa -= apuesta;
                    Jugadores[indiceCircular].ganar(apuesta * 2);
                    continue;
                }else{
                    cout << "¡Perdiste la apuesta¡\n";
                    mesa += apuesta;
                    continue;
                }
            }

            cout << "\nTienes que dar a la mesa obligatoriamente la apuesta inicial :( \n";
            Jugadores[indiceCircular].apostar(apuestaInicial);
            mesa += apuestaInicial;

        }

        limpiarJugadores(Jugadores, apuestaInicial);
        pausa(4);
    }
    
    
    return 0;
}