#include <ANSI.h>
#include <xinu.h>

// Prototipos de funciones
void emit2(char c);
int procesoA(void); // Añadido void como parámetro para claridad

xsh_intro_procesos2(void) {
    // creacion de los procesos
    pid32 proceso1 =
        create(procesoA, 1024, 30, "process 1", 0); // emitira un espacio con fondo rojo
    pid32 proceso2 =
        create(emit2, 1024, 30, "process 2", 1, 'B'); // emitira un espacio con fondo azul

    // ejecucion de los procesos
    resume(proceso1);
    resume(proceso2);

    // esperar 3 segundos
    sleep(10);

    // finalizacion de procesos
    kill(proceso1);
    kill(proceso2);

    // pantalla final

    kprintf("\n🔱PROCESOSFINALIZADO!!!🔱\n");
    return 0; // Añadido return
}

int procesoA(void) { // Añadido void como parámetro
    int pid = create(emit2, 1024, 35, "process 1", 1, 'C');
    resume(pid);
    emit2('A');
    return 0;
}

void emit2(char c) {
    int i = 0;
    while (++i < 36000) {
        putc(CONSOLE, c);
    }
}