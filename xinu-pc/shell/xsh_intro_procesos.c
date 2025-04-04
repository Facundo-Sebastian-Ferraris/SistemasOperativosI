
#include <xinu.h>

void emit(char c);

xsh_intro_procesos(void)
{
	// creacion de los procesos
	pid32 proceso1 = create(emit, 1024, 20, "process 1", 1, '0'); // emitira un espacio con fondo rojo
	pid32 proceso2 = create(emit, 1024, 20, "process 2", 1, ' '); // emitira un espacio con fondo azul

	// ejecucion de los procesos
	resume(proceso1);
	resume(proceso2);
}

void emit(char c)
{
	while (1)
	{
		putc(CONSOLE, c);
	}
}