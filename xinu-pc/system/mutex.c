#include <xinu.h>
sid32 mutex;
int pid_sem;

void mutex_init()
{
    mutex = semcreate(1);
    pid_sem = NULL;
}

void mutex_lock()
{
    // si el pid del proceso actual, es distinto al pid registrado
    if (pid_sem != getpid())
    {                // entonces
        wait(mutex); // se queda en espera || logra obtener el semaforo
        // kprintf(VERDE "%s lograr tomar el semaforo!\n" RESET, proctab[getpid()].prname);
        pid_sem = getpid(); // se registra el pid del proceso que logro tomar el semaforo
        // sleepms(1000);
    }
    // else
    // {
    // kprintf(ROJO "Mismo proceso (%s) intenta lockear!\n" RESET,
    // proctab[getpid()].prname);
    // }

    // OBSERVACIONES:
    // La condicion no es critica pues los procesos siempre tienen una pid unica
    // ademas que el pid_sem alterna entra NULL o un proceso registrado,
    // por lo que si fuese un proceso NO REGISTRADO, la condicion SIEMPRE se va cumplir

    // Los procesos jamas tendran un pid igual a NULL
}

void mutex_unlock()
{
    if (pid_sem == getpid()) // si el pid del proceso es igual al pid registrado
    {
        pid_sem = NULL; // entonces cierra la sesion del proceso
        // kprintf(CIAN "%s libera su permiso!\n" RESET, proctab[getpid()].prname);
        // sleepms(1000);
        signal(mutex); // logra liberar el semaforo
    }
    // else
    // {
    //     kprintf(MAGENTA "Un proceso no registrado (%s) intenta liberar!\n" RESET,
    //             proctab[getpid()].prname);
    // }
}