#include <xinu.h>;

//mensajes globales
int sintonia=0;
sid32 MUTEX;

int sint;
const char *mensajes[] = {
	"Mensaje de la primer radio\n",
	"Segunda radio transmitiendo\n",
	"Tercera Emisora enviando\n"
};

void emisor(int n, int retardo, pid32 radioEmisora){
	int indice;
	while(1){
		for (indice = 0; mensajes[n-1][indice] != '\0'; indice++){
			int msg = (n<<8)| mensajes[n-1][indice];
			if(sintonia == n){
				send(radioEmisora,msg);
			}
			sleepms(retardo);
		}

	}
}

void radio_play(){
	//decodificar
	while(1){
		int msg = receive();
		int emisora = msg >> 8;
		char car = (char) (msg & 0xFF);
		wait(MUTEX);
		kprintf("%c", car);
		signal(MUTEX);

	}
}

void radio_control(){

	MUTEX = semcreate(1);
	pid32 pid_radio_play = create(radio_play, 8*1024, 20, "radioP" , 0);
	pid32 pid_emisora1 = create(emisor, 8*1024, 20, "e1", 3, 1, 600, pid_radio_play);
	pid32 pid_emisora2 = create(emisor, 8*1024, 20, "e2", 3, 2, 500, pid_radio_play);
	pid32 pid_emisora3 = create(emisor, 8*1024, 20, "e3", 3, 3, 888, pid_radio_play);

	resume(pid_radio_play);
	resume(pid_emisora1);
	resume(pid_emisora2);
	resume(pid_emisora3);
	char c;
	control(CONSOLE, TC_MODER, 0, 0);
	while(1){
		c = getc(stdin);
		wait(MUTEX);
		if(c == 'q'){
			break;
		}

		if (c == '1'){
			sintonia = 1;
			kprintf("\n1: ");
		}


		if (c == '2'){
			sintonia = 2;
			kprintf("\n2: ");
		}


		if (c == '3'){
			sintonia = 3;
			kprintf("\n3: ");
		}
		signal(MUTEX);
	}
	control(CONSOLE, TC_MODEC, 0, 0);

	kill(pid_emisora1);
	kill(pid_emisora2);
	kill(pid_emisora3);
}
