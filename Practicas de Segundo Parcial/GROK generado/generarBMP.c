// consumidor.c
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "imagen.h"

int main() {
    const char *name = "OS";
    int shm_fd;
    void *ptr;

    // Abrir segmento de memoria compartida
    shm_fd = shm_open(name, O_RDONLY, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        return -1;
    }

    // Mapear segmento
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        return -1;
    }

    // Abrir archivo en modo binario
    FILE *f = fopen("imagen.bmp", "wb"); // Cambiar a .bmp para claridad
    if (f == NULL) {
        perror("fopen");
        return -1;
    }

    // Escribir datos al archivo
    if (fwrite(ptr, 1, SIZE, f) != SIZE) {
        perror("fwrite");
        fclose(f);
        return -1;
    }

    fclose(f);
    close(shm_fd);

    // Eliminar segmento de memoria compartida
    if (shm_unlink(name) == -1) {
        perror("shm_unlink");
        return -1;
    }

    printf("Imagen BMP creada exitosamente\n");
    return 0;
}
