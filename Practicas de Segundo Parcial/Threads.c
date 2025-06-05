// Compilar con: gcc -o p p.c -lpthread */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *p_msg(void *ptr);
int main()
{
    // cuando se invocan estos hilos, se reservan espacios que debemos luego indicar con &
    pthread_t thread1, thread2;

    char *msg1 = "\033[31mA";
    char *msg2 = "\033[36mB";
    int r1, r2;

    // crear hilos independientes donde cada uno ejecuta una funcion
    r1 = pthread_create(&thread1, NULL, p_msg, (void *)msg1);
    r2 = pthread_create(&thread2, NULL, p_msg, (void *)msg2);

    // esperar hasta que los hilos esten completos antes de que el main continue
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Thread 1 return %d\n", r1);
    printf("Thread 2 return %d\n", r2);
    exit(0);
    return 0;
}

void *p_msg(void *ptr)
{
    char *m;
    m = (char *)ptr;
    while (1)
    {
        printf("%s", m);
    }
}
