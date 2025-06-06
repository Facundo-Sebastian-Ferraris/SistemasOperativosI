/*Desarrollar tres programas en XINU (tres procesos) que verifican si un número es primo
y/o es un año bisiesto. El proceso principal, debe esperar una entrada del usuario, y
luego, debe utilizar algún mecanismo de comunicación apropiado para enviar la entrada del
usuario a los procesos restantes. El proceso 2 verifica si el número es primo y reporta el
resultado al proceso principal. El proceso 3 verifica si el número es un año bisiesto y
reporta el resultado al programa principal. Ambos procesos deben reportar el resultado
usando el mismo mecanismo de comunicación que usó el programa principal. El programa
principal reporta si el número ingresado por el usuario es primo y/o año bisiesto. Para
leer una entrada del usuario en la CONSOLA y convertirlo en un número entero (las entradas
en la consola son “cadenas de texto”), aquí hay un código de ayuda:*/

#include <xinu.h>

#include <stdlib.h>

int pp;

void inicio(void), principal(void), bisiesto(void), primo(void);

void inicio() {
    pid32 pid2, pid3;
    char buf[10];
    pp = getpid();

    int numero;

    printf("Ingrese el numero a verificar si es bisiesto o primo :)\n");

    read(CONSOLE, buf, 10);
    numero = atoi(buf);

    printf("EL NUMERO LEIDO ES %d\n", numero);

    pid2 = create(bisiesto, 1024, 20, "proceso 2", 0);
    resume(pid2);
    send(pid2, numero);

    printf("SE ENVIO MENSAJE AL P2\n");
    int r1 = receive(); //

    if (r1 == 0) {

        printf("EL numero es bisiesto\n");

    } else {

        printf("EL numero no es bisiesto\n");
    }

    pid3 = resume(create(primo, 1024, 20, "proceso 3", 0));

    send(pid3, numero);

    int r2 = receive();

    if (r2 == 0) {

        printf("EL NUMERO ES PRIMO");

    } else {

        printf("EL NUMERO NO ES PRIMO");
    }
}

void bisiesto() {
    int n = receive(); // Recibe el numero a analizar
    kprintf("Mensaje Recibido\n");
    if ((n % 4 == 0 && n % 100 != 0) || (n % 400 == 0)) {

        send(pp, 0);

    } else {
        send(pp, 1);
    }
}

void primo() {

    int n = receive(); // Recibe el numero
    kprintf("Numero Recibido");
    int i = 2, prim = 1;

    while (i < n && prim == 1) {
        printf("proceso 2 %d", n);
        if (i % n == 0) {
            prim = 0;
        }

        i++;
    }

    send(pp, prim);
    exit();
}
