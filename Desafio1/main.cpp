#include <iostream>
#include "Funciones.h"
#include "funcionesJuego.h"
#include <cstdlib>
#include <ctime>

using namespace std;
//taskkill /f /im desafio_1_sweet_crush.exe

int main()
{
    srand(time(NULL));

    int filas, columnas ;
    cout<<"        ************SWEET - CRUSH************\n";
    cout<<"**Para crear tablero ingrese filas y columnas**\n";
    cout<<"Ingrese Filas: ";
    cin>>filas;
    cout<<"Ingrese Columnas: ";
    cin>>columnas;
    //crear tablero
    unsigned char* tablero = new unsigned char[bytesNecesarios(filas, columnas)]();
    //llenar la reserva
    llenarAleatorio(tablero, columnas, 0, filas, 0, columnas);
    //Imprimir el tablero de juego
    imprimirTablero(tablero, filas, columnas);;
    // Primer diagnóstico
    //imprimirBytes(tablero, filas, columnas);
    procesarCascada(tablero, filas, columnas);

    insertarFila(tablero, filas, columnas, 3);

    cout << "\n--- Tablero despues de insertar fila ---\n";
    imprimirTablero(tablero, filas, columnas);

    insertarColumna(tablero, filas, columnas, 4);

    cout << "\n--- Tablero despues de insertar columna ---\n";
    imprimirTablero(tablero, filas, columnas);

    procesarCascada(tablero, filas, columnas);

    imprimirTablero(tablero, filas, columnas);


    delete[] tablero;

    return 0;
}