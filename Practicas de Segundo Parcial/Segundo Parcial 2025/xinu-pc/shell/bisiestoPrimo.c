#include <xinu.h>


int raizCuadrada(int n){
	int i;
	while (i*i<n){
		i++;
	}
	return i;
}

int esPrimo(int n){
	int r = n % 2 != 0 && n % 3 != 0;
	int nr = raizCuadrada(n);
	int i = 5;
	while (r && i <= nr){
		r = n % i != 0;
		i+=2;
	}

	if(r){
		printf("es Primo!");
	} else {
		
		printf("NO es Primo!");
	}
}

void esBisiesto(int n){
	if ((n % 4 == 0) && ((n % 100 != 0) || (n % 400 == 0))){
		printf("es bisiesto!");
	} else {
		printf("NO es bisiesto!");
	}
}

void bisiPrimo(){
	//variables
	

	char buf[10];
	printf("INGRESE UN NRO: ");
	read(CONSOLE, buf, 10);
	int 	i = atoi(buf);
	printf ("el numero ingresado entero es %d \n", i);

	pid32 pid_Primo = create(esPrimo, 8*1024, 20, "Primo", 1, i);
	pid32 pid_Bisiesto = create(esBisiesto, 8*1024, 20, "Bisiesto", 1, i);

	resume (pid_Primo);
	resume (pid_Bisiesto);
}
