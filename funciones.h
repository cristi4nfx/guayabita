#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <string>
#include "jugador.h"

int leerApuesta(string mensaje, string error = "Entrada inválida. Por favor ingresa un número entero mayor a 0.\n", int apuestaInicial = 0);
vector<Jugador> infoJugadores(int numJugadores, int apuestaInicial);
void limpiarJugadores(vector<Jugador>& Jugadores, int apuestaInicial);
void banner(bool jugadores = false, vector<Jugador> Jugadores = {}, int mesa = 0);
int indiceTurnoInicial(vector<Jugador> Jugadores);
void apuestasIniciales(vector<Jugador>& Jugadores, int apuestaInicial);

#endif