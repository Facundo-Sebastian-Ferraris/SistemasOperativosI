#include <stdio.h>

// Variables globales
char i = 'a';
char j = 77;
char k = 0x4D;

// Prototipos
void printToBin(int a);

int main() {
    // clang-format off
    int 
        i_Decimal = (int)i, 
        j_Decimal = (int)j, 
        k_Decimal = (int)k;
    // clang-format on

    // Impresión con emojis y formato mejorado
    printf("🔢 Números en Decimal:\n");
    printf("----------------------\n");
    printf("👉 i = %d\n", i_Decimal);
    printf("👉 j = %d\n", j_Decimal);
    printf("👉 k = %d\n\n", k_Decimal);

    printf("🔍 Conversión a Binario:\n");
    printf("------------------------\n");

    printf("🟢 i en binario: ");
    printToBin(i_Decimal);
    printf("🟡 j en binario: ");
    printToBin(j_Decimal);
    printf("🔴 k en binario: ");
    printToBin(k_Decimal);
    printf("\n");

    printf("📚 Explicaciones:\n");
    printf("-----------------\n");
    printf("El método `printToBin`:\n");
    printf("\t✅ Recorre de izquierda a derecha (bit por bit) e imprime 1 y 0 "
           "secuencialmente.\n");
    printf("La instrucción `(a >> bit) & 1` realiza lo siguiente:\n");
    printf("\t✅ `(a >> bit)`: Desplaza `a`, `bit` veces hacia la derecha (ej: "
           "`(10010 >> 1) = 01001`).\n");
    printf("\t✅ `&`: Es el operador AND bitwise, que compara los bits menos "
           "significativos (ej: `1 & 0 = 0`; `1 & 1 = 1`).\n");

    return 0;
}

void printToBin(int a) {
    for (int bit = 31; bit >= 0; bit--) {
        printf("%d", (a >> bit) & 1);
        if (bit % 8 == 0) { // para separar por bytes
            printf(" ");
        }
    }
    printf("\n");
}