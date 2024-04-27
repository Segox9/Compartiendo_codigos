
int min(int a,int b)
{
//    return a<b ? a : b;
    if( a < b )
        return a;
    return b;
}

int* resize(int *old_vector,int old_size, int new_size)
{
    
    int *aux = new int[new_size];
    int smallest = min(old_size,new_size); //el mas chico
    for( int i=0 ; i<smallest ; i++ )
        aux[i] = old_vector[i];

    delete []old_vector;
    return aux;
}

int main()
{
    int *v = new int[10];

    v = resize(v,10,25);


    delete []v;
    return 0;
}