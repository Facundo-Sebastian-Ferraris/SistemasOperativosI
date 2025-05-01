// clang-format off
#include <xinu.h>
#include "tifa.h"
#include "titlescreen.h"
#include "playerImage.h"
#include "enemy.h"
#include "boss.h"
#include "gameover.h"
#include "shoot.h"

extern unsigned char tecla_actual;
typedef unsigned short u16;
#define RGB(r, g, b) (r | (g << 5) | (b << 10))
// #define REG_DISPCNT *(u16 *)0x4000000
#define extern videoBuffer
#define MODE3 3
#define BG2_ENABLE (1 << 10)
#define WHITE RGB(31, 31, 31)
#define BLACK RGB(0, 0, 0)

typedef enum {
	MENU,
    RUNNING,
    PAUSED,
    LOSING
} GameState;
GameState estado = MENU;

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

int shoots[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int curr_shot = 0;
#define N_SHOOTS 10

// PROTOTYPES 🧩✨
void galaga_init();
void buttons_functions();
void display();
void turnBlack();

// SEMAPHORES 🚦✨
sid32 rendevouz_renderer;

// GLOBALS 🌎✨
struct Enemy easyEnemies[9];
struct Enemy hardEnemies[9];
struct Players player;
struct FastEnemy fast;

int galaga(void){
	galaga_init();

	pid32 botones_pid = create(buttons_functions, 1024, 20, "botones", 0);
	pid32 display_pid = create(display, 8*1024, 20, "display", 0);
	resume(botones_pid);
	resume(display_pid);
	// REG_DISPCNT = MODE3 | BG2_ENABLE;
	// initalize title screen
	

	// start black screen for drawing

	while (1){	 

		waitForVBlank();
		sleepms(50);
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
				endGame();
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
				if (collision(easyEnemies[j].enemyX, easyEnemies[j].enemyY, 15, 15, shoots[i] % 240, shoots[i] / 240))
				{
					drawRect(easyEnemies[j].enemyX, easyEnemies[j].enemyY, 20, 20, BLACK);
					drawRect((shoots[i] % 240), (shoots[i] / 240) + 4, 5, 5, BLACK);
					easyEnemies[j].enemyY = 0;
					shoots[i] = 0;
				}
			}
		}

		// draw hard enemies
		for (int a = 0; a < 9; a++)
		{
			hardEnemies[a].enemyY += enemyspeed;
			drawImage3(hardEnemies[a].enemyX, hardEnemies[a].enemyY, 20, 20, enemy);
			if (collision(hardEnemies[a].enemyX, hardEnemies[a].enemyY, 20, 20, player.playerX, player.playerY))
			{
				endGame();
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
			endGame();
		}
		// RAFA		fast.fastX += fastXSpeed;
		// RAFA		fast.fastY += fastYSpeed;
		if (fast.fastX >= 240)
		{
			fast.fastX = 0;
		}
		if (fast.fastY >= 200)
		{
			fast.fastY = player.playerY - 20;
		}
	}
	return 0;
}

int collision(u16 enemyX, u16 enemyY, u16 enemyWidth, u16 enemyHeight, u16 playerX, u16 playerY)
{
	// check if bottom right corner of enemy is within player
	if (((enemyX + enemyWidth) > playerX) && ((enemyY + enemyHeight) > playerY) && ((enemyX + enemyWidth) < (playerX + 24)) && ((enemyY + enemyWidth) < (playerY + 24)))
	{
		return 1;
	}
	// check bottom left corner of enemy
	if ((enemyX < (playerX + 24)) && (enemyX > playerX) && ((enemyY + enemyHeight) > playerY) && ((enemyY + enemyHeight) < (playerY + 24)))
	{
		return 1;
	}
	// check top left corner
	if ((enemyX < (playerX + 24)) && (enemyX > playerX) && (enemyY > playerY) && (enemyY < (playerY + 24)))
	{
		return 1;
	}
	// check top right corner
	if (((enemyX + enemyWidth) < (playerX + 24)) && ((enemyX + enemyWidth) > playerX) && (enemyY > playerY) && (enemyY < (playerY + 24)))
	{
		return 1;
	}
	return 0;
}


