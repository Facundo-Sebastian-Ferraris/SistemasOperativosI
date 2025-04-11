
#include <ANSI.h>
#include <xinu.h>
#define KB(n) (1024UL * (n))

void emit3(char c);

xsh_intro_procesos3(void) {
    // creacion de los procesos
    pid32 proceso1 = create(emit3, KB(8), 1, "process 1", 1,
                            '0'); // emitira un espacio con fondo rojo
    pid32 proceso2 = create(emit3, KB(8), 1, "process 2", 1,
                            ' '); // emitira un espacio con fondo azul

    // ejecucion de los procesos
    resume(proceso1);
    resume(proceso2);

    // esperar 5 segundos
    sleep(2);

    // finalizacion de procesos
    kill(proceso1);
    kill(proceso2);

    // pantalla final
    kprintf(aCLEAR aHOME);
    kprintf("🔱PROCESOSFINALIZADO!!!🔱\n");
}

void emit3(char c) {
    while (1) {
        putc(CONSOLE, c);
    }
}