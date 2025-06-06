#include <xinu.h>

pid32 pidMaster = 1;
// Prototipos
int sqrt(int n) {
    int r = 1;
    if (n == 1) {
        return 1;
    }

    while (r * r <= n) {
        r++;
    }
    return r - 1;
}

void esPrimos() {
    int numero = receive();
    int limite = sqrt(numero);
    int divisor = 2;
    int a = numero % divisor;
    int esPrimos = a != 0;
    while (esPrimos && divisor < limite) {
        divisor++;
        a = numero % divisor;
        esPrimos = a != 0;
    }
    send(pidMaster, esPrimos);
}

void esBisiesto() {
    int numero = receive();
    int esBisiesto = (numero % 4 == 0) && (numero % 100 != 0 || numero % 400 == 0);
    send(pidMaster, esBisiesto);
}

xsh_parcial2() {
    pidMaster = getpid();
    pid32 pid_Proceso2 = create(esPrimos, 8 * 1024, 20, "pid_Proceso 2", 0);
    pid32 pid_Proceso3 = create(esBisiesto, 8 * 1024, 20, "pid_Proceso 3", 0);

    resume(pid_Proceso2);
    resume(pid_Proceso3);
    int i;
    char buf[10];
    kprintf("INGRESE UN NRO: ");
    read(CONSOLE, buf, 10);
    i = atoi(buf);
    kprintf("el numero ingresado entero es %d \n", i);

    send(pid_Proceso2, i);
    int esPrimosV = receive();
    send(pid_Proceso3, i);
    int esBisiestoV = receive();

    kprintf("%d es :\n", i);
    if (esPrimosV) {
        kprintf("Primo\n");
    }

    if (esBisiestoV) {
        kprintf("Bisiesto\n");
    }

    if (!esPrimosV && !esBisiestoV) {
        kprintf("Nada :(\n");
    }
}