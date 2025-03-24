#include <limits.h>
#include <stdio.h>

int main() {
    signed char A = CHAR_MAX;
    unsigned char B = UCHAR_MAX;

    printf("🔵🔴 Comportamiento de desbordamiento (overflow) en chars:\n");
    printf("--------------------------------------------------\n");
    printf("🔵 A (signed char) [%d] antes de sumar:\t %c\n", A, A);
    printf("🔴 B (unsigned char) [%d] antes de sumar:\t %c\n", B, B);
    printf("--------------------------------------------------\n");

    A++; // Overflow en signed char
    B++; // Overflow en unsigned char

    printf("⚠️ ¡Overflow! ⚠️\n");
    printf("🔵 A (signed char) [%d] después de sumar:\t %c\n", A, A);
    printf("🔴 B (unsigned char) [%d] después de sumar:\t %c\n", B, B);
    printf("--------------------------------------------------\n");
    printf("📝 Explicación:\n");
    printf("🔵 Signed char: Al superar CHAR_MAX, vuelve al valor mínimo que es "
           "-128.\n");
    printf("🔴 Unsigned char: Al superar UCHAR_MAX, vuelve al valor minimo que "
           "es 0.\n");

    return 0;
}