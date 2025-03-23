#include <stdio.h>

int main() {
    char a = 'M';
    printf("a = %zu \n", a);
    printf("La letra %c \n", a);
    return 0;
}

// detalles a leer
// donde `%zu` es un especificador de formato para poder leer el tipo de dato
// size_t (esto es porque el metodo `sizeOf()` retorna ese mismo tipo)