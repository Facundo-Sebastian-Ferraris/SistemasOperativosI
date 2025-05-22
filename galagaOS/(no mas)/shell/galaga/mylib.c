#include <xinu.h>
#include <vga.h>

// #include <conf.h>

typedef unsigned short u16;
// u16 *videoBuffer = (u16 *)0x6000000;
// #define scanlinecounter *(volatile u16 *)0x4000006
extern void setPixel(int x, int y, u16 color);
extern void setPixelVGA(int x, int y, u16 color);

void drawRect(int x, int y, int width, int height, u16 color);
void drawHollowRect(int x, int y, int width, int height, u16 color);
void drawImage3(int x, int y, int width, int height, const u16 *image);
void drawImage3ToVGA(int x, int y, int size_x, int size_y, const u16 *image);
void drawImage3Scaler(int x, int y, int size_x, int size_y, int scale_x, int scale_y, const u16 *image);
float fminf(float a, float b);
// void delay();
void waitForVBlank();

/*
void setPixel(int x, int y, u16 color) {
	videoBuffer[x + 240 * y] = color;
}
*/

void drawRect(int x, int y, int width, int height, u16 color)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			setPixel(x + i, y + j, color);
		}
	}
}

void drawHollowRect(int x, int y, int width, int height, u16 color)
{
	for (int i = 0; i < width; i++)
	{
		setPixelVGA(x + i, y, color);
		setPixelVGA(x + i, y + (height - 1), color);
	}
	for (int j = 0; j < height; j++)
	{
		setPixelVGA(x, y + j, color);
		setPixelVGA(x + (width - 1), y + j, color);
	}
}

void drawImage3(int x, int y, int width, int height, const u16 *image)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			u16 color = *(image + i + (width * j));
			setPixel(x + i, y + j, color);
		}
	}
}
#define GBA_WIDTH 240
#define GBA_HEIGHT 160

void drawImage3FULL(int x, int y, const u16 *image)
{
	int scale_x = VGA_WIDTH / GBA_WIDTH;
	int scale_y = VGA_HEIGHT / GBA_HEIGHT;

	for (int y_gba = 0; y_gba < GBA_HEIGHT; y_gba++)
	{
		for (int x_gba = 0; x_gba < GBA_WIDTH; x_gba++)
		{
			u16 color = image[y_gba * GBA_WIDTH + x_gba];

			// Escalar el píxel (x_gba, y_gba) en VGA
			for (int dy = 0; dy < scale_y; dy++)
			{
				for (int dx = 0; dx < scale_x; dx++)
				{
					setPixelVGA(
						x + (x_gba * scale_x) + dx,
						y + (y_gba * scale_y) + dy,
						color);
				}
			}
		}
	}
}

void drawImage3ToVGA(int x, int y, int size_x, int size_y, const u16 *image)
{
	int scale_x = VGA_WIDTH / size_x;
	int scale_y = VGA_HEIGHT / size_y;

	for (int y_gba = 0; y_gba < GBA_HEIGHT; y_gba++)
	{
		for (int x_gba = 0; x_gba < GBA_WIDTH; x_gba++)
		{
			u16 color = image[y_gba * GBA_WIDTH + x_gba];

			// Escalar el píxel (x_gba, y_gba) en VGA
			for (int dy = 0; dy < scale_y; dy++)
			{
				for (int dx = 0; dx < scale_x; dx++)
				{
					setPixelVGA(
						x + (x_gba * scale_x) + dx,
						y + (y_gba * scale_y) + dy,
						color);
				}
			}
		}
	}
}

void drawImage3Scaler(int x, int y, int size_x, int size_y, int scale_x, int scale_y, const u16 *image)
{
	for (int y_gba = 0; y_gba < size_y; y_gba++)
	{
		for (int x_gba = 0; x_gba < size_x; x_gba++)
		{
			u16 color = image[y_gba * size_x + x_gba];

			// Escalar el píxel (x_gba, y_gba) en VGA
			for (int dy = 0; dy < scale_y; dy++)
			{
				for (int dx = 0; dx < scale_x; dx++)
				{
					setPixelVGA(
						x + (x_gba * scale_x) + dx,
						y + (y_gba * scale_y) + dy,
						color);
				}
			}
		}
	}
}

float fminf(float a, float b)
{
	if (a > b)
	{
		return a;
	}
	return b;
}

void delay_galaga()
{
	for (int a = 0; a < 10; a++)
	{
		a++;
	}
}

void waitForVBlank()
{
	sleepms(20);
	// while(scanlinecounter > 160);
	// while(scanlinecounter < 160);
}
