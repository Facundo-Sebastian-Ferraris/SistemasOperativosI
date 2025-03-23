#include <stdio.h>

int main() {
    printf("📏 Tamaños de los tipos básicos en este sistema:\n");
    printf("--------------------------------------------\n");
    printf("🔤 char:\t%zu bytes\n", sizeof(char));
    printf("🔢 short:\t%zu bytes\n", sizeof(short));
    printf("🔢 int:\t\t%zu bytes\n", sizeof(int));
    printf("🔢 long:\t%zu bytes\n", sizeof(long));
    printf("🔢 long long:\t%zu bytes\n", sizeof(long long));
    printf("🎈 float:\t%zu bytes\n", sizeof(float));
    printf("🎈🎈 double:\t%zu bytes\n", sizeof(double));
    printf("🎈🎈🎈 long double:\t%zu bytes\n", sizeof(long double));
    printf("--------------------------------------------\n");

    return 0;
}