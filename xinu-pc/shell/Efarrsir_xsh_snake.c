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
int map[55][36], x_snake = 27, y_snake = 17,

                 x_max = 54, y_max = 35, snakeValue = 8;
int suspendido = 0;

int perdido = 0;
char tecla = 'd';
// PROTOTIPOS
void rellenarConCeros(void), crearMarco(void), imprimirArreglo(void),
    renderizarArreglo(void), avance(void);

// MAIN 🔱
void xsh_snake(void) {
    kprintf(aCLEAR aHOME);

    resetGame();
    srand(getticks()); // Inicializar semilla
    pid32 renderer = create(renderizarArreglo, 16 * 1024, 20, "renderer", 0);
    pid32 avanzador = create(avance, 16 * 1024, 20, "avanzador", 0);

    control(CONSOLE, TC_MODER, 0, 0);
    resume(renderer);
    resume(avanzador);
    while (1) {
        tecla = getc(stdin);

        // exit
        if (tecla == '0') {
            break;
        }

        if (tecla == 'p') {
            if (suspendido == 0) {
                suspendido = 1;
                sleepms(100);
                kprintf("\033[5;30H JUEGO PAUSADO");
            } else {
                suspendido = 0;
            }
        }

        if (tecla == 'r') {
            resetGame();
        }
    }

    control(CONSOLE, TC_MODEC, 0, 0);
    kill(renderer);
    kill(avanzador);
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
    tecla = 'd';
    suspendido = 0;
    perdido = 0;
    spawnComida();
}

void simularCola(void) {
    for (int i = 1; i < 35; i++) {
        for (int j = 1; j < 54; j++) {
            if (map[j][i] > 0) {
                map[j][i]--;
            }
        }
    }
}

void avance(void) {
    char actual = 'd';
    while (1) {
        if (!suspendido) {
            /* code */

            sleepms(60);
            int condicion =
                (tecla == 'w' && actual != 's') || (tecla == 'a' && actual != 'd') ||
                (tecla == 's' && actual != 'w') || (tecla == 'd' && actual != 'a');

            if (condicion) {
                actual = tecla;
            }

            // direccionales
            switch (actual) {
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

            // limitadores
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

            // situaciones posicionales
            if (map[x_snake][y_snake] > 0) { // situacion de perdida
                perdido = 1;
            } else { // situacion NO perdida
                if (map[x_snake][y_snake] < 0) {
                    snakeValue++;
                    map[x_snake][y_snake] = snakeValue - 1;
                    spawnComida();
                } else {
                    map[x_snake][y_snake] = snakeValue;
                    simularCola();
                }
            }

            if (perdido) {
                suspendido = 1;
                sleepms(1000);
                kprintf("\033[5;30H" aSAVE "PERDISTE!!! Puntuacion: %d" aLOAD
                        "\033[B Presione R para reiniciar o 0 para cerrar!",
                        snakeValue - 1);
            }
        }
    }
}

void spawnComida(void) {
    int min = 1;
    int x = min + (rand() % (x_max - 1 - min + 1));
    int y = min + (rand() % (y_max - 1 - min + 1));
    int condicion = map[x][y] < 0;
    while (!condicion) {
        x = min + (rand() % (x_max - 1 - min + 1));
        y = min + (rand() % (y_max - 1 - min + 1));
        condicion = map[x][y] <= 0;
    }
    map[x][y] = -1;
}

// RENDERIZADO 🖌️
void renderizarArreglo(void) {
    int tiki = 1;
    int taki = 0;

    while (1) {
        if (!suspendido) {

            sleepms(60);
            kprintf(aHOME); // Limpiar pantalla
            for (int i = 0; i < 36; i++) {
                for (int j = 0; j < 55; j++) {
                    if (map[j][i] > 0) {
                        switch (taki) {
                        case 0:
                            kprintf(AMIGOSERPENTINO1);
                            break;

                        default:
                            kprintf(AMIGOSERPENTINO2);
                            break;
                        }
                    } else if (map[j][i] < 0) {
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
}
