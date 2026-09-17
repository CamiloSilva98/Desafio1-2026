#ifndef FUNCIONES_H
#define FUNCIONES_H

int bytesNecesarios(int filas, int columnas);
int obtenerFicha(unsigned char* tablero, int fila,int columna,int columnas);//extraer un campo de 3 bits de una posición

void imprimirEstadoMemoria(unsigned char* tablero, int filas, int columnas, int capacidadActual);
void imprimirBytes(unsigned char* tablero, int filas, int columnas);//recorrer el arreglo e imprimir todos los bytes
void eliminarFicha(unsigned char * tablero, int fila, int columna, int columnas); //poner un campo de 3 bits en 0
void imprimirByte(unsigned char b);//imprimir un byte en binario
void guardarFicha(unsigned char* tablero, int fila, int columna, int columnas, int numero);//escribir un campo de 3 bits en una posición


#endif // FUNCIONES_H
