#include "gps_data.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f    = fopen("file.dat","rb");

    //go to the end of the file
    fseek( f , 0 , SEEK_END);
    int size_bytes = ftell( f );
    int count_elements = size_bytes / sizeof(struct Data);

    //rewind the file
    fseek( f , 0 , SEEK_SET );
    //rewind( f );

    struct Data d[1000];
    fread( d , sizeof(struct Data) , count_elements , f );
    for( int i=0 ; i<count_elements ; i++ )
        printf("temp: %f\n",d[i].temp);

    fclose(f);
    return 0;
}
