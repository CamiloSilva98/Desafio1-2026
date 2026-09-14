#include <iostream>
#include "Funciones.h"
#include <cstdlib>
#include <ctime>

using namespace std;
//taskkill /f /im desafio_1_sweet_crush.exe

int main(){
    srand(time(NULL));

    int filas, columnas ;
    cout<<"        ************SWEET - CRUSH************\n";
    cout<<"**Para crear tablero ingrese filas y columnas**\n";
    cout<<"Ingrese Filas: ";
    cin>>filas;
    cout<<"Ingrese Columnas: ";
    cin>>columnas;
    int matriz[filas][columnas];

    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            matriz[i][j] = (rand() % 6) + 1;
            //matriz[i][j] = 1;
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
    //esto genera una matriz de numeros uniformes,  ahora vamos a convertir estos numeros a binarios y guardarlos en una matriz de binarios
    //calcular bits
    int bits_necesarios = filas * columnas * 3;

    //calcular bytes
    int bytes_necesarios = ((bits_necesarios+7)/8);

    //creamos la reserva del tablero
    unsigned char* tablero = new unsigned char[bytes_necesarios]();

    //llenar la reserva con cada numero en bits
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            // Imprimir visualmente matriz bits antes de empaquetar
            int numero = matriz[i][j];
            for (int b = 2; b >= 0; b--) {
                cout << ((numero >> b) & 1);
            }
            cout << " ";

            guardarFicha(tablero, i, j, columnas, matriz[i][j]);
        }
        cout << endl;
    }
    // Primer diagnóstico
    imprimirBytes(tablero, filas, columnas);

    // Eliminar la ficha en (3,3) usando la nueva función modular
    //eliminarFicha(tablero, 3, 3, columnas);

    // Segundo diagnóstico (para ver el bit en 000)
    imprimirBytes(tablero, filas, columnas);

    // Buscar combinaciones
    //detectarCombinacion(tablero,  filas, columnas);

    // Liberación de memoria ram limpia
    delete[] tablero;

    return 0;
}