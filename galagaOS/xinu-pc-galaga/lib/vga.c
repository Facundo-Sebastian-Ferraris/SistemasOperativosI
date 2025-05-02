#include <xinu.h>
#include <vga.h>
typedef unsigned short u16;

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

uint32 rgb16_to_rgb32(uint16 gba_color)
{
	// Extraer componentes (5 bits cada uno)
	uint32 r = (gba_color >> 10) & 0x1F; // R: bits 10-14
	uint32 g = (gba_color >> 5) & 0x1F;	 // G: bits 5-9
	uint32 b = gba_color & 0x1F;		 // B: bits 0-4

	// Escalar de 5 bits a 8 bits (sin redondeo)
	r = (r << 3) | (r >> 2); // r * 255 / 31 (pero más rápido)
	g = (g << 3) | (g >> 2); // g * 255 / 31
	b = (b << 3) | (b >> 2); // b * 255 / 31

	// Devolver en formato 0x00RRGGBB (RGB888)
	return (b << 16) | (g << 8) | r;
}

void setPixel(int x, int y, u16 color)
{
	if ((x >= 240) || (y >= 160))
		return;

	void *fb = (void *)(unsigned long)mbi->framebuffer_addr;
	uint32 *pixel = fb + mbi->framebuffer_pitch * y + 4 * x;
	//	 *pixel = color;
	*pixel = rgb16_to_rgb32(color);
}

void setPixelVGA(int x, int y, u16 color)
{
	if ((x >= VGA_WIDTH) || (y >= VGA_HEIGHT))
		return;

	void *fb = (void *)(unsigned long)mbi->framebuffer_addr;
	uint32 *pixel = fb + mbi->framebuffer_pitch * y + 4 * x;
	//	 *pixel = color;
	*pixel = rgb16_to_rgb32(color);
}

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

	uint32 color = 0x00FFFF00;
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
