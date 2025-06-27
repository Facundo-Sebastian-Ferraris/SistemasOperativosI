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
	
	unsigned char IMAGEN[270015];

	for(int i = 0; i < 15; i++){
		IMAGEN[i] = cabecera1[i];	
	}

	int cabSize = 15;
	int base = 269999-2;
	int inc = 0;
	for(int i = 0; i < 270000; i++){
		// 3 bytes per pixel
		// 1 2 3
		IMAGEN[cabSize + base + inc] = pixels1[i];
		inc = (inc + 1) % 3;
		if(i != 0 && i % 3 == 0){
			base -= 3;
		}
	}


	const char *name = "OS";

	void *ptr;

	//  Crear un segmento de memoria compartida 🏗️
	int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	// Configurar el tamaño del segmento de memoria a SIZE KB 📏
	ftruncate(shm_fd, 270015);

	// Mapear el segmento de memoria compartida con la direccion de espacio
	// del proceso 🗺️
	ptr = mmap(0, 270015, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED)
	{
		printf("El mapeo ha fallado\n");
		return -1;
	}
	memcpy(ptr,IMAGEN, 270015);

	return 0;
}
