#pragma once
#include <stdint.h>
#include <stdio.h>

struct Sensor{
    uint8_t Flow;
    uint8_t Temp;
    uint8_t Presure;
    uint8_t Level;
};
struct Actuador{
    uint8_t Valve;
    uint8_t Motor;
};
struct Info{
    struct Sensor sens;
    struct Actuador act;
};

struct ID{
    uint16_t ID;
    uint16_t ID_sup;
    uint16_t *ID_inf; 
};
struct registro{
    struct ID ids;
    uint8_t type;
    struct Info infor;
};
typedef struct registro Registro;

void showIDs(Registro *r, int n);
int countDevices(FILE *f);
Registro getRegister(uint16_t ID);
void fillRegister(FILE *f, Registro *r, int n);