// clang-format off
#include <xinu.h>
#include <ANSI.h>
#include <clock.h>
#include <prototypes.h>

// ========== DEFINICIONES DE COLORES ==========
#define COLOR_RESET   "\033[0m"
#define PARED1        "\033[48;2;0;0;255m  " COLOR_RESET
#define PARED2        "\033[48;2;0;255;0m  " COLOR_RESET
#define PARED3        "\033[48;2;255;0;0m  " COLOR_RESET
#define SNAKE_COLOR1  "\033[48;2;255;0;255m  " COLOR_RESET
#define SNAKE_COLOR2  "\033[48;2;125;0;125m  " COLOR_RESET

// ========== CONSTANTES DEL JUEGO ==========
#define MAX_X         55
#define MAX_Y         34
#define INIT_X        (MAX_X/2)
#define INIT_Y        (MAX_Y/2)
#define INIT_DIR      'd'
#define INIT_LENGTH   2
#define DELAY_MS      60

// ========== ESTADOS DEL JUEGO ==========
typedef enum {
    RUNNING,
    PAUSED,
    GAME_OVER
} GameState;

// ========== VARIABLES GLOBALES ==========
int mapa[MAX_X][MAX_Y];
int cabeza_x = INIT_X, cabeza_y = INIT_Y;
int longitud_serpiente = INIT_LENGTH;
int record = INIT_LENGTH-1;
GameState estado = RUNNING;
char direccion_actual = INIT_DIR;
char tecla=INIT_DIR;

// ========== PROTOTIPOS ==========
void inicializarJuego(void);
void crearMapa(void);
void resetearJuego(void);
void moverSerpiente(void);
void generarComida(void);
void actualizarCola(void);
void renderer(void);

// ========== FUNCIÓN PRINCIPAL ==========
void xsh_snake(void) {
    kprintf(aCLEAR aHOME);
    resetearJuego();
    
    srand(getticks());
    pid32 render_pid = create(renderer, 16 * 1024, 20, "render", 0);
    pid32 move_pid = create(moverSerpiente, 16 * 1024, 20, "move", 0);

    control(CONSOLE, TC_MODER, 0, 0);
    resume(render_pid);
    resume(move_pid);
    
    while (1) {
        tecla = getc(stdin);

        if (tecla == '0') break;  // Salir del juego

        if (estado != GAME_OVER) {
            if (tecla == 'p') {
                estado = (estado == PAUSED) ? RUNNING : PAUSED;
                if (estado == PAUSED) {
                    sleepms(100);
                    kprintf("\033[5;30H JUEGO PAUSADO");
                }
            }
        }

        if (tecla == 'r' && estado == GAME_OVER) {
            resetearJuego();
        }

    }

    control(CONSOLE, TC_MODEC, 0, 0);
    kill(render_pid);
    kill(move_pid);
    kprintf(aCLEAR aHOME);
}

// ========== FUNCIONES DEL JUEGO ==========
void inicializarJuego(void) {
    for (int y = 0; y < MAX_Y; y++) {
        for (int x = 0; x < MAX_X; x++) {
            mapa[x][y] = 0;
        }
    }
}

void crearMapa(void) {
    // Bordes horizontales
    for (int x = 0; x < MAX_X; x++) {
        mapa[x][0] = -1;
        mapa[x][MAX_Y-1] = -1;
    }
    
    // Bordes verticales
    for (int y = 0; y < MAX_Y; y++) {
        mapa[0][y] = -1;
        mapa[MAX_X-1][y] = -1;
    }
}

void resetearJuego(void) {
    inicializarJuego();
    crearMapa();
    cabeza_x = INIT_X;
    cabeza_y = INIT_Y;
    longitud_serpiente = INIT_LENGTH;
    direccion_actual = INIT_DIR;
    tecla=INIT_DIR;
    estado = RUNNING;
    generarComida();
}

void moverSerpiente(void) {
    while (1) {
        if (estado == RUNNING) {
            sleepms(DELAY_MS);
            // Validación de dirección
            if ((tecla == 'w' && direccion_actual != 's') ||
            (tecla == 'a' && direccion_actual != 'd') ||
            (tecla == 's' && direccion_actual != 'w') ||
            (tecla == 'd' && direccion_actual != 'a')) {
            direccion_actual = tecla;
    }

            // Actualizar posición según dirección
            switch (direccion_actual) {
                case 'w': cabeza_y--; break;
                case 'a': cabeza_x--; break;
                case 's': cabeza_y++; break;
                case 'd': cabeza_x++; break;
            }

            // Limitar movimiento dentro del mapa
            cabeza_x = (cabeza_x <= 0) ? 1 : (cabeza_x >= MAX_X-1) ? MAX_X-2 : cabeza_x;
            cabeza_y = (cabeza_y <= 0) ? 1 : (cabeza_y >= MAX_Y-1) ? MAX_Y-2 : cabeza_y;

            // Verificar colisiones
            if (mapa[cabeza_x][cabeza_y] > 0) {
                estado = GAME_OVER;
                sleepms(1000);

                kprintf("\033[5;30H" aSAVE "GAME OVER!" aLOAD );
                
                if (longitud_serpiente-1>record){
                    record = longitud_serpiente-1;
                    kprintf("\033[BNUEVO RECORD!!! Puntuacion: %d" aLOAD, record);
                } else{
                    kprintf("\033[BPuntuacion: %d" aLOAD, longitud_serpiente-1);
                }
                kprintf( "\033[2BPresione R para reiniciar o 0 para cerrar!");

            } 
            else if (mapa[cabeza_x][cabeza_y] < 0) {
                // Comer comida
                longitud_serpiente++;
                mapa[cabeza_x][cabeza_y] = longitud_serpiente;
                generarComida();
            } 
            else {
                // Movimiento normal
                mapa[cabeza_x][cabeza_y] = longitud_serpiente;
                actualizarCola();
            }
        }
    }
}

void generarComida(void) {
    int x, y;
    do {
        x = 1 + (rand() % (MAX_X - 2));
        y = 1 + (rand() % (MAX_Y - 2));
    } while (mapa[x][y] != 0);
    
    mapa[x][y] = -1;
}

void actualizarCola(void) {
    for (int y = 1; y < MAX_Y-1; y++) {
        for (int x = 1; x < MAX_X-1; x++) {
            if (mapa[x][y] > 0) {
                mapa[x][y]--;
            }
        }
    }
}

void renderer(void) {
    int anim_pared = 0;
    int anim_snake = 0;
    
    while (1) {
        if (estado == RUNNING) {
            sleepms(DELAY_MS);
            kprintf(aHOME);
            
            for (int y = 0; y < MAX_Y; y++) {
                for (int x = 0; x < MAX_X; x++) {
                    if (mapa[x][y] > 0) {
                        kprintf("%s", (anim_snake == 0) ? SNAKE_COLOR1 : SNAKE_COLOR2);
                    } else if (mapa[x][y] < 0) {
                        kprintf("%s", (anim_pared == 0) ? PARED1 : 
                                      (anim_pared == 1) ? PARED2 : PARED3);
                    } else {
                        kprintf("  ");
                    }

                    anim_pared = (anim_pared + 1) % 3;
                    anim_snake = (anim_snake + 1) % 2;
                }
                if (y != MAX_Y-1) kprintf("\n");
            }
            anim_pared = (anim_pared + 1) % 3;
            anim_snake = (anim_snake + 1) % 2;
            kprintf("\033[36;5H" aSAVE "Score: %d" aLOAD "\033[ARecord: %d", longitud_serpiente-1, record);
        }
    }
}