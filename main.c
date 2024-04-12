#include "gps_data.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f    = fopen("file.dat","rb");

    printf("ftell(): %d\n", ftell(f) );

//    struct Data d[1000];
//    fread( d , sizeof(struct Data) , ? , f );

    char c;
    fread( &c , sizeof(char) , 1 , f );
    fread( &c , sizeof(char) , 1 , f );
    fread( &c , sizeof(char) , 1 , f );
    fread( &c , sizeof(char) , 1 , f );
    fread( &c , sizeof(char) , 1 , f );

    printf("ftell(): %d\n", ftell(f) );

    fseek( f , -2 , SEEK_CUR );
    printf("ftell(): %d\n", ftell(f) );

    fclose(f);
    return 0;
}
