#include <xinu.h>

// Prototipos
int esPrimo(int n);
void intervaloPrimos(char flag, int desde, int hasta);
int raizCuadrada(int n);
void intervalo(char flag, int desde, int hasta);

xsh_primos() {
    pid32 proceso1 = create(intervalo, 1024, 22, "Izmael", 3, 'A', 0, 1000),
          proceso2 = create(intervaloPrimos, 1024, 21, "Balduino", 3, 'B', 1000, 5000);

    resume(proceso1);
    resume(proceso2);
}

void intervalo(char flag, int desde, int hasta) {
    int cantPrimos = 0;
    for (desde; desde <= hasta; desde++) {
        if (esPrimo(desde)) {
            kprintf("%c\t%d\n", flag, desde);
            if (++cantPrimos == 100) {
                kprintf("A DORMIR 💖\n");
                sleepms(100);
                kprintf("ME DESPERTE 🚀\n");
            }
        }
    }
}

int raizCuadrada(int n) {
    int r = 0;
    while (r * r < n) {
        r++;
    }
    return r;
}

int esPrimo(int n) {
    if (n == 2) {
        return 1;
    }

    int i = 2;
    int esPrimo = n >= 2;
    int tope = raizCuadrada(n);
    while (esPrimo && i <= tope) {
        esPrimo = n % i != 0;
        i++;
    }

    return esPrimo;
}
void intervaloPrimos(char flag, int desde, int hasta) {
    for (desde; desde <= hasta; desde++) {
        if (esPrimo(desde)) {
            kprintf("%c\t%d\n", flag, desde);
        }
    }
};