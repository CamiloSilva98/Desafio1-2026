#include "funciones.h"
#include <iostream>

int bytesNecesarios(int filas, int columnas)
{
    int bits = filas * columnas * 3;
    return (bits + 7) / 8;
}

void imprimirBytes(unsigned char* tablero, int filas, int columnas)
{
    int bytes_necesarios = bytesNecesarios(filas, columnas);

    std::cout << "\n--- Estado de los bytes ---\n";
    for (int k = 0; k < bytes_necesarios; k++)
    {
        std::cout << "Byte " << k << ": ";
        imprimirByte(tablero[k]);
        std::cout << '\n';
    }
}



void eliminarFicha(unsigned char * tablero, int fila, int columna, int columnas)
{
    int indice = fila * columnas + columna;
    int bit_inicial = indice * 3;
    int byte_index = bit_inicial / 8;
    int bit_offset = bit_inicial % 8;
    int espacio = 8 - bit_offset;

    //una vez obtenido el bit lo colocamos en 000
    if(espacio>=3){
        tablero[byte_index] &= ~(0b111 << bit_offset);
    }else{
        // Si no caben los 3 bits en el byte actual
        int bits_bajos = espacio;
        int bits_altos = 3 - espacio;

        // Guardar parte baja (en el byte actual)
        unsigned char mascara_baja = (1 << bits_bajos) - 1;
        tablero[byte_index] &= ~(mascara_baja << bit_offset);          // Limpia solo los bits que usaremos

        // Guardar parte alta (en el siguiente byte)
        unsigned char mascara_alta = (1 << bits_altos) - 1;
        tablero[byte_index+1] &= ~mascara_alta;                        // Limpia los primeros bits del siguiente byte
    }
}
void imprimirByte(unsigned char b)
{
    for (int i = 7; i >= 0; i--)
    {
        std::cout << ((b >> i) & 1);
    }
}

void guardarFicha(unsigned char* tablero, int fila, int columna, int columnas, int numero)
{
    unsigned char aux = (numero & 0b0111);
    int indice = fila * columnas + columna;
    int bit_inicial = indice * 3;
    int byte_index = bit_inicial / 8;
    int bit_offset = bit_inicial % 8;
    int espacio = 8 - bit_offset;

    if (espacio >= 3) { //si hay 3 bytes libres
        tablero[byte_index] &= ~(0b111 << bit_offset); //limpiamos bits y los colocamos en 0 creando una mascara y desplanzandola hasta la posicion que queremos
        tablero[byte_index] |= (aux & 0b111) << bit_offset; //insertamos valor en la posicion ofset  con el operador or
    }
    else { // Si no caben los 3 bits en el byte actual
        int bits_bajos = espacio;
        int bits_altos = 3 - espacio;

        // Guardar parte baja (en el byte actual)
        unsigned char mascara_baja = (1 << bits_bajos) - 1;
        tablero[byte_index] &= ~(mascara_baja << bit_offset);          // Limpia solo los bits que usaremos
        tablero[byte_index] |= (aux & mascara_baja) << bit_offset;     // Inserta los bits bajos

        // Guardar parte alta (en el siguiente byte)
        unsigned char mascara_alta = (1 << bits_altos) - 1;
        tablero[byte_index+1] &= ~mascara_alta;                        // Limpia los primeros bits del siguiente byte
        tablero[byte_index+1] |= (aux >> bits_bajos) & mascara_alta;   // Inserta los bits altos restantes
    }
}

int obtenerFicha(unsigned char* tablero, int fila,int columna,int columnas)
{
    int indice = fila * columnas + columna;
    int bit_inicial = indice * 3;
    int byte_index = bit_inicial / 8;
    int bit_offset = bit_inicial % 8;
    int valor;
    int espacio = 8 - bit_offset; //calculamos el espacio qoe ocupa pra saber si esta en 1 solo byte
    int ficha;
    if(espacio>=3){
        //construimos la mascara
        ficha = ((tablero[byte_index]>> bit_offset) & 0b111);
    }else{
        int bits_en_parte_baja = espacio;
        int bits_en_parte_alta = 3 - espacio; //caclulamos espacio que hay en bit n y en el bit n+1
        // Creamos las máscaras basadas en la cantidad de bits que queremos de cada lado
        unsigned char mascara_baja = (1 << bits_en_parte_baja) - 1; // Si es 2, genera 011. Si es 1, genera 001.
        unsigned char mascara_alta = (1 << bits_en_parte_alta) - 1; // Si es 1, genera 001. Si es 2, genera 011.
        //  Extraemos la parte baja: movemos al inicio y aplicamos su máscara
        int parte_baja = (tablero[byte_index] >> bit_offset) & mascara_baja;

        // Extraemos la parte alta: el inicio del siguiente byte tiene lo que nos falta
        int parte_alta = tablero[byte_index + 1] & mascara_alta;

        // Reconstruimos la ficha: la parte alta se mueve a la izquierda para dejarle espacio a la baja
        ficha = parte_baja | (parte_alta << bits_en_parte_baja);
    }
    return ficha;
}
