#include "funcionesjuego.h"
#include "funciones.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

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

int revisarYEliminarVecinosEspeciales(unsigned char* tablero, int filas, int columnas, int fila, int columna)
{
    int encontrados = 0;
    int df[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    for (int d = 0; d < 4; d++)
    {
        int nf = fila + df[d];
        int nc = columna + dc[d];
        if (nf >= 0 && nf < filas && nc >= 0 && nc < columnas)
        {
            if (obtenerFicha(tablero, nf, nc, columnas) == 7)
            {
                eliminarFicha(tablero, nf, nc, columnas);
                encontrados++;
            }
        }
    }
    return encontrados;
}

int generarValorAleatorio()
{
    int probabilidad = rand() % 100;
    if (probabilidad < 5) return 7;

    return (rand() % 6) + 1;
}

int calcularPuntosDeMatch(int filaInicio, int colInicio, int filaFin, int colFin)
{
    int longitud = (filaInicio == filaFin) ? (colFin - colInicio + 1): (filaFin - filaInicio + 1);
    int puntos = longitud * 10;
    if (longitud > 3) puntos += (longitud - 3) * 5;

    return puntos;
}

int eliminarCombinaciones(unsigned char* tablero, int filas, int columnas, int total,
                          int matchFilaInicio[], int matchColInicio[],
                          int matchFilaFin[], int matchColFin[], int& fichasEliminadas)
{
    int puntosGanados = 0;

    for (int k = 0; k < total; k++)
    {
        int puntosMatch = calcularPuntosDeMatch(matchFilaInicio[k], matchColInicio[k],
                                                matchFilaFin[k], matchColFin[k]);
        int especialesActivados = 0;

        if (matchFilaInicio[k] == matchFilaFin[k])
        {
            for (int c = matchColInicio[k]; c <= matchColFin[k]; c++)
            {
                especialesActivados += revisarYEliminarVecinosEspeciales(tablero, filas, columnas, matchFilaInicio[k], c);
                eliminarFicha(tablero, matchFilaInicio[k], c, columnas);
                fichasEliminadas++;
            }
        }
        else
        {
            for (int f = matchFilaInicio[k]; f <= matchFilaFin[k]; f++)
            {
                especialesActivados += revisarYEliminarVecinosEspeciales(tablero, filas, columnas, f, matchColInicio[k]);
                eliminarFicha(tablero, f, matchColInicio[k], columnas);
                fichasEliminadas++;
            }
        }
        fichasEliminadas += especialesActivados;

        if (especialesActivados > 0)
            puntosMatch *= (1 + especialesActivados);

        puntosGanados += puntosMatch;
    }

    return puntosGanados;
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

void eliminarFila(unsigned char*& tablero, int& filas, int columnas,
                  int filaEliminar, int& capacidadActual)
{
    int nuevasFilas = filas - 1;
    int necesarios = bytesNecesarios(nuevasFilas, columnas);

    unsigned char* compactado = new unsigned char[necesarios]();

    int filaDestino = 0;
    for (int f = 0; f < filas; f++)
    {
        if (f == filaEliminar) continue;
        for (int c = 0; c < columnas; c++)
        {
            int valor = obtenerFicha(tablero, f, c, columnas);
            guardarFicha(compactado, filaDestino, c, columnas, valor);
        }
        filaDestino++;
    }

    double uso = (double)necesarios / capacidadActual;

    if (uso < 0.65)
    {
        delete[] tablero;
        tablero = compactado;
        capacidadActual = necesarios;
    }
    else
    {
        for (int i = 0; i < necesarios; i++)
            tablero[i] = compactado[i];
        delete[] compactado;
    }

    filas = nuevasFilas;
}

void eliminarColumna(unsigned char*& tablero, int filas, int& columnas,
                     int columnaEliminar, int& capacidadActual)
{
    int nuevasColumnas = columnas - 1;
    int necesarios = bytesNecesarios(filas, nuevasColumnas);

    unsigned char* compactado = new unsigned char[necesarios]();

    for (int f = 0; f < filas; f++)
    {
        int columnaDestino = 0;
        for (int c = 0; c < columnas; c++)
        {
            if (c == columnaEliminar) continue;
            int valor = obtenerFicha(tablero, f, c, columnas);
            guardarFicha(compactado, f, columnaDestino, nuevasColumnas, valor);
            columnaDestino++;
        }
    }

    double uso = (double)necesarios / capacidadActual;

    if (uso < 0.65)
    {
        delete[] tablero;
        tablero = compactado;
        capacidadActual = necesarios;
    }
    else
    {
        for (int i = 0; i < necesarios; i++)
        {
            tablero[i] = compactado[i];
        }
        delete[] compactado;
    }

    columnas = nuevasColumnas;
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
                int numero =  generarValorAleatorio();
                guardarFicha(tablero, i, j, columnas, numero);
            }
        }
    }
}

void procesarCascada(unsigned char* tablero, int filas, int columnas, int& puntajeTotal,
                     int& cascadas, int& combinacionesDetectadas, int& fichasEliminadas)
{
    int vuelta = 0;
    int N = maxCombinaciones(filas, columnas);
    int* matchFilaInicio = new int[N];
    int* matchColInicio = new int[N];
    int* matchFilaFin = new int[N];
    int* matchColFin = new int[N];
    cascadas = 0;
    combinacionesDetectadas = 0;
    fichasEliminadas = 0;
    int total;
    do
    {
        gravedad(tablero, filas, columnas);
        regenerarVacios(tablero, filas, columnas);
        total = detectarCombinacion(tablero, filas, columnas,
                                    matchFilaInicio, matchColInicio,
                                    matchFilaFin, matchColFin);
    //std::cout << "\n--- Vuelta " << vuelta << ": " << total << " combinaciones ---\n";
        if (total > 0)
        {
            vuelta++;
            combinacionesDetectadas += total;
            int puntosVuelta = eliminarCombinaciones(tablero, filas, columnas, total,
                                                     matchFilaInicio, matchColInicio,
                                                     matchFilaFin, matchColFin, fichasEliminadas);
            puntajeTotal += puntosVuelta * vuelta;
            cascadas = vuelta;
        }

    } while (total > 0);

    delete[] matchFilaInicio;
    delete[] matchColInicio;
    delete[] matchFilaFin;
    delete[] matchColFin;
}
void insertarColumna(unsigned char*& tablero, int filas, int& columnas, int columnaInsertar, int& capacidadActual)
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
    capacidadActual = bytesNecesarios(filas, nuevasColumnas);
}

void insertarFila(unsigned char*& tablero, int& filas, int columnas, int filaInsertar, int& capacidadActual)
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
    capacidadActual = bytesNecesarios(nuevasFilas, columnas);
}


void imprimirTablero(unsigned char* tablero, int filas, int columnas)
{
    std::cout << "\n -----  Tablero  -----\n";

    // Encabezado con numeros de columna, ancho fijo de 2
    std::cout << "    ";
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
            int numero = generarValorAleatorio();
            guardarFicha(tablero, i, j, columnas, numero);
        }
    }
}
