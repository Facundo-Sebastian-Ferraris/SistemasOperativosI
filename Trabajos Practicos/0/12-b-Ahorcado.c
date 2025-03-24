#include <stdio.h>
#include <stdlib.h> /* para las funciones system y exit */

// Prototipos
char *guiones(int veces); // guiones(5) => "-----"
int develar(char *secreto, char *palabra, char ingresado);
int sonIguales(char *A, char *B);

int main() {
    char PALABRA[] = "hipopotomonstrosesquipedaliofobia";
    int PALABRA_largo = sizeof(PALABRA) - 1;
    char *SECRETO = guiones(PALABRA_largo);
    int vidas = 5;
    int c;
    /* Decirle al sistema que el modo input es RAW */
    system("/bin/stty raw");
    system("clear");
    printf("\033[2K\033[A\033[2K\033[A\033[2K\033[A\033[2K");
    printf("\t\tAHORCADO 📿\t\t\n\n");
    while (1) {

        printf("\r ✏️   %s\t", SECRETO);
        printf("c = %c  ❤️: %d ingrese una letra (0 para salir):", c, vidas);
        c = getchar();

        if (c == '0') {
            break;
        }

        if (!develar(SECRETO, PALABRA, c)) {
            vidas--;
            if (vidas == 0) {
                printf("\033[2K\033[A\033[A\033[2K\r 💀 GAME OVER 💀 \n\r la "
                       "palabra era: %s\n\r [tecla cualquiera para salir]",
                       PALABRA); // Borra toda la línea y mueve
                c = getchar();

                if (c != NULL) {
                    break;
                }
            }
        } else if (sonIguales(SECRETO, PALABRA)) {
            printf(
                "\033[2K\033[A\033[A\033[2K\r ✨ GANASTE! ✨ \n\r \n\r [tecla "
                "cualquiera para salir]"); // Borra toda la línea y mueve
            c = getchar();

            if (c != NULL) {
                break;
            }
        }
    }
    system("/bin/stty sane erase ^H");
    system("clear");
}

int sonIguales(char *A, char *B) {
    while (*A && *B &&
           *A == *B) { // Mientras ninguno sea '\0' y ambos sean iguales
        A++;
        B++;
    }
    return *A == *B; // Ultima Verificacion
}

int develar(char *secreto, char *palabra, char ingresado) {
    int r = 0;
    while (*secreto != '\0') {
        if (ingresado == *palabra) {
            if (r == 0) {
                r = 1;
            }
            *secreto = ingresado;
        }
        *palabra++;
        *secreto++;
    }
    return r;
}

char *guiones(int veces) {
    char *r = (char *)malloc(veces + 1);
    if (r == NULL) { // Verifica fallo de malloc
        return NULL;
    }

    // Llena con guiones
    for (int i = 0; i < veces; i++) {
        r[i] = '-';
    }
    r[veces] = '\0'; // Agrega el terminador nulo

    return r;
}

// AYUDA:
//  #include <stdio.h>

// int main() {
//     char *S = "Hola";
//     printf("Dirección: %p\n", (void *)S);   // Dirección de "Hola"
//     printf("Primer carácter: %c\n", *S);    // 'H'
//     printf("String completo: %s\n", S);     // "Hola"
//     printf("Segundo carácter: %c\n", *(S + 1)); // 'o'
//     return 0;
// }