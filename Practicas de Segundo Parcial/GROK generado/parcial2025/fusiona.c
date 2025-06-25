#include "imagen1.h"
#include "imagen2.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <string.h>

int main()
{
	// en image1.h e imagen2.h están los arreglos de las imágenes
	// los arreglos son de tipo: unsigned char
	const int cabeceraSIZE = sizeof(cabecera1)-1;
	printf("%d\n",cabeceraSIZE);
	const int totalSIZE = cabeceraSIZE + 2 * sizeof(pixels1)-2;
	unsigned char IMAGEN[totalSIZE];	

	//unsigned char  fus[270015];

	int i;

	for (i=0; i<cabeceraSIZE; i++)
		IMAGEN[i] = cabecera1[i];

        int j = 0;
	for (i=sizeof(pixels1); i>=0; i--) {
		IMAGEN[cabeceraSIZE+j] = pixels1[i];
		i--;
		j++;
		IMAGEN[cabeceraSIZE+j] = pixels2[i];
		j++;
	}
	// cabecera1[] tiene 15 bytes que son la cabecera de la imagen

	// pixels1[4]  tiene el pixel 4 de la imagen 1
	// pixels1[5]  tiene el pixel 5 de la imagen 1

	// pixels2[10]  tiene el pixel 10 de la imagen 2
	const char
		*name = "imagen";

	int shm_fd;
	void *ptr;

	//  Crear un segmento de memoria compartida 🏗️
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	// Configurar el tamaño del segmento de memoria a totalSIZE KB 📏
	ftruncate(shm_fd, totalSIZE);

	// Mapear el segmento de memoria compartida con la direccion de espacio
	// del proceso 🗺️
	ptr = mmap(0, totalSIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED)
	{
		printf("El mapeo ha fallado\n");
		return -1;
	}

	// Escribir en la region de memoria compartida ✍️
	memcpy(ptr,  IMAGEN,  totalSIZE);

}


