#include "binary_operations_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void show_bin8 (uint8_t val)
{
    uint8_t aux;
    uint8_t mask = 1<<7; //Se inicializa una variable en el valor mas significativa (1000 0000)
    for(int i=0; i<8; i++)
    {
        //Se comienza comparando de izquierda a derecha y se imprime asi
        aux= val & mask; //Se compara de forma binaria val (AND: si val es 1 Y mask 1, devuelve un 1)
        if(aux != 0){
            printf("1"); //Si hay un 1 en la posicion comparada se imprime "1"
        } else{
            printf("0"); //Si hay un 0 en la posicion comparada se imprime "0"
        }
        if(i == 4)
            printf("\t");
        mask = mask >> 1; //Se desplaza la mascara un valor (de forma binaria se divide por dos, así hasta llegar a 0x01)
    } 
}
void show_bin32 (uint32_t val)
{
    uint32_t aux;
    uint32_t mask= 1 << 31;
    for(int i=0; i<32; i++)
    {
        if(i%4 == 0 && i != 0)
            printf("\t");
        if(i%8 == 0 && i != 0)
            printf("-\t");
        aux= val & mask;
        if(aux != 0)
            printf("1");
        else
            printf("0");
        mask = mask >> 1;
    }
}
uint32_t set_bit32(uint32_t data, uint8_t bit_pos, bool bit_value)
{
    uint32_t mask= 1 << bit_pos; //Se le asigna un 1 en bit_pos a la mascara, y los demas valores seran 0
    if(bit_pos > 32) //Si se ingresa una cantidad de posiciones de bits mayores a 32 se muestra error
    {
        printf("\nCantidad de posiciones excedidas\n");
        return 0;
    } else{
            if(bit_value) //Si bit_value es "true" se cambia el valor de data en bit_pos por un 1
                data = data | mask;
            else {//Si bit_value es "false" se cambia el valor de data en bit_pos por un 0
                mask = ~mask;
                data = data & mask;
            }
    return data;
    }
}
uint32_t toogle_bit32(uint32_t data, uint8_t bit_pos)
{
    uint32_t mask= 1<< bit_pos; //Se le asigna un 1 en bit_pos a la mascara, y los demas valores seran 0
    if(bit_pos < 32 ){
        data = data ^ mask; //Se compara con un XOR, si en bit_pos hay un 1, se convierte en 0, y si hay un 0 se convierte en 1
        return data;    
    }else{
        printf("\nCantidad de posiciones excedidas\n");
        return 0;
    }
}
uint32_t carry_rotate32(uint32_t data, int8_t N)
{   
    uint32_t aux;
    if(N<32)
    {
        if(N>0)  //Rota a la derecha >>
        {      
            aux= data >> (32 - N); //Se guardan los bits que se van a caer
            data = (data << N) | (aux); //Se desplaza a la derecha data N bits, y se compara con un OR con aux, si alguno de los bits es 1 se coloca un 1
        } else{ //Rota a la izquierda <<
            N= -N;  //Se hace positivo N
            aux= data << (32 - N);  //Se guardan los bits que se van a caer
            data= (data >> N) | (aux); //Se desplaza a la izquierda data N bits, y se compara con un OR con aux, si alguno de los bits es 1 se coloca un 1
        }
    } else{
        printf("\nCantidad de posiciones excedidas\n");
        return 0;
    }
    return data;
}
uint32_t exxtract_segment(uint32_t data, uint8_t startBit, uint8_t endBit)
{
   if(endBit < 32 && startBit <= endBit){
        uint32_t mask = ((1 << (endBit - startBit + 1)) - 1); //Se llena la mascara de unos desde star hasta end, y las demas posiciones seran 0
        data = (data >> startBit) & mask; /*Con la operacion AND se eliminan los bits que no estan en el rango deseado, como mask tiene unos en el segmento de posiciones que se desean guardar y cero en las demas posiciones, la operacion ADN mantiene solo los bits que se quieran guardar
            luego se desplazan el resultado del AND startBit veces, los bits que se caen se descartan y se colocan ceros*/
    } else{
        printf("\nRango de posiciones incorrecto\n");
        return 0;
    }
    return data;
}