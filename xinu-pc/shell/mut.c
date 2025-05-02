/* mut.c - mut, operar, incrementar */
#include <xinu.h>
void operar(void), incrementar(void);
unsigned char x = 0;

// int isAvailable;
// int pid_sem = NULL;
// sid32 mutex;
// sid32 aux;

#define ROJO "\033[31m"
#define MAGENTA "\033[35m"
#define CIAN "\033[36m"
#define VERDE "\033[32m"
#define RESET "\033[0m"
/*------------------------------------------------------------------------
 * mut -- programa con regiones criticas
 *------------------------------------------------------------------------
 */
void mut(void) {
    mutex_init();
    int i;
    resume(create(operar, 1024, 20, "operador", 0));
    resume(create(incrementar, 1024, 20, "incrementador", 0));
    sleep(10);
}
/*------------------------------------------------------------------------
 * operar x e y
 *------------------------------------------------------------------------
 */
void operar(void) {
    int y = 0;
    while (1) {
        /* si x es multiplo de 10 */
        mutex_unlock();
        mutex_unlock();
        mutex_lock();
        sleepms(1000);
        if ((x % 10) == 0) {
            y = x * 2; /* como y es el doble de x entonces
                        * y es multiplo de 10 tambien
                        */
            /* si y no es multiplo de 10 entonces hubo un error */
            if ((y % 10) != 0) {
                printf("\r ERROR!! y=%d, x=%d \r", y, x);
            } else {
                printf("Si no existen mensajes de ERROR entonces todo va OK! \n");
            }
        }

        mutex_unlock();
    }
}
/*------------------------------------------------------------------------
 * incrementar x
 *------------------------------------------------------------------------
 */
void incrementar(void) {
    while (1) {
        sleepms(1000);
        mutex_lock();
        mutex_lock();
        mutex_lock();
        mutex_lock();
        x = x + 1;
        kprintf("\t aumentando x a %d!\n", x);
        mutex_unlock();
        mutex_unlock();
        mutex_unlock();
        mutex_unlock();
        mutex_unlock();
    }
}
