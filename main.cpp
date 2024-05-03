#include <stdint.h>
#include <stdio.h>

/**
 * @brief Muestra contenido binario.
 * 
 * Esta funcion recibe una variable entera y muestra en consola
 * el contenido binario, separando los nibbles con espacios.
 * 
 * @param val entero sin signo de 8 bits (uint8_t)
 * 
 * @returns nada (imprime en consola)
 */
void showBin(uint8_t val)
{
    uint8_t aux;
    uint8_t mask = 0x80;    //1000 0000

    for( int i=0 ; i<8 ; i++ )
    {
        aux = val & mask;
        if( aux != 0 )
            printf("1");
        else
            printf("0");
        if( i == 3 )
            printf(" ");
        mask = mask >> 1;
    }
    printf("\n");
}

/**
 * @brief Main para probar operaciones binarias.
 * 
 * Se prueba la funcion showBin().
 * 
*/
int main()
{
    uint8_t val = 0x3A;
    showBin(val);   // consola -> 00000011
    return 0;
}