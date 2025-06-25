// productor.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "imagen.h"

int main() {
    unsigned char imagen[SIZE]; // Usar SIZE desde imagen.h
    // Copiar cabecera
    for (int i = 0; i < sizeof(cabecera); i++) {
        imagen[i] = cabecera[i];
    }
    // Copiar pixeles
    for (int i = 0; i < sizeof(pixeles); i++) {
        imagen[i + sizeof(cabecera)] = pixeles[i];
    }

    printf("Imagen fusionada exitosamente\n");

    const char *name = "OS";
    int shm_fd;
    void *ptr;

    // Crear segmento de memoria compartida
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        return -1;
    }

    // Configurar tamaño
    if (ftruncate(shm_fd, SIZE) == -1) {
        perror("ftruncate");
        return -1;
    }

    // Mapear segmento
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        return -1;
    }

    // Copiar datos binarios a la memoria compartida
    memcpy(ptr, imagen, SIZE);

    // Cerrar descriptor (no elimina la memoria compartida)
    close(shm_fd);

    return 0;
}
