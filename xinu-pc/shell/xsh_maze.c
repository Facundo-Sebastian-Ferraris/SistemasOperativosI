#include <stdlib.h>
#include <xinu.h>
// clang-format off
#include <clock.h>
// clang-format on

#define Wall "\033[48;2;248;58;0m  \033[0m"
#define Wall2 "\033[48;2;255;163;71m  \033[0m"
// Prototipos
int max = 50;
void rellenar(int matriz[][max]);
void renderizar(int matriz[][max]);

xsh_maze() {
    kprintf("\033[2J");
    srand(getticks());
    int matriz[max][max];

    rellenar(matriz);
    renderizar(matriz);

    kprintf("\n");
}

void rellenar(int matriz[][max]) {
    for (int i = 0; i < max; i++) {
        for (int j = 0; j < max; j++) {
            matriz[i][j] = rand() % 3;
        }
    }
}

void renderizar(int matriz[][max]) {
    for (int i = 0; i < max; i++) {
        for (int j = 0; j < max; j++) {
            if (matriz[i][j] == 1) {
                kprintf(Wall);
            }
        }
        kprintf("\n\r");
    }
}