// RESET VALUES !!!
void galaga_init()
{
	rendevouz_renderer = semcreate(1);
	// easy enemy wave set setup
	for (int a = 0; a < 9; a++)
	{
		easyEnemies[a].enemyX = (28 * a);
		easyEnemies[a].enemyY = 0;
	}
	easyEnemies[1].enemyX = 240;
	easyEnemies[4].enemyX = 240;
	easyEnemies[8].enemyX = 240;
	// difficult enemies setup
	for (int a = 0; a < 9; a++)
	{
		hardEnemies[a].enemyX = (28 * a);
		hardEnemies[a].enemyY = 160;
	}
	hardEnemies[3].enemyX = 240;
	hardEnemies[6].enemyX = 240;
	// player setup
	player.playerX = 120;
	player.playerY = 136;
	// fast enemy "boss" setup
	fast.fastX = 0;
	fast.fastY = 30;
}

// RENDERER 	🖌️✨

void display(){
	while (1){
		wait(rendevouz_renderer);	
		switch (estado)
		{
		case MENU:
		kprintf("Pantalla Inicio\n");
		drawImage3FULL(30, 60, titlescreen);
			break;
		case RUNNING:
		kprintf("Inicio JUEGO\n");
		turnBlack();
			break;
		case LOSING:
		drawImage3FULL(0, 0, gameover);
		drawHollowRect(0, 0, VGA_WIDTH, VGA_HEIGHT, WHITE);
		default:
			break;
		}
	}
	
}

// INPUT CONTROLS	⌨️ ✨
#define BUTTON_A 0x24		// flanco positivo "j"
#define BUTTON_B 0x25			// flanco positivo "k"
#define BUTTON_SELECT 0x03 // flanco positivo "2"
#define BUTTON_START 0x2c  // flanco positivo "z"
#define BUTTON_RIGHT 0x1f	// flanco postivo "s"
#define BUTTON_LEFT 0x1e	// flanco positivo "a"
#define BUTTON_UP 'w'
#define BUTTON_DOWN 's'
#define BUTTON_R '1'
#define BUTTON_L '2'
#define KEY_DOWN_NOW(key) (tecla_actual == key)

void buttons_functions(){
	kprintf("Ejecutando Proceso de botobnes\n");
	while (1)
	{
		if (KEY_DOWN_NOW(BUTTON_START) && estado == MENU){
			estado = RUNNING;
			signal(rendevouz_renderer);
		}
		// go back to title screen if select button is pressed
		if (KEY_DOWN_NOW(BUTTON_SELECT)){
			// kprintf("Volviendo al Menu");
			// galaga();

		}
		// player shots
		if (KEY_DOWN_NOW(BUTTON_A)){
			if (shoots[curr_shot] == 0){
				shoots[curr_shot] = 136 * 240 + player.playerX + 9; /* 24 widht player */
				curr_shot++;
				if (curr_shot >= N_SHOOTS)
					curr_shot = 0;
			};
		}
		// player movement input
		if (KEY_DOWN_NOW(BUTTON_LEFT) && (player.playerX > 0)){
			player.playerX -= playerspeed;
		}
		if (KEY_DOWN_NOW(BUTTON_RIGHT) && (player.playerX <= 216)){
			player.playerX += playerspeed;
		}
		if (KEY_DOWN_NOW(BUTTON_UP) && (player.playerY > 25)){
			player.playerY -= playerspeed;
		}
		if (KEY_DOWN_NOW(BUTTON_DOWN) && (player.playerY <= 136)){
			player.playerY += playerspeed;
		}
	}
	exit();
}

void endGame(){
	// start Game Over State
	estado = LOSING;
	signal(rendevouz_renderer);
	
	while (1){
		if (KEY_DOWN_NOW(BUTTON_SELECT)){
			galaga();
		}
		if (KEY_DOWN_NOW(BUTTON_START)){
			galaga();
		}
	}
}

void turnBlack(){
	for (int i = 0; i < VGA_HEIGHT; i++)
	{
		for (int j = 0; j < VGA_WIDTH; j++)
		{
			setPixelVGA(j, i, BLACK);
		}
	}
}