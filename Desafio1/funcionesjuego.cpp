#include "funcionesjuego.h"
#include "funciones.h"
#include <iostream>
#include <iomanip>

char convertirASimbolo(int valor)
{
    switch (valor)
    {
    case 0: return ' ';   // vacio
    case 1: return '#';
    case 2: return '@';
    case 3: return '%';
    case 4: return '&';
    case 5: return '$';
    case 6: return 190;   //
    case 7: return '*';   // estado especial
    default: return '?';
    }
}

int maxCombinaciones(int filas, int columnas)
{
    return filas * (columnas / 3) + columnas * (filas / 3);
}

int detectarCombinacion(unsigned char* tablero, int filas, int columnas,
                        int matchFilaInicio[], int matchColInicio[],
                        int matchFilaFin[], int matchColFin[])
{
    int total = 0;

    // Horizontal: recorrer cada fila buscando rachas
    for (int i = 0; i < filas; i++)
    {
        int inicio = 0;
        int j = 0;
        while (j < columnas)
        {
            int valorInicio = obtenerFicha(tablero, i, inicio, columnas);
            int valorActual = obtenerFicha(tablero, i, j, columnas);

            if (valorActual == valorInicio && valorInicio != 0)
            {
                j++;
            }
            else
            {
                if ((j - inicio) >= 3)
                {
                    matchFilaInicio[total] = i;
                    matchColInicio[total] = inicio;
                    matchFilaFin[total] = i;
                    matchColFin[total] = j - 1;
                    total++;
                }
                inicio = j;
                j++;
            }
        }
        if ((columnas - inicio) >= 3 &&
            obtenerFicha(tablero, i, inicio, columnas) != 0)
        {
            matchFilaInicio[total] = i;
            matchColInicio[total] = inicio;
            matchFilaFin[total] = i;
            matchColFin[total] = columnas - 1;
            total++;
        }
    }

    // Vertical: misma logica, recorriendo columnas
    for (int j = 0; j < columnas; j++)
    {
        int inicio = 0;
        int i = 0;
        while (i < filas)
        {
            int valorInicio = obtenerFicha(tablero, inicio, j, columnas);
            int valorActual = obtenerFicha(tablero, i, j, columnas);

            if (valorActual == valorInicio && valorInicio != 0)
            {
                i++;
            }
            else
            {
                if ((i - inicio) >= 3)
                {
                    matchFilaInicio[total] = inicio;
                    matchColInicio[total] = j;
                    matchFilaFin[total] = i - 1;
                    matchColFin[total] = j;
                    total++;
                }
                inicio = i;
                i++;
            }
        }
        if ((filas - inicio) >= 3 &&
            obtenerFicha(tablero, inicio, j, columnas) != 0)
        {
            matchFilaInicio[total] = inicio;
            matchColInicio[total] = j;
            matchFilaFin[total] = filas - 1;
            matchColFin[total] = j;
            total++;
        }
    }

    return total;
}

void eliminarCombinaciones(unsigned char* tablero, int columnas, int total,
                           int matchFilaInicio[], int matchColInicio[],
                           int matchFilaFin[], int matchColFin[])
{
    for (int k = 0; k < total; k++)
    {
        if (matchFilaInicio[k] == matchFilaFin[k])
        {
            // horizontal
            for (int c = matchColInicio[k]; c <= matchColFin[k]; c++)
                eliminarFicha(tablero, matchFilaInicio[k], c, columnas);
        }
        else
        {
            // vertical
            for (int f = matchFilaInicio[k]; f <= matchFilaFin[k]; f++)
                eliminarFicha(tablero, f, matchColInicio[k], columnas);
        }
    }
}

void gravedad(unsigned char* tablero, int filas, int columnas)
{
    for (int j = 0; j < columnas; j++)
    {
        int filaDestino = filas - 1;

        for (int i = filas - 1; i >= 0; i--)
        {
            int valor = obtenerFicha(tablero, i, j, columnas);

            if (valor != 0)
            {
                if (i != filaDestino)
                {
                    guardarFicha(tablero, filaDestino, j, columnas, valor);
                    eliminarFicha(tablero, i, j, columnas);
                }
                filaDestino--;
            }
        }
    }
}

void regenerarVacios(unsigned char* tablero, int filas, int columnas)
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            if (obtenerFicha(tablero, i, j, columnas) == 0)
            {
                int numero = (rand() % 6) + 1;
                guardarFicha(tablero, i, j, columnas, numero);
            }
        }
    }
}

