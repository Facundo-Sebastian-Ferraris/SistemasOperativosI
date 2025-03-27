#include <xinu.h>
#include <vga.h>
#include <colores.h>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
typedef struct
{
	unsigned int height;
	unsigned int width;
	unsigned int size;
	unsigned int pitch;
	unsigned char bpp;
	unsigned char ypp;
	unsigned char *buffer;
	unsigned char *device;
} vgaframebuffer_t;

vgaframebuffer_t vga2;

void pixeld(int x, int y, int color)
{
	if (x > vga2.width || y > vga2.height)
		return;
	int b = color >> 16, g = color >> 8 & 255, r = color & 255;
	vga2.device[(y * vga2.width + x) * vga2.ypp] = r;
	vga2.device[(y * vga2.width + x) * vga2.ypp + 1] = g;
	vga2.device[(y * vga2.width + x) * vga2.ypp + 2] = b;
}

void linea()
{
	pixeld(50, 50, 0xAFAFAFAF);
	while (1)
		;
}

void pixel(unsigned x, unsigned y, uint32 color)
{
	void *fb = (void *)(unsigned long)mbi->framebuffer_addr;
	uint32 *pixel = fb + mbi->framebuffer_pitch * y + 4 * x;
	*pixel = color;
}

void paint_screen()
{

	uint32 color = COLOR_AZUL;
	int i, j, x, y;
	open(VGA, NULL, 0);
	for (y = 0; y < VGA_HEIGHT; y++)
	{
		for (x = 0; x < VGA_WIDTH; x++)
		{
			pixel(x, y, color);
		}
		sleepms(1);
	}
	close(VGA);
}

void paint_screen_degrade(uint32 color)
{
	uint8_t r_base = GET_R(color);
	uint8_t g_base = GET_G(color);
	uint8_t b_base = GET_B(color);

	int i, j, x, y;
	open(VGA, NULL, 0);
	for (y = 0; y < VGA_HEIGHT; y++)
	{
		uint8_t r = (r_base * (VGA_HEIGHT - y)) / VGA_HEIGHT;
		uint8_t g = (g_base * (VGA_HEIGHT - y)) / VGA_HEIGHT;
		uint8_t b = (b_base * (VGA_HEIGHT - y)) / VGA_HEIGHT;
		for (x = 0; x < VGA_WIDTH; x++)
		{
			pixel(x, y, ARGB(255, r, g, b));
		}
		sleepms(1);
	}
	close(VGA);
}
