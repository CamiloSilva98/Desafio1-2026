#ifndef FUNCIONESJUEGO_H
#define FUNCIONESJUEGO_H

int bytesNecesarios(int filas, int columnas);

char convertirASimbolo(int valor);

void detectarCombinacion(unsigned char* tablero, int filas, int columnas);
void imprimirTablero(unsigned char* tablero, int filas, int columnas);
void llenarAleatorio(unsigned char* tablero, int columnas,int filaInicio, int filaFin,int columnaInicio, int columnaFin);
#endif // FUNCIONESJUEGO_H
