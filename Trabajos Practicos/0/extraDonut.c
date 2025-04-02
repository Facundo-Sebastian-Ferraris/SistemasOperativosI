#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> // Para usleep()

int main() {
    float A = 0, B = 0;
    float i, j;
    int k;
    float z[1760];
    char b[1760];

    printf("\x1b[2J"); // Limpiar pantalla

    while (1) {
        memset(b, 32, 1760); // Rellenar con espacios (ASCII 32)
        memset(z, 0, 7040);  // Limpiar buffer de profundidad

        for (j = 0; j < 6.28; j += 0.07) {
            for (i = 0; i < 6.28; i += 0.02) {
                // Cálculos 3D (sin cambios)
                float c = sin(i);
                float d = cos(j);
                float e = sin(A);
                float f = sin(j);
                float g = cos(A);
                float h = d + 2;
                float D = 1 / (c * h * e + f * g + 5);
                float l = cos(i);
                float m = cos(B);
                float n = sin(B);
                float t = c * h * g - f * e;
                int x = 40 + 30 * D * (l * h * m - t * n);
                int y = 12 + 15 * D * (l * h * n + t * m);
                int o = x + 80 * y;
                int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g -
                             l * d * n);

                if (y > 0 && y < 22 && x > 0 && x < 80 && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }

        printf("\x1b[H"); // Mover cursor al inicio
        for (k = 0; k < 1761; k++) {
            putchar(k % 80 ? b[k] : 10); // Imprimir línea por línea
        }

        // Ajuste para ~60 FPS
        A += 0.04;     // Velocidad de rotación en X
        B += 0.02;     // Velocidad de rotación en Y
        usleep(16667); // 16.667 ms ≈ 60 FPS (1/60 segundos)
    }

    return 0;
}