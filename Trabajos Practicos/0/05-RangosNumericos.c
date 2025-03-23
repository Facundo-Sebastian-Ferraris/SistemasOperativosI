#include <limits.h>
#include <stdio.h>

int main() {
    char i;
    unsigned char j;

    printf("tamanio de i: %zu\n", sizeof(i));
    printf("tamanio de j: %zu\n", sizeof(j));

    printf("Utilizado libreria \"<limits.h>\" 📚, donde se guardan las "
           "constantes "
           "de dichos rangos 📐 \n\n");
    printf("Rango de char 🅰️:\t\t %d \ta %d\n", CHAR_MIN, CHAR_MAX);
    printf("Rango de signed char ✔️ ➖ ➕:\t %d \ta %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("Rango de unsigned char ❌ ➖:\t 0 \ta %u\n", UCHAR_MAX);

    return 0;
}