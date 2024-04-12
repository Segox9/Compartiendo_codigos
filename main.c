#include "gps_data.h"
#include <stdio.h>
#include <stdlib.h>

#define N 20

int main()
{
    FILE *f    = fopen("file.dat","wb");
    FILE *ftxt = fopen("file.txt","wb");
    if( f == NULL || ftxt == NULL )
    {
        printf("error opening the file");
        return 0;
    }
    struct Data d[N];
    for( int i=0 ; i<N ; i++ )
    {
        d[i].p.x = rand() % 100;
        d[i].p.y = rand() % 100;
        d[i].temp = rand() % 100;
        fwrite(d+i,sizeof(struct Data),1,f);
        fprintf(ftxt,"x: %f\n",d[i].p.x);
        fprintf(ftxt,"y: %f\n",d[i].p.y);
        fprintf(ftxt,"temp: %f\n",d[i].temp);
        fprintf(ftxt,"---------------------------\n");
    }
    fclose(f);
    fclose(ftxt);
    return 0;
}
