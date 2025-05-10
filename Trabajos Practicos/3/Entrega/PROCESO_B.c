#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>    /* For O_* constants */

int main()
{
    const int SIZE = 4096;
    const char *name = "OS";

    int shm_fd;
    void *ptr;
    int i;

    //  Abrir el segmento de memoria compartida 🔓
    shm_fd = shm_open(name, O_RDONLY, 0666);
    if (shm_fd == -1)
    {
        printf("Fallo en la lectura de memoria\n");
        exit(-1);
    }

    // Mapear el segmento de memoria compartida con la direccion de espacio
    // del proceso 🗺️
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED)
    {
        printf("El mapeo ha fallado\n");
        exit(-1);
    }

    // Leer desde la region de memoria compartida 📖
    printf("%s\n", (char *)ptr);

    //  remover el segemento de memoria compartida 🗑️
    if (shm_unlink(name) == -1)
    {
        printf("Error al remover %s\n", name);
        exit(-1);
    }

    return 0;
}