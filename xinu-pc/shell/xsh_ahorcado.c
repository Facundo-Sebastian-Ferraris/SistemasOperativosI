#include <xinu.h>
#include <ANSI.h>

// Prototipos
void llenarConGuiones(char palabra[]); // guiones(5) => "-----"
int develar(char *secreto, char *palabra, char ingresado);
int sonIguales(char *A, char *B);
void clear();
// Variables Globales
char c;
xsh_ahorcado()
{
    char PALABRA[] = "rombicosidodecaedro";
    int PALABRA_largo = sizeof(PALABRA) - 1;
    char SECRETO[PALABRA_largo + 1];
    int i = 0;

    while (i < PALABRA_largo)
    {
        SECRETO[i] = '-';
        i++;
    }

    int vidas = 5;
    /* Decirle al sistema que el modo input es RAW */
    clear();
    kprintf("\t\t\t\033[31mA\033[33mH\033[32mO\033[36mR\033[34mC\033[35mA\033[31mD\033[33mO\033[0m 📿\t\t\n\n");
    control(CONSOLE, TC_MODER, 0, 0);
    while (1)
    {
        kprintf(aSAVE "\t❤️: %d\n", vidas);
        kprintf("\t✏️  %s\n", SECRETO);
        kprintf("\tc = %c\n\n\tingrese una letra (0 para salir):", c, vidas);
        c = getc(stdin);
        kprintf(aLOAD);
        if (c == '0')
        {
            break;
        }

        if (!develar(SECRETO, PALABRA, c))
        {
            vidas--;
            if (vidas == 0)
            {
                clear();
                kprintf("\t\t\t💀 GAME OVER 💀 \n\n\t\tLa palabra era: %s\n\n\t\t [tecla cualquiera para salir]",
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
            clear();
            kprintf("\t\t\t✨ GANASTE! ✨\n\n\t\tLa palabra era: %s\n\n\t\t[tecla cualquiera para salir]",
                    PALABRA); // Borra toda la línea y mueve
            c = getc(stdin);

            if (c != NULL)
            {
                break;
            }
        }
    }
    clear();
    control(CONSOLE, TC_MODEC, 0, 0);
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
    kprintf(aCLEAR aHOME);
}

// AYUDA:
//  #include <stdio.h>

// int main() {
//     char *S = "Hola";
//     kprintf("Dirección: %p\n", (void *)S);   // Dirección de "Hola"
//     kprintf("Primer carácter: %c\n", *S);    // 'H'
//     kprintf("String completo: %s\n", S);     // "Hola"
//     kprintf("Segundo carácter: %c\n", *(S + 1)); // 'o'
//     return 0;
// }
