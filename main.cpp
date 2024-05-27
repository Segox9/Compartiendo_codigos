#include "binary_operations_lib.h"
#include "dinamic_memory.h"
#include <stdio.h>
void shellSort(uint32_t *arr, int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            int temp = *(arr+i);
            int j;
            for (j = i; j >= gap && *(arr+j-gap) > temp; j -= gap) {
                *(arr+j) = *(arr+j-gap);
            }
            *(arr+j) = temp;
        }
    }
}
void pos_mayor(uint32_t *v, int n){
    uint32_t may;
    may= v[0];
    int posmay=0;
    for(int i=0; i<n; i++){
        if(v[i]>may){
            may=v[i];
            posmay=i;
        }
    }
    printf("%d", posmay);
}
int main()
{
    FILE *f = fopen("C:\\Users\\lauta\\Desktop\\SEGOVIA LAUTARO\\Parciales\\Info2\\InformaticaII_2024\\Tp union-maps\\motors.dat", "rb");
    if(f == NULL){
        printf("El archivo no existe\n");
        return 0;
    }
    uint32_t dato;
    uint32_t *motor;
    uint32_t *w, *V, *I, *T, *type;
    int c=0;
    while(fread(&dato, sizeof(uint32_t), 1, f) != 0)
    {
        c++;
    }
    motor = new uint32_t[c];
    w = new uint32_t[c];
    V = new uint32_t[c];
    T = new uint32_t[c];
    type = new uint32_t[c];
    I = new uint32_t[c];
    int i=0;
    rewind(f);
    
    while(fread(motor+i, sizeof(uint32_t), 1, f) != 0)
    {
        w[i]= exxtract_segment(motor[i], 28, 31);
        V[i]= exxtract_segment(motor[i], 20, 27);
        I[i]= exxtract_segment(motor[i], 16, 19);
        T[i]= exxtract_segment(motor[i], 5, 13);
        type[i]= exxtract_segment(motor[i], 3, 4);
        i++;
    } 
    for(i=0; i<c; i++){
        printf("\n-----------");
        
        if(type[i] == 0){
        printf("\nTipo: Brushless");
        printf("\nTorque: %d N.m", T[i]);
        printf("\nVoltaje: %d Volt", V[i]);
        printf("\nCorriente: %d Amper", I[i]);
        printf("\nPeso: %d Kg", w[i]);
        }
        if(type[i] == 1){
        printf("\nTipo: Brushed");
        printf("\nTorque: %d N.m", T[i]);
        printf("\nVoltaje: %d Volt", V[i]);
        printf("\nCorriente: %d Amper", I[i]);
        printf("\nPeso: %d Kg", w[i]);
        }
        if(type[i] == 2){
        printf("\nTipo: Induction");
        printf("\nTorque: %d N.m", T[i]);
        printf("\nVoltaje: %d Volt", V[i]);
        printf("\nCorriente: %d Amper", I[i]);
        printf("\nPeso: %d Kg", w[i]);
        }
        if(type[i] == 3){
        printf("\nTipo: DC");
        printf("\nTorque: %d N.m", T[i]);
        printf("\nVoltaje: %d Volt", V[i]);
        printf("\nCorriente: %d Amper", I[i]);
        printf("\nPeso: %d Kg", w[i]);
        }
    }
    uint32_t *prop;
    prop = new uint32_t [c];
    uint32_t *pot= new uint32_t[c];
 
    for(i=0; i<c; i++)
        pot[i]=V[i]*I[i];
    for(i=0; i<c; i++)
        prop[i]= T[i]/pot[i];
    printf("\nMejor motor con relacion Torque/potencia:\n");
    pos_mayor(prop, c);

    shellSort(T, c);   
    printf("\nTorque ordenado de forma ascendente:\n");
    for(i=0; i<c; i++){
        printf("[%d]\t", T[i]);
    }

    delete []pot;
    delete []prop;
    delete []motor;
    delete []w;
    delete []V;
    delete []T;
    delete []type;
    fclose(f);
}