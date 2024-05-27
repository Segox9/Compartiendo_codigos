#include "binary_operations_lib.h"
#include <stdio.h>
struct fecha{
    uint32_t año;
    uint32_t mes;
    uint32_t dia;
};

struct tarifa{
    uint32_t ent; //parte entera de la tarifa
    uint32_t dec; //parte decimal de la tafifa
};

struct registro{
    struct fecha Fec; //fecha
    struct tarifa Tar; //Tarifa kWh
    uint32_t ID; //DNI del usuario 
    uint32_t cons_ad; //consumos adeudados
    float *consumo;
};

typedef struct registro Registro;

void imprimir_registros(Registro *v, int n){   
    printf("\n-----------------------------");
    printf("\n-----------------------------");
    for(int i=0; i<n; i++){
        printf("\nID del usuario: %d", v[i].ID);
        printf("\nFecha: %d/%d/%d", v[i].Fec.dia, v[i].Fec.mes, v[i].Fec.año);
        printf("\nTarifa %d.%d", v[i].Tar.ent, v[i].Tar.dec);
        printf("\nUltimo consumo: %f", v[i].consumo[0]);
        printf("\nPeriodos adeudados: %d", v[i].cons_ad);
        if(v[i].cons_ad > 0)
        {               
            for(int j=1; j<(v[i].cons_ad+1); j++){
                printf("\nConsumo adeudado: %f", v[i].consumo[j]);
            }
        }
        printf("\n--------------------------------------");
    }
}
//Funcion para unir dos vectores 
Registro* concat(Registro* vec_left, int left_size, Registro* vec_right, int right_size)
{
    Registro *aux= new Registro[left_size + right_size];
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

float total_cobrar(Registro *r, int n){
    float tot_cob=0;
    for(int i=0; i<n; i++){
        float total_usuario=0;
        for(int j=0; j<(r[i].cons_ad+1); j++)
        {
            total_usuario+= r[i].consumo[j];
        }
        total_usuario*= (r[i].Tar.ent+(r[i].Tar.dec/100));
        tot_cob+= total_usuario;
    }
return tot_cob;

}
int main()
{
    FILE *f1= fopen("C:\\Users\\lauta\\Desktop\\SEGOVIA LAUTARO\\Parciales\\Info2\\InformaticaII_2024\\InformaticaII_2024\\registro_copelco_1.dat", "rb");
    FILE *f2= fopen("C:\\Users\\lauta\\Desktop\\SEGOVIA LAUTARO\\Parciales\\Info2\\InformaticaII_2024\\InformaticaII_2024\\registro_copelco_2.dat","rb");
    FILE *f3= fopen("C:\\Users\\lauta\\Desktop\\SEGOVIA LAUTARO\\Parciales\\Info2\\InformaticaII_2024\\InformaticaII_2024\\registro_copelco_3.dat","rb");    
    if(f1 == NULL || f2 == NULL || f3 == NULL){
        printf("error al abrir el archivo\n");
        return 0;
    }
    uint32_t h;
    uint32_t c_cons;
    int c1=0;
    //determino cuantos registros hay
    while(fread(&h, sizeof(uint32_t), 1, f1) != 0)
    {
        c_cons= exxtract_segment(h, 16, 20);
        fseek(f1, sizeof(uint32_t), SEEK_CUR); //DNI del usuario
        fseek(f1, sizeof(float), SEEK_CUR); //ultimo consumo
        fseek(f1, c_cons*(sizeof(float)), SEEK_CUR); //consumos adeudados 
        c1++;
    }
    rewind(f1);
    int c2=0;
    while(fread(&h, sizeof(uint32_t), 1, f2) != 0)
    {
        c_cons= exxtract_segment(h, 16, 20);
        fseek(f2, sizeof(uint32_t), SEEK_CUR); //DNI del usuario
        fseek(f2, sizeof(float), SEEK_CUR); //ultimo consumo
        fseek(f2, c_cons*(sizeof(float)), SEEK_CUR); //consumos adeudados 
        c2++;
    }
    rewind(f2);
    int c3=0;
    while(fread(&h, sizeof(uint32_t), 1, f3) != 0)
    {
        c_cons= exxtract_segment(h, 16, 20);
        fseek(f3, sizeof(uint32_t), SEEK_CUR); //DNI del usuario
        fseek(f3, sizeof(float), SEEK_CUR); //ultimo consumo
        fseek(f3, c_cons*(sizeof(float)), SEEK_CUR); //consumos adeudados 
        c3++;
    }
    rewind(f3);
    //Leo los registros
    Registro *R1= new Registro[c1];
    uint32_t deud, id;
    float cns;
    int c=0;
    while(c<c1)
    {
        fread(&h, sizeof(uint32_t), 1, f1);
        //Extraigo la tarifa del encabezado
        R1[c].Tar.dec = exxtract_segment(h, 21, 25);
        R1[c].Tar.ent = exxtract_segment(h, 26, 31);
        //Extraigo la fehca del encabezado 
        R1[c].Fec.año = exxtract_segment(h, 9, 15);
        R1[c].Fec.mes = exxtract_segment(h, 5, 8);
        R1[c].Fec.dia = exxtract_segment(h, 0, 4);
        //Extraigo los meses adeudados del encabezado
        deud= exxtract_segment(h, 16, 20);
        if(deud > 0){
            R1[c].cons_ad = deud;
            R1[c].consumo = new float[deud+1];
        } else{
            R1[c].cons_ad = 0;
            R1[c].consumo = new float[1];
        }
        fread(&id, sizeof(uint32_t), 1, f1);
        R1[c].ID= id;
        if(deud >0){ //si tiene deudas, se guarda el ultimo consumo + los adeudados
            int i=0;
            while(i<(deud+1)){
                fread(&cns, sizeof(float), 1, f1);
                R1[c].consumo[i]= cns;
                i++;
            }
        }else{  //sino tiene deudas, se guarda unicamente el ultimo consumo
            fread(&cns, sizeof(float), 1, f1); 
            *(R1[c].consumo)= cns;
        }
       c++;
    }
    Registro *R2= new Registro[c2];
    c=0;
    while(c<c2)
    {
        fread(&h, sizeof(uint32_t), 1, f2);
        //Extraigo la tarifa del encabezado
        R2[c].Tar.dec = exxtract_segment(h, 21, 25);
        R2[c].Tar.ent = exxtract_segment(h, 26, 31);
        //Extraigo la fehca del encabezado 
        R2[c].Fec.año = exxtract_segment(h, 9, 15);
        R2[c].Fec.mes = exxtract_segment(h, 5, 8);
        R2[c].Fec.dia = exxtract_segment(h, 0, 4);
        //Extraigo los meses adeudados del encabezado
        deud= exxtract_segment(h, 16, 20);
        if(deud > 0){
            R2[c].cons_ad = deud;
            R2[c].consumo = new float[deud+1];
        } else{
            R2[c].cons_ad = 0;
            R2[c].consumo = new float[1];
        }
        fread(&id, sizeof(uint32_t), 1, f2);
        R2[c].ID= id;
        if(deud >0){ //si tiene deudas, se guarda el ultimo consumo + los adeudados
            int i=0;
            while(i<(deud+1)){
                fread(&cns, sizeof(float), 1, f2);
                R2[c].consumo[i]= cns;
                i++;
            }
        }else{  //sino tiene deudas, se guarda unicamente el ultimo consumo
            fread(&cns, sizeof(float), 1, f2); 
            *(R2[c].consumo)= cns;
        }
       c++;
    }   
    Registro *R3= new Registro[c3];
    c=0;
    while(c<c3)
    {
        fread(&h, sizeof(uint32_t), 1, f3);
        //Extraigo la tarifa del encabezado
        R3[c].Tar.dec = exxtract_segment(h, 21, 25);
        R3[c].Tar.ent = exxtract_segment(h, 26, 31);
        //Extraigo la fehca del encabezado 
        R3[c].Fec.año = exxtract_segment(h, 9, 15);
        R3[c].Fec.mes = exxtract_segment(h, 5, 8);
        R3[c].Fec.dia = exxtract_segment(h, 0, 4);
        //Extraigo los meses adeudados del encabezado
        deud= exxtract_segment(h, 16, 20);
        if(deud > 0){
            R3[c].cons_ad = deud;
            R3[c].consumo = new float[deud+1];
        } else{
            R3[c].cons_ad = 0;
            R3[c].consumo = new float[1];
        }
        fread(&id, sizeof(uint32_t), 1, f3);
        R3[c].ID= id;
        if(deud >0){ //si tiene deudas, se guarda el ultimo consumo + los adeudados
            int i=0;
            while(i<(deud+1)){
                fread(&cns, sizeof(float), 1, f3);
                R3[c].consumo[i]= cns;
                i++;
            }
        }else{  //sino tiene deudas, se guarda unicamente el ultimo consumo
            fread(&cns, sizeof(float), 1, f3); 
            *(R3[c].consumo)= cns;
        }
       c++;
    }
    printf("\nR1:\n");
    imprimir_registros(R1, c1);
    printf("\nR2:\n");
    imprimir_registros(R2, c2);
    printf("\nR3:\n");
    imprimir_registros(R3, c3);
    //Total a cobrar 
    float Tot_cobR1= total_cobrar(R1, c1);
    printf("\nTotal a cobrar R1: %f", Tot_cobR1);
    float Tot_cobR2= total_cobrar(R2, c2);
    printf("\nTotal a cobrar R2: %f", Tot_cobR2);
    float Tot_cobR3= total_cobrar(R3, c3);
    printf("\nTotal a cobrar R3: %f", Tot_cobR3);
    float Tot_cobT= Tot_cobR1+Tot_cobR2+Tot_cobR3;
    printf("\nTotal a cobrar: %f", Tot_cobT);
    
    FILE *ftxt= fopen("Registros_copelco.txt", "wb");
    for(int i=0; i<c1; i++){
        if(R1[i].cons_ad>0)
        {
            delete []R1[i].consumo;
        } else{
            delete []R1[i].consumo;
        }
    }
    for(int i=0; i<c2; i++){
        if(R2[i].cons_ad>0)
        {
            delete []R2[i].consumo;
        } else{
            delete []R2[i].consumo;
        }
    }
    for(int i=0; i<c3; i++){
        if(R3[i].cons_ad>0)
        {
            delete []R3[i].consumo;
        } else{
            delete []R3[i].consumo;
        }
    }

    delete []R1;
    delete []R2;
    delete []R3;
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(ftxt);
}