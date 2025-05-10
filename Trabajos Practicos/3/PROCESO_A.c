#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>    /* For O_* constants */
#include <string.h>

void *p_msg(void *ptr);

int main()
{

    // PROCESO DE EXTRACCION DE TEXTO EN .TXT
    char *PATH = "ubicacion/rancia/carpeta/mmap06.txt";
    int fd = open(PATH, O_RDONLY); // 📂 Abrir
    char buffer[4096];             // 🪣 Buffer estático

    ssize_t bytes = read(fd, buffer, sizeof(buffer)); // 📖 Leer
    buffer[bytes] = '\0';                             // 🏁 Terminar cadena

    close(fd);
    // PROCESO DE CREACION DE REGION DE MEMORIA
    const int SIZE = 4096;
    const char
        *name = "OS",
        *mess0 = "Studying ",
        *mess1 = "Operating Systems ";

    int shm_fd;
    void *ptr;

    //  Crear un segmento de memoria compartida 🏗️
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    // Configurar el tamaño del segmento de memoria a SIZE KB 📏
    ftruncate(shm_fd, SIZE);

    // Mapear el segmento de memoria compartida con la direccion de espacio
    // del proceso 🗺️
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED)
    {
        printf("El mapeo ha fallado\n");
        return -1;
    }

    // Escribir en la region de memoria compartida ✍️
    sprintf(ptr, "%s\n", buffer);
}
