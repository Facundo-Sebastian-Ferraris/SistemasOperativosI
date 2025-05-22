#include <xinu.h>
#include "titlescreen.h"
#include "playerImage.h"
#include "enemy.h"
#include "boss.h"
#include "gameover.h"
#include "shoot.h"

extern paint_screen();
extern print_text_on_vga(unsigned int x, unsigned int y, const char *t);

extern unsigned char tecla_actual;
typedef unsigned short u16;
#define RGB(r, g, b) (r | (g << 5) | (b << 10))
// #define REG_DISPCNT *(u16 *)0x4000000
#define extern videoBuffer
#define MODE3 3
#define BG2_ENABLE (1 << 10)
#define WHITE RGB(31, 31, 31)
#define BLACK RGB(0, 0, 0)

// MENSAJES codigo
#define MSG_POINT 1
#define MSG_LIVES 2
#define MSG_GAMEOVER 3
#define MSG_OK 4

/*
#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)
#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)
*/
// #define BUTTONS *(volatile unsigned int *)0x4000130

#define BUTTON_A 0x24
#define BUTTON_B 0x25
#define BUTTON_SELECT 0x03
#define BUTTON_START 0x2c
#define BUTTON_RIGHT 0x1f
#define BUTTON_LEFT 0x1e
#define BUTTON_UP 'w'
#define BUTTON_DOWN 's'
#define BUTTON_R '1'
#define BUTTON_L '2'
#define KEY_DOWN_NOW(key) (tecla_actual == key)

// variable definitions
#define playerspeed 2
#define enemyspeed 1
#define fastXSpeed 3
#define fastYSpeed 2

void setPixel(int x, int y, u16 color);
void drawRect(int x, int y, int width, int height, u16 color);
void drawHollowRect(int x, int y, int width, int height, u16 color);
void drawImage3(int x, int y, int width, int height, const u16 *image);
void delay_galaga();
void waitForVBlank();

// helpers
void initialize();
void drawEnemies();
void endGame();
int collision(u16 enemyX, u16 enemyY, u16 enemyWidth, u16 enemyHeight, u16 playerX, u16 playerY);

