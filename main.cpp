#include <stdio.h>
#include "file_read.h"



int main(){
    FILE *f = fopen("C:\\Users\\lauta\\Desktop\\SEGOVIA LAUTARO\\Parciales\\Info2\\Parcial1 (clase)\\network_structure.dat", "rb");
    if(f == NULL){
        printf("error al abrir el archivo\n");
        return 0;
    }
    int cant = countDevices(f);
    Registro *R= new Registro[cant];
    printf("\nCantidad de registros: %d", cant);
    rewind(f);
    fillRegister(f, R, cant);
    for(int i=0; i<cant; i++){
        printf("\nIDs: %d", R[i].ids.ID);
    }

    delete []R;
    fclose(f);
}