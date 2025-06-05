#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

// Estructura para pasar argumentos a los hilos
typedef struct
{
    int *numeros;
    int desde;
    int hasta;
} ThreadArgs;

int cantidadCaracteres_File(int fd)
{
    int r = 0;
    char dummy;
    while (read(fd, &dummy, 1))
    {
        r++;
    }
    lseek(fd, 0, SEEK_SET);
    return r;
}

int binToDec(char *bin)
{
    int r = 0;
    int is_negative = bin[0] == '1';
    if (is_negative)
    {
        char inverted[33];
        for (int i = 0; i < 32; i++)
        {
            inverted[i] = (bin[i] == '1') ? '0' : '1';
        }
        inverted[32] = '\0';
        for (int i = 0; i < 32; i++)
        {
            r = r * 2 + (inverted[i] - '0');
        }
        r += 1;
        r = -r;
    }
    else
    {
        for (int i = 0; i < 32; i++)
        {
            r = r * 2 + (bin[i] - '0');
        }
    }
    return r;
}

void binariosADecimal(char *bufferBinarios, int iteraciones, int *bufferDecimales)
{
    if (!bufferBinarios || !bufferDecimales)
        return;
    char *numero = bufferBinarios;
    char temp[33];
    for (int i = 0; i < iteraciones; i++)
    {
        strncpy(temp, numero, 32);
        temp[32] = '\0';
        bufferDecimales[i] = binToDec(temp);
        numero += 33;
    }
}

void imprimirNumeros(int *bufferNumeros, int largo)
{
    for (size_t i = 0; i < largo; i++)
    {
        printf("%d ", bufferNumeros[i]);
    }
    printf("\n");
}

void *bubbleSort(void *args)
{
    ThreadArgs *targs = (ThreadArgs *)args;
    int *numeros = targs->numeros;
    int desde = targs->desde;
    int hasta = targs->hasta;

    int cambio;
    for (size_t i = desde; i < hasta - 1; i++)
    {
        cambio = 0;
        for (size_t j = desde; j < hasta - 1 - (i - desde); j++)
        {
            if (numeros[j] > numeros[j + 1])
            {
                int temp = numeros[j];
                numeros[j] = numeros[j + 1];
                numeros[j + 1] = temp;
                cambio = 1;
            }
        }
        if (!cambio)
        {
            break;
        }
    }
    return NULL;
}

void merge(int *arr, int start, int mid, int end)
{
    int n1 = mid - start; // Tamaño de la primera mitad
    int n2 = end - mid;   // Tamaño de la segunda mitad
    int *left = malloc(n1 * sizeof(int));
    int *right = malloc(n2 * sizeof(int));
    if (!left || !right)
    {
        perror("Error: malloc falló en merge");
        exit(1);
    }

    // Copiar datos a los arreglos temporales
    for (int i = 0; i < n1; i++)
        left[i] = arr[start + i];
    for (int i = 0; i < n2; i++)
        right[i] = arr[mid + i];

    // Combinar los arreglos temporales
    int i = 0, j = 0, k = start;
    while (i < n1 && j < n2)
    {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }
    while (i < n1)
        arr[k++] = left[i++];
    while (j < n2)
        arr[k++] = right[j++];

    free(left);
    free(right);
}

int main()
{
    printf("\033[2J\033[H");
    // 1. Obtener el archivo
    const char *PATH = "./numersBinarios.txt";
    int fd = open(PATH, O_RDONLY);
    if (fd == -1)
    {
        perror("Error: fd no encontrado");
        exit(1);
    }

    // 2. Leer el archivo
    int file_charSize = cantidadCaracteres_File(fd);
    printf("Cantidad de caracteres ASCII: %d\n", file_charSize);
    char *bufferLectura = malloc(file_charSize + 1);
    if (!bufferLectura)
    {
        perror("Error: malloc falló para bufferLectura");
        close(fd);
        exit(1);
    }
    ssize_t bytesRead = read(fd, bufferLectura, file_charSize);
    if (bytesRead != file_charSize)
    {
        perror("Error: lectura incompleta");
        free(bufferLectura);
        close(fd);
        exit(1);
    }
    bufferLectura[bytesRead] = '\0';

    // 3. Convertir binarios a decimales
    int num_binaries = file_charSize / 33;
    if (file_charSize % 33 == 1)
        num_binaries--; // Ajustar por '\n' final
    int *bufferDecimales = malloc(num_binaries * sizeof(int));
    if (!bufferDecimales)
    {
        perror("Error: malloc falló para bufferDecimales");
        free(bufferLectura);
        close(fd);
        exit(1);
    }
    binariosADecimal(bufferLectura, num_binaries, bufferDecimales);
    printf("Antes de ordenar:\n");
    imprimirNumeros(bufferDecimales, num_binaries);

    // 4. Guardar decimales (ya hecho)

    // 5. Ordenar con dos hilos
    pthread_t threads[2];
    ThreadArgs args[2];
    int mid = num_binaries / 2;

    args[0] = (ThreadArgs){bufferDecimales, 0, mid};
    args[1] = (ThreadArgs){bufferDecimales, mid, num_binaries};
    if (pthread_create(&threads[0], NULL, bubbleSort, &args[0]) != 0)
    {
        perror("Error: fallo al crear hilo 0");
        free(bufferLectura);
        free(bufferDecimales);
        close(fd);
        exit(1);
    }
    if (pthread_create(&threads[1], NULL, bubbleSort, &args[1]) != 0)
    {
        perror("Error: fallo al crear hilo 1");
        free(bufferLectura);
        free(bufferDecimales);
        close(fd);
        exit(1);
    }
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    // Combinar las mitades ordenadas
    merge(bufferDecimales, 0, mid, num_binaries);

    // 6. Imprimir el arreglo ordenado
    printf("Después de ordenar:\n");
    imprimirNumeros(bufferDecimales, num_binaries);

    // Liberar recursos
    free(bufferLectura);
    free(bufferDecimales);
    close(fd);
    return 0;
}