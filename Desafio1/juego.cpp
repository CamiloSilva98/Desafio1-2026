#include "juego.h"
#include "funciones.h"
#include "funcionesjuego.h"
#include<iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void refrescarPantalla(unsigned char* tablero, int filas, int columnas)
{
    imprimirTablero(tablero, filas, columnas);
    //imprimirBytes(tablero, filas, columnas);
    //imprimirTableroBits(tablero, filas, columnas);
}

void mostrarMenu()
{
    cout << "\n===== SWEET - CRUSH =====\n";
    cout << "1. Eliminar ficha\n";
    cout << "2. Insertar fila\n";
    cout << "3. Insertar columna\n";
    cout << "4. Eliminar fila\n";
    cout << "5. Eliminar columna\n";
    cout << "6. Salir\n";
    cout << "Opcion: ";
}

void juego()
{
    srand(time(NULL));
    cout<<"        ************SWEET - CRUSH************\n";
    cout<<"**Para crear tablero ingrese filas y columnas**\n";
    int filas, columnas;
    cout << "Ingrese Filas: ";
    while(!(cin >> filas))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Entrada invalida, Ingrese un numero: ";
    }
    cout << "Ingrese Columnas: ";
    while(!(cin >> columnas))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Entrada invalida, Ingrese un numero: ";
    }
    while(filas < 1 || columnas < 1)
    {
        cout << "Ingrese Filas: ";
        while(!(cin >> filas))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada invalida, Ingrese un numero: ";
        }
        cout << "Ingrese Columnas: ";
        while(!(cin >> columnas))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada invalida, Ingrese un numero: ";
        }
    }

    int capacidadActual = bytesNecesarios(filas, columnas);
    int eliminacionesUsuario = 0, fichasEliminadasTotal = 0, combinacionesTotal = 0, cascadasUltimaJugada = 0, puntajeTotal = 0, nada;

    unsigned char* tablero = new unsigned char[capacidadActual]();
    llenarAleatorio(tablero, columnas, 0, filas, 0, columnas);

    procesarCascada(tablero, filas, columnas, nada, nada, nada, nada);
    refrescarPantalla(tablero, filas, columnas);

    int opcion;
    do
    {
        mostrarMenu();
        while(!(cin >> opcion))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada invalida, Ingrese un numero: ";
        }

        switch (opcion)
        {
        case 1:
        {
            int f, c;
            cout << "Fila (1 a " << filas << "): ";
            while(!(cin >> f))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Entrada invalida, Ingrese un numero: ";
            }
            cout << "Columna (1 a " << columnas << "): ";
            while(!(cin >> c))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Entrada invalida, Ingrese un numero: ";
            }
            if (f < 1 || f > filas || c < 1 || c > columnas)
            {
                cout << "Posicion invalida.\n";
            }
            else
            {
                eliminarFicha(tablero, f - 1, c - 1, columnas);
                eliminacionesUsuario++;
                fichasEliminadasTotal++;
            }
            break;
        }
        case 2:
        {
            int f;
            cout << "Insertar en fila (1 a " << filas + 1 << "): ";
            while(!(cin >> f))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Entrada invalida, Ingrese un numero: ";
            }
            if (f < 1 || f > filas + 1)
            {
                cout << "Posicion invalida.\n";
            }
            else
            {
                insertarFila(tablero, filas, columnas, f - 1, capacidadActual);
            }
            break;
        }
        case 3:
        {
            int c;
            cout << "Insertar en columna (1 a " << columnas + 1 << "): ";
            while(!(cin >> c))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Entrada invalida, Ingrese un numero: ";
            }
            if (c < 1 || c > columnas + 1)
            {
                cout << "Posicion invalida.\n";
            }
            else
            {
                insertarColumna(tablero, filas, columnas, c - 1, capacidadActual);
            }
            break;
        }
        case 4:
        {
            if(filas<=1)
            {
                cout << "No se puede eliminar: quedaria un tablero sin filas.\n";
            }
            else
            {
                int f;
                cout << "Eliminar fila (1 a " << filas << "): ";
                while(!(cin >> f))
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Entrada invalida, Ingrese un numero: ";
                }
                if(f > filas || f <= 0)
                {
                    cout<<"Fila invalido.\n";
                }
                else
                {
                    eliminarFila(tablero, filas, columnas, f - 1, capacidadActual);
                }
            }
            break;
        }
        case 5:
        {
            if(columnas <= 1)
            {
                cout << "No se puede eliminar: quedaria un tablero sin columnas.\n";
            }
            else
            {
                int c;
                cout << "Eliminar columna (1 a " << columnas << "): ";
                while(!(cin >> c))
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Entrada invalida, Ingrese un numero: ";
                }
                if(c > columnas ||  c <= 0)
                {
                    cout << "Columna invalida.\n";
                }
                else
                {
                    eliminarColumna(tablero, filas, columnas, c - 1, capacidadActual);
                }
            }

            break;
        }
        case 6:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion invalida\n";
            break;
        }

        if (opcion >= 1 && opcion <= 5)
        {
            int cascadasJugada, combosJugada, fichasJugada;
            procesarCascada(tablero, filas, columnas, puntajeTotal,
                            cascadasJugada, combosJugada, fichasJugada);

            cascadasUltimaJugada = cascadasJugada;
            combinacionesTotal += combosJugada;
            fichasEliminadasTotal += fichasJugada;

            refrescarPantalla(tablero, filas, columnas);

            cout << "\n--- Estado del juego ---\n";
            cout << "Dimensiones: " << filas << " x " << columnas << "\n";
            cout << "Eliminaciones del usuario: " << eliminacionesUsuario << "\n";
            cout << "Fichas eliminadas (total): " << fichasEliminadasTotal << "\n";
            cout << "Combinaciones detectadas (total): " << combinacionesTotal << "\n";
            cout << "Cascadas en esta jugada: " << cascadasUltimaJugada << "\n";
            cout << "Puntaje: " << puntajeTotal << "\n";
        }

    } while (opcion != 6);

    delete[] tablero;
}
