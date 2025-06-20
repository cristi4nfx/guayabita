#include "jugador.h"
#include "utilidades.h"  // para pausa()
#include <iostream>
#include <cstdlib> // rand

int Jugador::tirarDado() {
    cout << "....Lanzando el dado....\n";
    pausa(1);
    return 1 + rand() % 6;
}

int Jugador::apostar(int cantidad) {
    if (cantidad <= this->dinero) {
        this->dinero -= cantidad;
        return cantidad;
    }

    cout << this->nombre << " no tiene suficiente dinero para apostar esa cantidad.\n";
    return 0;
}

void Jugador::apuestaInicial(int cantidad) {
    this->dinero -= cantidad;
}

void Jugador::ganar(int cantidad) {
    this->dinero += cantidad;
}
