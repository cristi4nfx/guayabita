#include "utilidades.h"
#include <cstdlib>

//COMPATIBILIDAD LINUX/WINDOWS
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif


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