#include "funcionesjuego.h"
#include "funciones.h"
#include <iostream>
#include <iomanip>

int bytesNecesarios(int filas, int columnas)
{
    int bits = filas * columnas * 3;
    return (bits + 7) / 8;
}

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
    case 6: return 190;   // ¥
    case 7: return '*';   // estado especial
    default: return '?';
    }
}

void detectarCombinacion(unsigned char* tablero, int filas, int columnas)
{
    //para busacr combinaciones recorremos cad fila y columna comparando con las que tiene a ambos lados
    bool hubo_match = false;

    std::cout << "\n--- Buscando Combinaciones (Match-3) ---\n";

    // 1. COMPROBACIÓN HORIZONTAL (Fila por fila)
    for (int i = 0; i < filas; i++) {
        // Llegamos hasta COLUMNAS - 2 porque evaluamos grupos de 3 (j, j+1, j+2)
        for (int j = 0; j < columnas - 2; j++) {
            int f1 = obtenerFicha(tablero, i, j,columnas);
            int f2 = obtenerFicha(tablero, i, j + 1,columnas);
            int f3 = obtenerFicha(tablero, i, j + 2,columnas);

            // Si las tres son iguales y NO son fichas vacías (0)
            if (f1 != 0 && f1 == f2 && f1 == f3) {
                std::cout << "[Match Horizontal] Ficha " << f1 << " en la fila " << i
                          << ", columnas: (" << j << ", " << j+1 << ", " << j+2 << ")\n";
                hubo_match = true;
            }
        }
    }

    // 2. COMPROBACIÓN VERTICAL (Columna por columna)
    for (int j = 0; j < columnas; j++) {
        // Llegamos hasta FILAS - 2 porque evaluamos grupos de 3 (i, i+1, i+2)
        for (int i = 0; i < filas - 2; i++) {
            int f1 = obtenerFicha(tablero, i, j,columnas);
            int f2 = obtenerFicha(tablero, i + 1, j,columnas);
            int f3 = obtenerFicha(tablero, i + 2, j,columnas);

            // Si las tres son iguales y NO son fichas vacías (0)
            if (f1 != 0 && f1 == f2 && f1 == f3) {
                std::cout << "[Match Vertical] Ficha " << f1 << " en la columna " << j
                          << ", filas: (" << i << ", " << i+1 << ", " << i+2 << ")\n";
                hubo_match = true;
            }
        }
    }

    if (!hubo_match) {
        std::cout << "No se encontraron combinaciones en este turno.\n";
    }
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
            int numero = (rand() % 6) + 1;
            guardarFicha(tablero, i, j, columnas, numero);
        }
    }
}
