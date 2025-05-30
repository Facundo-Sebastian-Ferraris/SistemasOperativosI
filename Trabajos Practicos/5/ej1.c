/* programa usamem.c */
#include <stdio.h>
#include <stdlib.h>
#define N 240000
#define BSIZE 4096
#define SMALL 4
char *pp;
int main()
{
    int i, j, k;
    // printf("tamanio del malloc %d kb\n", (N * BSIZE) / 1024);
    pp = malloc(N * BSIZE);
    if (pp == NULL)
    {
        printf("Error al reservar memoria.\n");
        exit(1);
    }
    /* RECORREMOS y modificamos todo el segmento solicitado */
    for (j = 0; j < BSIZE; j++)
    {
        for (i = 0; i < N; i++)
        {
            *(pp + i * BSIZE + j) = 2; // pp[i][j] = 2;
        }
    }
    /* RECORREMOS y VERIFICAMOS QUE HEMOS MODIFICADO todo el segmento solicitado */
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < BSIZE; j++)
        {
            if (*(pp + i * BSIZE + j) != 2)
            { // if (pp[i][j] != 2)
                printf("ERROR! \n");
                exit(1);
            }
        }
    }
    printf("OK, \ndireccion de pp :\t %p"
           "\ndireccion de i:\t%p"
           "\ndireccion de j:\t%p"
           "\ndireccion de k:\t%p",
           "\ndireccion de main:\t%p",
           &pp, &i, &j, &k, (void *)&main);
    printf("\nPID: %d\n", getpid()); // Imprime el ID del proceso
    getchar();                       // Pausa hasta que presiones Enter
    return 0;
}