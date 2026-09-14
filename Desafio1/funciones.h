#ifndef FUNCIONES_H
#define FUNCIONES_H

void imprimirBytes(unsigned char* tablero, int filas, int columnas);
void detectarCombinacion(unsigned char* tablero, int filas, int columnas);
void eliminarFicha(unsigned char * tablero, int fila, int columna, int columnas);
void imprimirByte(unsigned char b);
void guardarFicha(unsigned char* tablero, int fila, int columna, int columnas, int numero);

int obtenerFicha(unsigned char* tablero, int fila,int columna,int columnas);

#endif // FUNCIONES_H
