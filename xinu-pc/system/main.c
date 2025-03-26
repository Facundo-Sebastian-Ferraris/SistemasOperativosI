/*  main.c  - main */

#include <xinu.h>


extern paint_screen();
extern print_text_on_vga(unsigned int x, unsigned int y, const char * t);

process	main(void)
{






	paint_screen();
	int renglon=1;
	print_text_on_vga(10, 10 * renglon++, "     *                                                            *");
	print_text_on_vga(10, 10 * renglon++, "                             aaaaaaaaaaaaaaaa               *");
	print_text_on_vga(10, 10 * renglon++, "                         aaaaaaaaaaaaaaaaaaaaaaaa");
	print_text_on_vga(10, 10 * renglon++, "                      aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	print_text_on_vga(10, 10 * renglon++, "                    aaaaaaaaaaaaaaaaa           aaaaaa");
	print_text_on_vga(10, 10 * renglon++, "                  aaaaaaaaaaaaaaaa                  aaaa");
	print_text_on_vga(10, 10 * renglon++, "                 aaaaaaaaaaaaa aa                      aa");
	print_text_on_vga(10, 10 * renglon++, "*               aaaaaaaa      aa                         a");
	print_text_on_vga(10, 10 * renglon++, "                aaaaaaa aa aaaa");
	print_text_on_vga(10, 10 * renglon++, "          *    aaaaaaaaa     aaa");
	print_text_on_vga(10, 10 * renglon++, "               aaaaaaaaaaa aaaaaaa                               *");
	print_text_on_vga(10, 10 * renglon++, "               aaaaaaa    aaaaaaaaaa");
	print_text_on_vga(10, 10 * renglon++, "               aaaaaa a aaaaaa aaaaaa");
	print_text_on_vga(10, 10 * renglon++, "                aaaaaaa  aaaaaaa");
	print_text_on_vga(10, 10 * renglon++, "                aaaaaaaa                                 a");
	print_text_on_vga(10, 10 * renglon++, "                 aaaaaaaaaa                            aa");
	print_text_on_vga(10, 10 * renglon++, "                  aaaaaaaaaaaaaaaa                  aaaa");
	print_text_on_vga(10, 10 * renglon++, "                    aaaaaaaaaaaaaaaaa           aaaaaa        *");
	print_text_on_vga(10, 10 * renglon++, "      *               aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	print_text_on_vga(10, 10 * renglon++, "                         aaaaaaaaaaaaaaaaaaaaaaaa");
	print_text_on_vga(10, 10 * renglon++, "                      *      aaaaaaaaaaaaaaaa");
	print_text_on_vga(10, 10 * renglon++, "Hola MUNDOOOO!!!");
	print_text_on_vga(10, 10 * renglon++, "Facundo-Sebastian-Ferraris");

	recvclr();
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */

	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
    
}
