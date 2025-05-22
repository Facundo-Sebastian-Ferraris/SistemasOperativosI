#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int largoArchivo(const char *pathing)
{
    printf("Path: %s\n", pathing);
    int largo = 0;

    int fd = open(pathing, O_RDONLY);
    if (fd == -1)
    {
        perror("No se encontro el archivo\n");
        exit(1);
    }

    char c;
    while (read(fd, &c, 1) == 1)
    { // Corregido: &c en lugar de c
        largo++;
    }

    close(fd);
    return largo;
}

char *guardarArchivo(const char *pathing, int size)
{ // Cambiado a char*
    int fd = open(pathing, O_RDONLY);
    if (fd == -1)
    {
        perror("No se encontro el archivo\n");
        exit(1);
    }

    char *buffer = malloc(size * sizeof(char));
    if (buffer == NULL)
    {
        perror("Error en malloc\n");
        exit(1);
    }

    if (read(fd, buffer, size) != size)
    {
        perror("Size Incorrecto\n");
        exit(1);
    }

    close(fd);
    return buffer;
}

void imprimirReverso(char *buffer, int size)
{
    for (int i = size - 1; i >= 0; i--)
    {
        write(STDOUT_FILENO, &buffer[i], 1);
    }
}

int main()
{
    const char *path = "./secreto.txt";
    int l = largoArchivo(path);
    char *buffer = guardarArchivo(path, l);
    imprimirReverso(buffer, l);

    free(buffer);
    return 0;
}