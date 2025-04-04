#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int num_hijos = 3;
    pid_t pids[num_hijos]; // Arreglo para PIDs 📋

    for (int i = 0; i < num_hijos; i++) {
        pids[i] = fork();   // Crear hijo y guardar su PID 🌱
        if (pids[i] == 0) { // Hijo 👶
            printf("Hijo %d: fork me dio %d, mi PID real es %d\n", i + 1,
                   pids[i], getpid());
            return 0; // Hijo termina aquí
        }
        // El padre sigue el bucle
    }

    // Padre imprime los PIDs guardados 👴
    for (int i = 0; i < num_hijos; i++) {
        printf("Padre: pids[%d] = %d\n", i, pids[i]);
    }
    return 0;
}