// objects
struct Players
{
	volatile u16 playerX;
	volatile u16 playerY;
};
struct Enemy
{
	volatile u16 enemyX;
	volatile u16 enemyY;
};
struct FastEnemy
{
	volatile u16 fastX;
	volatile u16 fastY;
};
int y_Cartel = VGA_HEIGHT - 40;
int shoots[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int curr_shot = 0;
#define N_SHOOTS 10

// PROCESOS A CREAR
pid32 galagaGame;
void gameGalaga();
pid32 vidasYPuntos;
pid32 control3;
void controlador();
void puntosYVidas();

sid32 semaforoFinalizarPrograma;

int galaga(void)
{
	semaforoFinalizarPrograma = semcreate(0);
	kprintf("\033[2J\033[HCreando proceso control3\n");
	control3 = create(controlador, 8 * 1024, 20, "Control", 0);
	resume(control3);
	wait(semaforoFinalizarPrograma);
	return 0;
}

void controlador()
{
	print_text_on_vga(10, y_Cartel, "                            ");
	print_text_on_vga(10, y_Cartel + 20, "                            ");
	kprintf("proceso 3 creado\n creando proceso Juego y sistema de vidas y puntos\n");
	galagaGame = create(gameGalaga, 8 * 1024, 20, "Galaga", 0);
	vidasYPuntos = create(puntosYVidas, 8 * 1024, 20, "PuntosYVidas", 0);

	resume(galagaGame);
	resume(vidasYPuntos);
	receive();

	kill(galagaGame);
	kill(vidasYPuntos);
	endGame();
	signal(semaforoFinalizarPrograma);
}

void puntosYVidas()
{
	int vidas = 5;
	int puntaje = 0;
	int colision;

	print_text_on_vga(10, y_Cartel, "Vidas: ");
	print_text_on_vga(10, y_Cartel + 20, "Puntaje: ");
	int buffer1[10];
	int buffer2[10];
	sprintf(buffer1, "%d", (vidas - 1));
	sprintf(buffer2, "%d", puntaje);
	print_text_on_vga(100, y_Cartel, buffer1);
	print_text_on_vga(100, y_Cartel + 20, buffer2);
	while (1)
	{
		colision = receive();
		switch (colision)
		{
		case MSG_POINT:
			puntaje += 100;
			sprintf(buffer2, "%d", puntaje);
			print_text_on_vga(100, y_Cartel + 20, buffer2);
			break;
		case MSG_LIVES:
			vidas--;
			sprintf(buffer1, "%d", (vidas - 1));
			print_text_on_vga(100, y_Cartel, buffer1);
			if (vidas == 0)
			{
				send(control3, MSG_GAMEOVER);
			}

			break;
		default:
			break;
		}

		send(galagaGame, MSG_OK);
	}
};

void gameGalaga()
{
	// easy enemy wave set setup
	struct Enemy easyEnemies[9];
	for (int a = 0; a < 9; a++)
	{
		easyEnemies[a].enemyX = (28 * a);
		easyEnemies[a].enemyY = 0;
	}
	easyEnemies[1].enemyX = 240;
	easyEnemies[4].enemyX = 240;
	easyEnemies[8].enemyX = 240;
	// difficult enemies setup
	struct Enemy hardEnemies[9];
	for (int a = 0; a < 9; a++)
	{
		hardEnemies[a].enemyX = (28 * a);
		hardEnemies[a].enemyY = 160;
	}
	hardEnemies[3].enemyX = 240;
	hardEnemies[6].enemyX = 240;
	// player setup
	struct Players player;
	player.playerX = 120;
	player.playerY = 136;
	// fast enemy "boss" setup
	struct FastEnemy fast;
	fast.fastX = 0;
	fast.fastY = 30;

	int shootOrigin = 136 * 240 + 9;
	// REG_DISPCNT = MODE3 | BG2_ENABLE;
	// initalize title screen
	print_text_on_vga(10, 20, "GALAGA ");
	drawImage3(0, 0, 240, 160, titlescreen);
	while (1)
	{
		if (KEY_DOWN_NOW(BUTTON_START))
		{
			break;
		}
	}
	// start black screen for drawing
	for (int i = 0; i < 240; i++)
	{
		for (int j = 0; j < 160; j++)
		{
			setPixel(i, j, BLACK);
		}
	}
	while (1)
	{
		// go back to title screen if select button is pressed
		if (KEY_DOWN_NOW(BUTTON_SELECT))
		{
			// initialize();
			galaga();
		}
		// player shots
		if (KEY_DOWN_NOW(BUTTON_A))
		{
			if (shoots[curr_shot] == 0)
			{
				shoots[curr_shot] = player.playerX + shootOrigin; /* 24 widht player */
				curr_shot = (curr_shot + 1) % N_SHOOTS;
			};
		}
		if (KEY_DOWN_NOW(BUTTON_B))
		{
			send(control3, MSG_GAMEOVER);
		}
		// player movement input
		if (KEY_DOWN_NOW(BUTTON_LEFT) && (player.playerX > 0))
		{
			player.playerX -= playerspeed;
		}
		if (KEY_DOWN_NOW(BUTTON_RIGHT) && (player.playerX <= 216))
		{
			player.playerX += playerspeed;
		}
		if (KEY_DOWN_NOW(BUTTON_UP) && (player.playerY > 25))
		{
			player.playerY -= playerspeed;
		}
		if (KEY_DOWN_NOW(BUTTON_DOWN) && (player.playerY <= 136))
		{
			player.playerY += playerspeed;
		}
		waitForVBlank();
		sleepms(10);
		// draw player
		drawImage3(player.playerX, player.playerY, 24, 24, playerImage);
		drawHollowRect(player.playerX - 1, player.playerY - 1, 26, 26, BLACK);
		drawHollowRect(player.playerX - 2, player.playerY - 2, 28, 28, BLACK);
		// draw easy enemies with downward movement
		for (int a = 0; a < 9; a++)
		{
			easyEnemies[a].enemyY += enemyspeed;
			drawImage3(easyEnemies[a].enemyX, easyEnemies[a].enemyY, 20, 20, enemy);
			if (collision(easyEnemies[a].enemyX, easyEnemies[a].enemyY, 20, 20, player.playerX, player.playerY))
			{
				drawRect(easyEnemies[a].enemyX, easyEnemies[a].enemyY, 20, 20, BLACK);
				easyEnemies[a].enemyY = 0;
				send(control3, MSG_LIVES);
				receive();
			}
			if (easyEnemies[a].enemyY >= 160)
			{
				easyEnemies[a].enemyY = 0;
			}
		}

		// draw shots
		for (int i = 0; i < N_SHOOTS; i++)
		{
			if (shoots[i] != 0)
			{
				drawRect((shoots[i] % 240), (shoots[i] / 240) + 4, 5, 5, BLACK);
				drawImage3((shoots[i] % 240), (shoots[i] / 240), 5, 5, shoot);
				shoots[i] = shoots[i] - 240 * 4;
				if (shoots[i] <= 0)
					shoots[i] = 0;
			}

			// check hits of shoots
			for (int j = 0; j < 9; j++)
			{
				if (shoots[i] != 0)
				{

					if (collision(easyEnemies[j].enemyX, easyEnemies[j].enemyY, 20, 20, shoots[i] % 240, shoots[i] / 240))
					{
						drawRect(easyEnemies[j].enemyX, easyEnemies[j].enemyY, 20, 20, BLACK);
						drawRect((shoots[i] % 240), (shoots[i] / 240) + 4, 5, 5, BLACK);
						easyEnemies[j].enemyY = 0;
						shoots[i] = 0;
						send(vidasYPuntos, MSG_POINT);
						receive();
					}

					if (collision(hardEnemies[j].enemyX, hardEnemies[j].enemyY, 20, 20, shoots[i] % 240, shoots[i] / 240))
					{
						drawRect(hardEnemies[j].enemyX, hardEnemies[j].enemyY, 20, 20, BLACK);
						drawRect((shoots[i] % 240), (shoots[i] / 240) + 4, 5, 5, BLACK);
						hardEnemies[j].enemyY = 0;
						shoots[i] = 0;
						send(vidasYPuntos, MSG_POINT);
						receive();
					}
				}
			}
			if (collision(fast.fastX, fast.fastY, 15, 15, shoots[i] % 240, shoots[i] / 240))
			{
				drawRect(fast.fastX, fast.fastY, 20, 20, BLACK);
				drawRect((shoots[i] % 240), (shoots[i] / 240) + 4, 5, 5, BLACK);
				fast.fastY = 0;
				shoots[i] = 0;
				send(vidasYPuntos, MSG_POINT);
				receive();
			}
		}

		// draw hard enemies
		for (int a = 0; a < 9; a++)
		{
			hardEnemies[a].enemyY += enemyspeed;
			drawImage3(hardEnemies[a].enemyX, hardEnemies[a].enemyY, 20, 20, enemy);
			if (collision(hardEnemies[a].enemyX, hardEnemies[a].enemyY, 20, 20, player.playerX, player.playerY))
			{
				drawRect(hardEnemies[a].enemyX, hardEnemies[a].enemyY, 20, 20, BLACK);
				hardEnemies[a].enemyY = 0;
				send(vidasYPuntos, MSG_LIVES);
				receive();
			}
			if (hardEnemies[a].enemyY >= 228)
			{
				hardEnemies[a].enemyY = 0;
			}
			if ((hardEnemies[a].enemyY >= 200) && (easyEnemies[a].enemyY <= 45))
			{
				hardEnemies[a].enemyY = 160;
			}
			// space enemies apart
			if ((hardEnemies[a].enemyY >= 200) && (easyEnemies[a].enemyY <= 45))
			{
				hardEnemies[a].enemyY = 160;
			}
			if ((easyEnemies[a].enemyY >= 120) && (hardEnemies[a].enemyY >= 170))
			{
				hardEnemies[a].enemyY = 160;
			}
		}
		// draw fast enemy
		drawImage3(fast.fastX, fast.fastY, 15, 15, boss);
		drawHollowRect(fast.fastX - 1, fast.fastY - 1, 17, 17, BLACK);
		drawHollowRect(fast.fastX - 2, fast.fastY - 2, 19, 19, BLACK);
		if (collision(fast.fastX, fast.fastY, 15, 15, player.playerX, player.playerY))
		{
			drawRect(fast.fastX, fast.fastY, 20, 20, BLACK);
			fast.fastY = 0;
			send(vidasYPuntos, MSG_LIVES);
			receive();
		}
		fast.fastX += fastXSpeed;
		fast.fastY += fastYSpeed;
		if (fast.fastX >= 240)
		{
			fast.fastX = 0;
		}
		if (fast.fastY >= 200)
		{
			fast.fastY = player.playerY - 20;
		}
	}
}

int collision(u16 enemyX, u16 enemyY, u16 enemyWidth, u16 enemyHeight,
			  u16 playerX, u16 playerY)
{
	int enemyRight = enemyX + enemyWidth;
	int enemyLeft = enemyX;
	int enemyBottom = enemyY + enemyHeight;
	int enemyTop = enemyY;

	int playerRight = playerX + 24;
	int playerLeft = playerX;
	int playerBottom = playerY + 24;
	int playerTop = playerY;

	// Verificar superposición en ambos ejes (X e Y)
	return (enemyRight > playerLeft &&
			enemyLeft < playerRight &&
			enemyBottom > playerTop &&
			enemyTop < playerBottom);
}

void endGame()
{
	// start Game Over State
	drawImage3(0, 0, 240, 160, gameover);
	drawHollowRect(0, 0, 240, 160, WHITE);
}
