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

	int height = 300;
	int width = 300;
	int saltoGrande = 897;
	int piso = 0;
	int inc = 0; 	
	for (int i = 0; i < 270000; i++){
		IMAGEN[15 + saltoGrande + inc] = pixels1[i];
		inc = (inc + 1) % 3;
		if(inc == 0){
			saltoGrande -= 3;
		}
		if(saltoGrande<piso){
			piso += 900;
			saltoGrande = piso + 897;
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
