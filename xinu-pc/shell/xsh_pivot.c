#include <ANSI.h>
#include <xinu.h>

#define Pivot1 "\033[48;2;248;58;0m  \033[0m"   // rojo
#define Pivot2 "\033[48;2;255;163;71m  \033[0m" // amarillo
// Prototipos
int m = 15;
void shuffle(int matriz[][m]);
int mult = 1;
xsh_pivot() {
    char c;
    kprintf(aCLEAR aHOME);
    int matriz[m][m];
    shuffle(matriz);
    control(CONSOLE, TC_MODER, 0, 0);
    while (1) {
        if (mult == 1) {
            kprintf(aSAVE Pivot1);
        } else {
            mult = 1;
        }
        c = getc(stdin);
        switch (c) {
        case 'w': // arriba
            kprintf(aLOAD "  " aUP aLEFT aLEFT);
            break;
        case 's': // abajo
            kprintf(aLOAD "  " aDOWN aLEFT aLEFT);
            break;
        case 'a': // izquierda
            kprintf(aLOAD "  " aLEFT aLEFT aLEFT aLEFT);
            break;
        case 'd': // derecha
            kprintf(aLOAD "  ");
            break;
        default:
            mult = -1;
            break;
        }
        if (c == '0') {
            break;
        }
    }
    control(CONSOLE, TC_MODEC, 0, 0);
}

void shuffle(int matriz[][m]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            matriz[i][j] = 0;
            kprintf("  ");
        }
        kprintf(aHOME);
    }
}