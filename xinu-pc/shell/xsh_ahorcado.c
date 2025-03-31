#include <xinu.h>
#include <stdio.h>

// Prototipos
void llenarConGuiones(char palabra[]); // guiones(5) => "-----"
int develar(char *secreto, char *palabra, char ingresado);
int sonIguales(char *A, char *B);
void clear();
// Variables Globales
char c;
xsh_ahorcado()
{
    char PALABRA[] = "pantera";
    int PALABRA_largo = sizeof(PALABRA) - 1;
    char SECRETO[PALABRA_largo + 1];
    int i = 0;

    while (i < PALABRA_largo)
    {
        SECRETO[i] = '-';
        i++;
    }

    printf("%d \t %s \n\n", sizeof(SECRETO), SECRETO);
    int vidas = 5;
    /* Decirle al sistema que el modo input es RAW */
    clear();
    printf("\033[2K");
    printf("\t\t\033[31mA\033[33mH\033[32mO\033[36mR\033[34mC\033[35mA\033[31mD\033[33mO\033[0m 📿\t\t\n\n");
    control(CONSOLE, TC_MODER, 0, 0);
    while (1)
    {

        printf("\r ✏️   %s\t", SECRETO);
        printf("c = %c  ❤️: %d ingrese una letra (0 para salir):", c, vidas);
        c = getc(stdin);

        if (c == '0')
        {
            break;
        }

        if (!develar(SECRETO, PALABRA, c))
        {
            vidas--;
            if (vidas == 0)
            {
                printf("\033[2K\033[2A\033[2K\r 💀 GAME OVER 💀 \n\r la "
                       "palabra era: %s\n\r [tecla cualquiera para salir]",
                       PALABRA); // Borra toda la línea y mueve
                c = getc(stdin);

                if (c != NULL)
                {
                    break;
                }
            }
        }
        else if (sonIguales(SECRETO, PALABRA))
        {
            printf(
                "\033[2K\033[A\033[A\033[2K\r ✨ GANASTE! ✨ \n\r \n\r [tecla "
                "cualquiera para salir]"); // Borra toda la línea y mueve
            c = getc(stdin);

            if (c != NULL)
            {
                break;
            }
        }
    }
    control(CONSOLE, TC_MODEC, 0, 0);
    clear();
}

int sonIguales(char A[], char B[])
{
    int i = 0;
    while (A[i] != '\0' && B[i] != '\0' && A[i] == B[i])
    {
        i++;
    }
    return A[i] == B[i];
}

int develar(char secreto[], char palabra[], char ingresado)
{
    int r = 0;
    int i = 0;
    while (secreto[i] != '\0')
    {
        if (ingresado == palabra[i])
        {
            if (r == 0)
            {
                r = 1;
            }
            secreto[i] = ingresado;
        }
        i++;
    }
    return r;
}

void clear()
{
    printf("\033[2J\033[H");
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