void procesarCascada(unsigned char* tablero, int filas, int columnas)
{
    int vuelta = 1;
    int N = maxCombinaciones(filas, columnas);
    int* matchFilaInicio = new int[N];
    int* matchColInicio = new int[N];
    int* matchFilaFin = new int[N];
    int* matchColFin = new int[N];

    int total;
    do
    {
        total = detectarCombinacion(tablero, filas, columnas,
                                    matchFilaInicio, matchColInicio,
                                    matchFilaFin, matchColFin);
    std::cout << "\n--- Vuelta " << vuelta << ": " << total << " combinaciones ---\n";
        if (total > 0)
        {
            eliminarCombinaciones(tablero, columnas, total,
                                  matchFilaInicio, matchColInicio,
                                  matchFilaFin, matchColFin);
            gravedad(tablero, filas, columnas);
            regenerarVacios(tablero, filas, columnas);
        }
        vuelta++;
    } while (total > 0);

    delete[] matchFilaInicio;
    delete[] matchColInicio;
    delete[] matchFilaFin;
    delete[] matchColFin;
}
void insertarColumna(unsigned char*& tablero, int filas, int& columnas, int columnaInsertar)
{
    int nuevasColumnas = columnas + 1;
    unsigned char* nuevoTablero = new unsigned char[bytesNecesarios(filas, nuevasColumnas)]();

    for (int f = 0; f < filas; f++)
    {
        int columnaOrigen = 0;
        for (int c = 0; c < nuevasColumnas; c++)
        {
            if (c == columnaInsertar) continue; // hueco, se llena despues
            int valor = obtenerFicha(tablero, f, columnaOrigen, columnas);
            guardarFicha(nuevoTablero, f, c, nuevasColumnas, valor);
            columnaOrigen++;
        }
    }

    delete[] tablero;
    tablero = nuevoTablero;
    columnas = nuevasColumnas;

    llenarAleatorio(nuevoTablero, nuevasColumnas, 0, filas, columnaInsertar, columnaInsertar + 1);
}

void insertarFila(unsigned char*& tablero, int& filas, int columnas, int filaInsertar)
{
    int nuevasFilas = filas + 1;
    unsigned char* nuevoTablero = new unsigned char[bytesNecesarios(nuevasFilas, columnas)]();

    int filaOrigen = 0;
    for (int f = 0; f < nuevasFilas; f++)
    {
        if (f == filaInsertar) continue; // hueco, se llena despues
        for (int c = 0; c < columnas; c++)
        {
            int valor = obtenerFicha(tablero, filaOrigen, c, columnas);
            guardarFicha(nuevoTablero, f, c, columnas, valor);
        }
        filaOrigen++;
    }

    delete[] tablero;
    tablero = nuevoTablero;
    filas = nuevasFilas;

    llenarAleatorio(tablero, columnas, filaInsertar, filaInsertar + 1, 0, columnas);
}


void imprimirTablero(unsigned char* tablero, int filas, int columnas)
{
    std::cout << "\n -----  Tablero  -----\n";

    // Encabezado con numeros de columna, ancho fijo de 2
    std::cout << "     ";
    for (int c = 1; c <= columnas; c++)
    {
        std::cout << std::setw(2) << c << " ";
    }
    std::cout << "\n";

    for (int f = 1; f <= filas; f++)
    {
        std::cout << std::setw(2) << f << ": ";
        for (int c = 1; c <= columnas; c++)
        {
            int valor = obtenerFicha(tablero, f-1, c-1, columnas);
            std::cout << std::setw(2) << convertirASimbolo(valor) << " ";
        }
        std::cout << "\n";
    }
}
void llenarAleatorio(unsigned char* tablero, int columnas,
                     int filaInicio, int filaFin,
                     int columnaInicio, int columnaFin)//llena de manera aleatoria con numeros del 1 al 6 y recibe limites a llenar
                                                        // podemos llenar toda el arreglo o una fila o columna de ser necesario
{
    for (int i = filaInicio; i < filaFin; i++)
    {
        for (int j = columnaInicio; j < columnaFin; j++)
        {
            int numero = (rand() % 7) + 1;
            guardarFicha(tablero, i, j, columnas, numero);
        }
    }
}
