// clang-format off
#include <xinu.h>
#include <ANSI.h>
#include <clock.h>
#include <prototypes.h>

#define PARED1 "\033[48;2;0;0;255m  \033[0m"
#define PARED2 "\033[48;2;0;255;0m  \033[0m"
#define PARED3 "\033[48;2;255;0;0m  \033[0m"

#define AMIGOSERPENTINO1 "\033[48;2;255;0;255m  \033[0m"
#define AMIGOSERPENTINO2 "\033[48;2;125;0;125m  \033[0m"

// Variable global
int 
    map[55][36],
    x_snake = 27,
    y_snake = 17,

    x_max = 54,
    y_max = 35,
    snakeValue = 8;
// PROTOTIPOS
void rellenarConCeros(void), crearMarco(void), imprimirArreglo(void),
    renderizarArreglo(void);

// MAIN 🔱
void xsh_snake(void) {
    kprintf(aCLEAR aHOME);

    resetGame();
    pid32 renderer = create(renderizarArreglo, 16 * 1024, 20, "renderer", 0);

    control(CONSOLE, TC_MODER, 0, 0);
    resume(renderer);

    char c;
    while (1) {
        c = getc(stdin);

        //direccionales
        switch (c) {
        case 'w':
            y_snake--;
            break;
        case 'a':
            x_snake--;
            break;
        case 's':
            y_snake++;
            break;
        case 'd':
            x_snake++;
            break;
        default:
            break;
        }

        //limitadores
        if (x_snake >= x_max) {
            x_snake = x_max - 1;
        } else if (x_snake <= 0) {
            x_snake = 1;
        }

        if (y_snake >= y_max) {
            y_snake = y_max - 1;
        } else if (y_snake <= 0) {
            y_snake = 1;
        }

        //situaciones posicionales
        if (map[x_snake][y_snake] > 0) { //situacion de perdida
            resetGame();
        } else { //situacion NO perdida
            if (map[x_snake][y_snake] < 0) {
                snakeValue++;
            }
            map[x_snake][y_snake] = snakeValue;
            simularCola();
        }

        // exit
        if (c == '0') {
            break;
        }
    }

    control(CONSOLE, TC_MODEC, 0, 0);
    kill(renderer);
    rellenarConCeros();
    kprintf(aCLEAR aHOME);
}
// FIN MAIN 🔱

// MATRIZADO ⚙️
void rellenarConCeros(void) {
    for (int i = 0; i < 36; i++) {
        for (int j = 0; j < 55; j++) {
            map[j][i] = 0;
        }
    }
}

void crearMarco(void) {
    for (int i = 0; i < 36; i++) {
        map[0][i] = -1;
        map[54][i] = -1;
    }
    for (int i = 0; i < 55; i++) {
        map[i][0] = -1;
        map[i][35] = -1;
    }
}

void imprimirArreglo(void) {
    for (int i = 0; i < 36; i++) {
        for (int j = 0; j < 55; j++) {
            kprintf("%d ", map[j][i]);
        }
        kprintf("\n");
    }
}

void resetGame(void) {
    rellenarConCeros();
    crearMarco();
    snakeValue = 2;
    x_snake = 27;
    y_snake = 17;
    map[x_snake][y_snake] = snakeValue-1;
    map[x_snake/2][y_snake/2] = -1;
    map[x_snake/2][y_snake] = -1;
    map[x_snake][y_snake/2] = -1;
}

void simularCola(void){
    for (int i = 1; i < 35; i++) {
        for (int j = 1; j < 54; j++) {
           if (map[j][i]>0){
            map[j][i]--;
           }
           
        }
    }
}

// RENDERIZADO 🖌️
void renderizarArreglo(void) {
    int tiki = 1;
    int taki = 0;

    while (1) {
        sleepms(60);
        kprintf(aHOME); // Limpiar pantalla
        for (int i = 0; i < 36; i++) {
            for (int j = 0; j < 55; j++) {
                if (map[j][i]>0){
                    switch (taki)
                    {
                    case 0:
                        kprintf(AMIGOSERPENTINO1);
                        break;
                    
                    default:
                        kprintf(AMIGOSERPENTINO2);
                        break;
                    }
                } else if (map[j][i]<0){
                    switch (tiki) {
                        case 0:
                            kprintf(PARED1);
                            break;
                        case 1:
                            kprintf(PARED2);
                            break;
                        default:
                            kprintf(PARED3);
                            break;
                        }
                } else {
                    kprintf("  ");
                }
                
                tiki = (++tiki) % 3; // Actualizar tiki para animación
                taki = (++taki) % 2;
            }

            if (i != 35) {
                kprintf("\n"); // Nueva línea, excepto en la última fila
            }
        }
        tiki = (++tiki) % 3; // Actualizar tiki globalmente
    }
}