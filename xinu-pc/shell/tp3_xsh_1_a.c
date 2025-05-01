// clang-format off
#include <xinu.h>
#include <ANSI.h>

// Prototipos
void produce(void), consume(void);

// Variable compartida
int n = 0;
int maximo = 10;
// Semáforo para sincronización
sid32 rendevouz1;
sid32 rendevouz2;
sid32 mutex3;

// main 🔱🔱🔱
int xsh_Procesamiento() {
    // Inicializar el semáforo
    rendevouz1 = semcreate(1);
    rendevouz2 = semcreate(0);
    mutex3 = semcreate(0);


    // Crear procesos
    pid32 consume_pid = create(consume, 1024, 20, "consume", 0);
    pid32 produce_pid = create(produce, 1024, 20, "produce", 0);

    // Reanudar procesos
    kprintf("Iniciando procesos...\n");
    resume(consume_pid);
    resume(produce_pid);

    // Esperar a que los procesos terminen
    // sleep(2); // Ajusta según sea necesario

    // Liberar el semáforo
    wait(mutex3);
    kprintf("Liberando semaforo...\n");

    return 0;
}

void produce(void) {
    int32 i;
    for (i = 1; i <= maximo; i++) { // Reducido para pruebas
        wait(rendevouz1);
        n++;
        signal(rendevouz2);
    }
}

void consume(void) {
    int32 i;
    for (i = 1; i <=maximo; i++) { // Reducido para pruebas
        wait(rendevouz2);
        kprintf("\tConsumidor: The Value of n is %d\n", n);
        signal(rendevouz1);
    }
    signal(mutex3);

}