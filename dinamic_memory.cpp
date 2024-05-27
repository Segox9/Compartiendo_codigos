#include "dinamic_memory.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * @brief Retorna el menor valor 
 * 
 * Esta función recibe dos enteros, los compara y devuelve el menor de ellos
 * 
 * @param a entero 
 * @param b entero 
 * @return int 
 */
int min(int a, int b)
{
    if(a<b)
        return a;
    return b;
}

/**
 * @brief Retorna un puntero redimensionado
 * 
 * Esta funcion reserva una nueva cantidad de memoria en un vector dinámico
 * 
 * @param old_vec puntero que referencia al vector viejo 
 * @param old_size tamaño del vector viejo
 * @param nw_size nuevo tamaño
 * @return puntero de tipo entero
 */
int* resize(int* old_vec, int old_size, int nw_size)
{
    int *aux= new int[nw_size];
    int smallest= min(old_size, nw_size);   //Dimension mas chica a recorrer
    for(int i=0; i<smallest; i++)
        aux[i]=old_vec[i];
    delete []old_vec;           //Libera la memoria utilizada por el vector viejo
    return aux;
}
//Funcion para remover un valor de un vector en determinada posicion
int* removeItem(int* vec, int vec_size, int item_pos)
{  
    if(item_pos < 0 || item_pos >= vec_size) {
        return nullptr; // Posición inválida
    }
    int cv=0;
    int *aux= new int[vec_size -1];
    for(int i=0; i<vec_size; i++)
    {
        if(i != item_pos)   //Cuando se llegue al elemento de la posicion solicitada, este no se copiara y avanzara al siguiente elemento
            aux[cv++] = vec[i];
    }
    delete []vec;
    return aux;   
}
//Funcion para insertar un valor en una determinadad posicion de un vector
int* insertItem(int* vec, int vec_size, int insert_pos, int insert_value)
{
    int *aux= new int[vec_size];
    int cv=0;
    for(int i=0; i<vec_size; i++)
    {
        if(i != insert_pos)     //Se copiaran los valores del vector hasta que se llegue a la posicion en la que se desea insertar el valor nuevo
            aux[cv++]=vec[i];
            else{               
                aux[cv++]=insert_value;     //Cuando se llega a la posicion de inserccion se copia el valor deseado
            }
    }
    delete []vec;
    return aux;
}
//Funcion para unir dos vectores 
int* concat(int* vec_left, int left_size, int* vec_right, int right_size)
{
    int *aux= new int[left_size + right_size];
    for(int i=0; i<(left_size+right_size); i++)
    {
        if(i < left_size) //Se copian los valores del primer vector y una vez que se recorrio por completo se copian los elementos del segundo
            aux[i]=vec_left[i];
        else{
            aux[i]=vec_right[i-left_size]; 
        }

    }
    delete []vec_left;
    delete []vec_right;
    return aux;   
}