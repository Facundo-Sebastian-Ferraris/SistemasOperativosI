#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int esPrimo(int n);
void intervaloPrimos(char flag, int desde, int hasta);
int raizCuadrada(int n);

int main() {
    int pid = fork();
    if (pid < 0) {
        return 1;
    } else if (pid == 0) {
        intervaloPrimos('H', 1001, 5000);
    } else {
        intervaloPrimos('P', 0, 1000);
        // wait();
        kill(pid, SIGTERM);
    }

    return 0;
}

int raizCuadrada(int n) {
    int r = 0;
    while (r * r < n) {
        r++;
    }
    return r;
}

int esPrimo(int n) {
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
    for (int i = desde; i <= hasta; i++) {
        if (esPrimo(i)) {
            printf("%c\t%d\n", flag, i);
        }
    }
};
