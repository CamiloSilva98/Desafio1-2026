#ifndef FUNCIONESJUEGO_H
#define FUNCIONESJUEGO_H

char convertirASimbolo(int valor);

int maxCombinaciones(int filas, int columnas);
int detectarCombinacion(unsigned char* tablero, int filas, int columnas);

void eliminarFila(unsigned char*& tablero, int& filas, int columnas,
                 int filaEliminar, int& capacidadActual);
void eliminarColumna(unsigned char*& tablero, int filas, int& columnas,
                     int columnaEliminar, int& capacidadActual);
void gravedad(unsigned char* tablero, int filas, int columnas);
void regenerarVacios(unsigned char* tablero, int filas, int columnas);
void procesarCascada(unsigned char* tablero, int filas, int columnas);
void insertarColumna(unsigned char*& tablero, int filas, int& columnas, int columnaInsertar, int &capacidadActual);
void insertarFila(unsigned char*& tablero, int& filas, int columnas, int filaInsertar, int &capacidadActual);
void imprimirTablero(unsigned char* tablero, int filas, int columnas);
void llenarAleatorio(unsigned char* tablero, int columnas,int filaInicio, int filaFin,
                     int columnaInicio, int columnaFin);

#endif // FUNCIONESJUEGO_H
