#include "file_read.h"


void fillRegister(FILE *f, Registro *r, int n){
    uint16_t id;
    uint16_t Llc;
    uint8_t type, inf;
    uint16_t UpID;
    int c=0;
    while(c<n)
    {
        fread(&id, sizeof(uint16_t), 1, f);
        r[c].ids.ID= id;
        fread(&Llc, sizeof(uint16_t), 1, f);
        fread(&type, sizeof(uint8_t), 1, f);
        fread(&inf, sizeof(uint8_t), 1, f);
        fread(&UpID, sizeof(uint16_t), 1, f);
        r[c].ids.ID_sup= UpID;
        fseek(f, Llc*(sizeof(uint16_t)), SEEK_CUR);
        c++;
    }
}

void showIDs(Registro *r, int n){

}
int countDevices(FILE *f){
    uint64_t h;
    uint64_t Llc;
    int cant;
    while(fread(&h, sizeof(uint64_t), 1, f))
    {
        Llc = (h << 16) >> 48;
        fseek(f, Llc*(sizeof(uint16_t)), SEEK_CUR);
        cant++;
    }
    return cant;
}
/*Registro getRegister(uint16_t ID){

}*/