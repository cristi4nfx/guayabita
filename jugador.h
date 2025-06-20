#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
using namespace std;

struct Jugador {
    string nombre;
    int dinero;

    int tirarDado();
    int apostar(int cantidad);
    void apuestaInicial(int cantidad);
    void ganar(int cantidad);
};

#endif
