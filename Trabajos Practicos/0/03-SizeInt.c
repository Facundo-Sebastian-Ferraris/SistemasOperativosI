#include <stdio.h>

int main() {
    printf("\"PC con arquitectura de 64 bits 🖥️ \"\n\tBits en un int: %zu "
           "✨\n\n ",
           sizeof(int) * 8);
    printf("Se utilizo %%zu que es un especificador de formato para poder \n "
           "leer el tipo de dato size_t.\n"
           "(esto es porque el metodo sizeOf() retorna ese mismo tipo)\n");
    return 0;
}
