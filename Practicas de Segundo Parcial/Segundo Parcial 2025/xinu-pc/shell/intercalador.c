#include <xinu.h>

pid32 hilo1;
pid32 hilo2;
sid32 waiter[3];
char *mensajes1[] = {
	"Hl ud!",
	"oamno"
};

char res[11];
int index;
void intercalador1(int indice, int sem1, int sem2){
	int j = 0;
	while(mensajes1[indice][j] != '\0'){
		wait(waiter[sem1]);
		res[index] = mensajes1[indice][j];
		printf("%c", res[index]);

		j++;
		index++;
		signal(waiter[sem2]);

	}

	signal(waiter[2]);
}

void intercalador(){
	hilo1 = create(intercalador1, 8*1024, 20, "h1", 3,0,0,1);
	hilo2 = create(intercalador1, 8*1024, 20, "h1", 3,1,1,0);
	
	waiter[0] = semcreate(1);
	waiter[1] = semcreate(0);
	resume(hilo1);
	resume(hilo2);
	
	wait(waiter[2]);
	wait(waiter[2]);
}
