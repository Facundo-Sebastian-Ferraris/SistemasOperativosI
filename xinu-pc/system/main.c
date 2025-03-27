/*  main.c  - main */

#include <xinu.h>
#include <colores.h>

extern paint_screen_degrade(uint32 color);
extern print_text_on_vga2(unsigned int x, unsigned int y, const char *t);

process main(void)
{

	paint_screen_degrade(COLOR_AZUL);

	printWallpaper();
	recvclr();
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */

	while (TRUE)
	{
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
}

void printWallpaper()
{
	int renglon = 1;
	print_text_on_vga2(10, 10 * renglon++, "     *                                                            *");
	print_text_on_vga2(10, 10 * renglon++, "                             aaaaaaaaaaaaaaaa               *");
	print_text_on_vga2(10, 10 * renglon++, "                         aaaaaaaaaaaaaaaaaaaaaaaa");
	print_text_on_vga2(10, 10 * renglon++, "                      aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	print_text_on_vga2(10, 10 * renglon++, "                    aaaaaaaaaaaaaaaaa           aaaaaa");
	print_text_on_vga2(10, 10 * renglon++, "                  aaaaaaaaaaaaaaaa                  aaaa");
	print_text_on_vga2(10, 10 * renglon++, "                 aaaaaaaaaaaaa aa                      aa");
	print_text_on_vga2(10, 10 * renglon++, "*               aaaaaaaa      aa                         a");
	print_text_on_vga2(10, 10 * renglon++, "                aaaaaaa aa aaaa");
	print_text_on_vga2(10, 10 * renglon++, "          *    aaaaaaaaa     aaa");
	print_text_on_vga2(10, 10 * renglon++, "               aaaaaaaaaaa aaaaaaa                               *");
	print_text_on_vga2(10, 10 * renglon++, "               aaaaaaa    aaaaaaaaaa");
	print_text_on_vga2(10, 10 * renglon++, "               aaaaaa a aaaaaa aaaaaa");
	print_text_on_vga2(10, 10 * renglon++, "                aaaaaaa  aaaaaaa");
	print_text_on_vga2(10, 10 * renglon++, "                aaaaaaaa                                 a");
	print_text_on_vga2(10, 10 * renglon++, "                 aaaaaaaaaa                            aa");
	print_text_on_vga2(10, 10 * renglon++, "                  aaaaaaaaaaaaaaaa                  aaaa");
	print_text_on_vga2(10, 10 * renglon++, "                    aaaaaaaaaaaaaaaaa           aaaaaa        *");
	print_text_on_vga2(10, 10 * renglon++, "      *               aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	print_text_on_vga2(10, 10 * renglon++, "                         aaaaaaaaaaaaaaaaaaaaaaaa");
	print_text_on_vga2(10, 10 * renglon++, "                      *      aaaaaaaaaaaaaaaa");
	renglon = renglon + (41);
	print_text_on_vga2(10, 10 * renglon++, "          |\\___/|");
	print_text_on_vga2(10, 10 * renglon++, "          )     (             .              '");
	print_text_on_vga2(10, 10 * renglon++, "         =\\     /=");
	print_text_on_vga2(10, 10 * renglon++, "           )===(       *");
	print_text_on_vga2(10, 10 * renglon++, "          /     \\");
	print_text_on_vga2(10, 10 * renglon++, "          |     |");
	print_text_on_vga2(10, 10 * renglon++, "         /       \\");
	print_text_on_vga2(10, 10 * renglon++, "         \\       /");
	print_text_on_vga2(10, 10 * renglon++, "  _/\\_/\\_/\\__  _/_/\\_/\\_/\\_/\\_/\\_/\\_/\\_/\\_/\\_");
	print_text_on_vga2(10, 10 * renglon++, "  |  |  |  |( (  |  |  |  |  |  |  |  |  |  |");
	print_text_on_vga2(10, 10 * renglon++, "  |  |  |  | ) ) |  |  |  |  |  |  |  |  |  |");
	print_text_on_vga2(10, 10 * renglon++, "  |  |  |  |(_(  |  |  |  |  |  |  |  |  |  |");
	print_text_on_vga2(10, 10 * renglon++, "  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |");
	print_text_on_vga2(10, 10 * renglon--, "  jgs|  |  |  |  |  |  |  |  |  |  |  |  |  |");
	print_text_on_vga2(800, 10 * renglon--, "XINU de FACUNDO FERRARIS [FAI-3820]");
	print_text_on_vga2(800, 10 * renglon, "SISTEMAS OPERATIVOS I");
}