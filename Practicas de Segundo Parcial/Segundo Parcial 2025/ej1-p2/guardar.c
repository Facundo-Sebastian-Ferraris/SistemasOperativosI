#include "imagen1.h"
#include "imagen2.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <string.h>

int main(){
	const int cabecera_Size = sizeof(cabecera1)-1;
	const int pixel_Size = sizeof(pixels1);
	const int total_Size = 270015;

	const char *name = "OS";

	int shm_fd;
	void *ptr;
	int i;

	shm_fd = shm_open(name, O_RDONLY, 0666);
	if (shm_fd == -1){
		printf("FALLO RDMEM\n");
		exit(-1);
	}

	ptr = mmap(0, total_Size, PROT_READ, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED){
		printf("FALLO MAP\n");
		exit(-1);
	}

	if(shm_unlink(name) == -1){
		printf("Error al remover %s\n", name);
		exit(-1);
	}

	printf("ingrese nombre del archivo\n");
	system("/bin/stty raw");
	char nombre[100];
	nombre[0] = 'a';
	int largo = 0;
	char c = 'a';
	while(c != '0' && largo < 100){
		c = getchar();

		if (c != '0'){
			nombre[largo] = c;
		} else {
			nombre[largo] = '\0';
		}	
		largo++;
	}
	system("/bin/stty sane erase ^H");

	int f = open(nombre, O_RDWR|O_CREAT, 0666);
	write(f, ptr, total_Size);
	close(f);
	return 0;
}
