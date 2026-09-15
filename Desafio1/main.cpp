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

    //calcular bits
    int bits_necesarios = filas * columnas * 3;

    //calcular bytes
    int bytes_necesarios = ((bits_necesarios+7)/8);

    //creamos la reserva del tablero
    unsigned char* tablero = new unsigned char[bytes_necesarios]();

    //llenar la reserva
    llenarAleatorio(tablero, columnas, 0, filas, 0, columnas);
    //Imprimir el tablero de juego
    imprimirTablero(tablero, filas, columnas);;
    // Primer diagnóstico
    imprimirBytes(tablero, filas, columnas);

    detectarCombinacion(tablero, filas, columnas);



    /*cout << "\n--- Bytes crudos (valor almacenado) ---\n";
    for (int k = 0; k < bytes_necesarios; k++)
    {
        cout << "Byte " << k << ": " << (int)tablero[k] << "\n";
    }*/
    //Eliminar la ficha en (2,2)
    //eliminarFicha(tablero, 2, 2, columnas);

    // Segundo diagnóstico (para ver el bit en 000)
    imprimirBytes(tablero, filas, columnas);

    // Liberación de memoria
    delete[] tablero;

    return 0;
}