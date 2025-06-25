/* source: https://forum.osdev.org/viewtopic.php?t=10247 */

/* kbdhandler.c - kbdhandler */

#include <xinu.h>
#include <keyboard.h>

char BUFFER[10];
int inicio = 0;
int fin = 0;

int esVacio()
{
	return inicio == fin && BUFFER[inicio] == NULL;
}

int estaLLeno()
{
	return inicio == fin && BUFFER[inicio] != NULL;
}

int poner(char a)
{
	int r = !estaLLeno();
	if (r)
	{
		BUFFER[inicio];
		inicio = (inicio + 1) % 10;
	}
	return r;
}

char sacar(char a)
{
	char r = NULL;
	if (!esVacio())
	{
		r = BUFFER[fin];
		BUFFER[fin] = NULL;
		fin = (fin + 1) % 10;
	}
	return r;
}

unsigned char get_scancode()
{
	unsigned char inputdata;
	inputdata = inportb(KEYBOARD_DATAREG);
	return inputdata;
}

/*------------------------------------------------------------------------
 *  kbdhandler  -  Handle an interrupt for the keyboard device
 *------------------------------------------------------------------------
 */
void kbdhandler(void)
{
	char t[sizeof("ENTRADA DE TECLADO  kbd: 0xaa     ")];
	unsigned char scancode;
	unsigned int shift_key = 0;
	int i = 10;

	scancode = get_scancode();
	sprintf(t, "ENTRADA DE TECLADito kbd: 0x%x    ", scancode);
	print_text_on_vga(10, 300, t);

	if (scancode == 0x2A)
	{
		shift_key = 1;
	}
	else if (scancode & 0xAA)
	{
		shift_key = 0;
	}
	else
	{
		if (scancode & 0x80)
		{
			int shiftaltctrl = 1;
		}
		else
		{
		}
	}
}
