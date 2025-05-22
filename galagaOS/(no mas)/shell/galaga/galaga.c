// clang-format off
#include <xinu.h>
#include "tifa.h"
#include "titlescreen.h"
#include "playerImage.h"
#include "enemy.h"
#include "boss.h"
#include "gameover.h"
#include "shoot.h"
#include "keyBoardConstants.h"

extern unsigned char tecla_actual;
typedef unsigned short u16;
#define RGB(r, g, b) (r | (g << 5) | (b << 10))
// #define REG_DISPCNT *(u16 *)0x4000000
#define extern videoBuffer
#define MODE3 3
#define BG2_ENABLE (1 << 10)
#define WHITE RGB(31, 31, 31)
#define BLACK RGB(0, 0, 0)
#define RED RGB(255, 0, 0)
#define BLUE RGB(0, 0, 255)
#define GBA_WIDTH 240
#define GBA_HEIGHT 160
#define GBAtoVGA_X VGA_WIDTH/GBA_WIDTH
#define GBAtoVGA_Y VGA_HEIGHT/GBA_HEIGHT
#define KEY_DOWN_NOW(key)  (tecla_actual == key)

#define BUTTON_ENTER 0x1c


typedef enum {
	MENU,
    RUNNING,
    PAUSED,
    LOSING,
	KILL
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
void drawImage3ToVGA(int x, int y, int size_x, int size_y, const u16 *image);
void drawImage3Scaler(int x, int y, int size_x, int size_y, int scale_x, int scale_y, const u16 *image);
void waitForVBlank();

// helpers
void initialize();
void drawEnemies();
void endGame();

//====== STRUCTURES 🏦⚙️ ======//
struct Players
{
	
	volatile u16 lives;
	volatile u16 score;
	volatile u16 playerX;
	volatile u16 playerY;
};
struct Enemy
{
	int isAlive;
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

//====== PROTOTYPES 🧩✨ ======//

//PROCESSOS 🏁🏎️
void galaga_init();
void buttons_functions();
void turnBlack();	pid32 pid_botones;
void display();		pid32 pid_display;
void gameStart();	pid32 pid_gameStart;
//ENGINE ⚙️
int scalePosX(int x);
int scalePosY(int y);

void playEasyEnemies();
void playHardEnemies();
void playFastEnemy();
//DRAWERS 🎨🖌️
void drawShots();
void drawTitleScreen();
void drawPlayer();
void drawEasyEnemy(int index);
void drawFastEnemy();
//Checkers 🔎👀
int collision(u16 enemyX, u16 enemyY, u16 enemyWidth, u16 enemyHeight, u16 playerX, u16 playerY);
//===========================//


//====== SEMAPHORES 🚦🪡 ======//
sid32 rendevouz_renderer;
sid32 rendevouz_closeGame;
sid32 mutex_PlayerX;
sid32 mutex_PlayerY;

//===========================//


//====== GLOBALS 🌎✨ ======//
struct Enemy
	easyEnemies[9],
	hardEnemies[9];

struct Players player;
struct FastEnemy fast;


//===========================//

//====== 🔱 MAIN 🔱 ======//
int galaga(void){
	kprintf("\033[2J");
	galaga_init();

	
	resume(pid_botones);
	resume(pid_display);
	// REG_DISPCNT = MODE3 | BG2_ENABLE;
	// initalize title screen
	
	while (estado != KILL){	 
		if(estado == RUNNING)
		{		
			waitForVBlank();
			drawPlayer();
			
			// playEasyEnemies();

			// drawShots();

			// playHardEnemies();

			// playFastEnemy();
		}
	}
	kill(pid_botones);
	kill(pid_display);
	return 0;
}

void gameStart(){

}

int collision(u16 enemyX, u16 enemyY, u16 enemyWidth, u16 enemyHeight, 
	u16 playerX, u16 playerY) 
{
// Coordenadas del jugador
u16 playerRight = playerX + 24;
u16 playerBottom = playerY + 24;

// Coordenadas del enemigo
u16 enemyRight = enemyX + enemyWidth;
u16 enemyBottom = enemyY + enemyHeight;

// Detección de colisión entre rectángulos
return 
	(enemyX < playerRight) &&
 	(enemyRight > playerX) &&
 	(enemyY < playerBottom) &&
 	(enemyBottom > playerY);
}


// START VALUES 🎬✨
void galaga_init()
{
	rendevouz_renderer = semcreate(1);
	// easy enemy wave set setup
	for (int a = 0; a < 9; a++)
	{
		easyEnemies[a].isAlive = 1;
		easyEnemies[a].enemyX = (28 * a);
		easyEnemies[a].enemyY = 0;
	}
	easyEnemies[1].enemyX = 240;
	easyEnemies[4].enemyX = 240;
	easyEnemies[8].enemyX = 240;
	// difficult enemies setup
	for (int a = 0; a < 9; a++)
	{
		hardEnemies[a].isAlive = 1;
		hardEnemies[a].enemyX = (28 * a);
		hardEnemies[a].enemyY = 160;
	}
	hardEnemies[3].enemyX = 240;
	hardEnemies[6].enemyX = 240;
	// player setup
	player.playerX = 120;
	player.playerY = 136;
	player.score = 0;
	player.lives = 3;
	// fast enemy "boss" setup

	fast.fastX = 0;
	fast.fastY = 30;

	pid_botones = create(buttons_functions, 1024, 20, "botones", 0);
	pid_display = create(display, 8*1024, 20, "display", 0);
}

// RENDERER 🖌️✨

void display(){
	while (1){
		wait(rendevouz_renderer);	
		switch (estado)
		{
		case MENU:
			turnBlack();
			drawTitleScreen();
			break;
		case RUNNING:
			turnBlack();
			break;
		case LOSING:
			drawImage3FULL(0, 0, gameover);
		default:
			break;
		}
	}
	
}

// INPUT CONTROLS ⌨️ ✨

void buttons_functions(){
	kprintf("\033[0;0HEjecutando Proceso de botobnes\n");
	while (1)
	{
		// kprintf("\033[0;1H%x",tecla_actual);
		if (estado != LOSING)
		{
			sleepms(30);
			if (KEY_DOWN_NOW(BUTTON_ENTER) && estado == MENU){
				estado = RUNNING;
				signal(rendevouz_renderer);
			}
			// go back to title screen if select button is pressed
			if (KEY_DOWN_NOW(BUTTON_ESCAPE)){
				estado = RUNNING;
				signal(rendevouz_renderer);

			}
			// player shots
			if (KEY_DOWN_NOW('z')){
				if (shoots[curr_shot] == 0){
					shoots[curr_shot] = 136 * 240 + player.playerX + 9; /* 24 widht player */
					curr_shot++;
					if (curr_shot >= N_SHOOTS)
						curr_shot = 0;
				};
			}
			// player movement input
			if (KEY_DOWN_NOW(BUTTON_LEFT_ARROW) && (player.playerX > 0)){
				increasePlayerX(-playerspeed);
			}
			if (KEY_DOWN_NOW(BUTTON_RIGHT_ARROW) && (player.playerX <= GBA_WIDTH)){
				increasePlayerX(playerspeed);
			}
			if (KEY_DOWN_NOW(BUTTON_UP_ARROW) && (player.playerY > 25)){
				increasePlayerY(-playerspeed);
			}
			if (KEY_DOWN_NOW(BUTTON_DOWN_ARROW) && (player.playerY <= 136)){
				increasePlayerY(playerspeed);
			}
		} else {
			if (KEY_DOWN_NOW(BUTTON_z)){
				estado = MENU;
				signal(rendevouz_renderer);
			}
			if (KEY_DOWN_NOW(BUTTON_ENTER)){
				estado = RUNNING;
				signal(rendevouz_renderer);
				galaga_init();
			}
		}
		
	}
}

// PLAYER RESOURCES

void increasePlayerX(int x){
	wait(mutex_PlayerX);
	player.playerX += x;
	signal(mutex_PlayerX);
}

void increasePlayerY(int y){
	wait(mutex_PlayerY);
	player.playerY += y;
	signal(mutex_PlayerY);
}

void getPlayerX(){
	return player.playerX;
}

void getPlayerY(){
	return player.playerY;
}

// DRAWERS
void drawTitleScreen(){
	kprintf("Pantalla Inicio\n");
	drawImage3FULL(30, 60, titlescreen);
}

void drawEasyEnemy(int index){
	int pos_rel_x = scalePosX(easyEnemies[index].enemyX);
	int pos_rel_y = scalePosX(easyEnemies[index].enemyY);
	int size_rel_x = scalePosX(ENEMY_WIDTH);
	int size_rel_y = scalePosY(ENEMY_HEIGHT);
	drawImage3Scaler(pos_rel_x, pos_rel_y, ENEMY_WIDTH, ENEMY_HEIGHT,GBAtoVGA_X, GBAtoVGA_Y, enemy);
}

void drawHardEnemy(int index){
	int pos_rel_x = scalePosX(hardEnemies[index].enemyX);
	int pos_rel_y = scalePosX(hardEnemies[index].enemyY);
	int size_rel_x = scalePosX(ENEMY_WIDTH);
	int size_rel_y = scalePosY(ENEMY_HEIGHT);
	drawImage3Scaler(pos_rel_x, pos_rel_y, ENEMY_WIDTH, ENEMY_HEIGHT,GBAtoVGA_X, GBAtoVGA_Y, enemy);
}

void drawFastEnemy(){
	// draw fast enemy
	int pos_rel_x = scalePosX(fast.fastX);
	int pos_rel_y = scalePosX(fast.fastY);
	int size_rel_x = scalePosX(BOSS_WIDTH);
	int size_rel_y = scalePosY(BOSS_HEIGHT);
	drawImage3Scaler(pos_rel_x, pos_rel_y, BOSS_WIDTH, BOSS_HEIGHT,GBAtoVGA_X, GBAtoVGA_Y, boss);
	drawHollowRect(pos_rel_x - 1, fast.fastY - 1, 17, 17, BLACK);
	drawHollowRect(pos_rel_x - 2, fast.fastY - 2, 19, 19, BLACK);

	int maxIt = 9;
	for (int i = 1; i <= maxIt; i++)
	{
		drawHollowRect(pos_rel_x - i, pos_rel_y-1, size_rel_x+maxIt-5, size_rel_y+1, BLACK);
	}
}

void drawPlayer(){
	int pos_rel_x = scalePosX(player.playerX);
	int pos_rel_y = scalePosX(player.playerY);
	int size_rel_x = scalePosX(PLAYERIMAGE_WIDTH);
	int size_rel_y = scalePosY(PLAYERIMAGE_HEIGHT);
	drawImage3Scaler(pos_rel_x, pos_rel_y, PLAYERIMAGE_WIDTH, PLAYERIMAGE_HEIGHT, GBAtoVGA_X, GBAtoVGA_Y, playerImage);
	
	int maxIt = 9;
	for (int i = 1; i <= maxIt; i++)
	{
		drawHollowRect(pos_rel_x - i, pos_rel_y-1, size_rel_x+maxIt-5, size_rel_y+1, BLACK);
	}
}

void drawShots(){
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
				easyEnemies[j].isAlive = 0;
				easyEnemies[j].enemyY = 0;
				shoots[i] = 0;
			}

			if (collision(hardEnemies[j].enemyX, hardEnemies[j].enemyY, 15, 15, shoots[i] % 240, shoots[i] / 240))
			{
				drawRect(hardEnemies[j].enemyX, hardEnemies[j].enemyY, 20, 20, BLACK);
				drawRect((shoots[i] % 240), (shoots[i] / 240) + 4, 5, 5, BLACK);
				hardEnemies[j].isAlive = 0;
				hardEnemies[j].enemyY = 0;
				shoots[i] = 0;
			}
		}
	}
}


// HELPERS

int scalePosX(int x){
	return x * GBAtoVGA_X;
}

int scalePosY(int y){
	return y * GBAtoVGA_Y;
}

// playNPCs

void playEasyEnemies(){
	for (int a = 0; a < 9; a++)
	{
		int pos_rel_x = scalePosX(easyEnemies[a].enemyX);
		int pos_rel_y = scalePosX(easyEnemies[a].enemyY);
		int size_rel_x = scalePosX(ENEMY_WIDTH);
		int size_rel_y = scalePosY(ENEMY_HEIGHT);
		if(easyEnemies[a].isAlive){
			easyEnemies[a].enemyY += enemyspeed;
			drawEasyEnemy(a);
			if (collision(pos_rel_x, pos_rel_y, size_rel_x, size_rel_y, scalePosX(player.playerX), scalePosY(player.playerY)))
			{
				endGame();
			}
			if (easyEnemies[a].enemyY >= 160 + ENEMY_HEIGHT)
			{
				easyEnemies[a].enemyY = 0;
			}
		}
	}
}

void playHardEnemies(){

	for (int a = 0; a < 9; a++)
	{
		int pos_rel_x = scalePosX(hardEnemies[a].enemyX);
		int pos_rel_y = scalePosX(hardEnemies[a].enemyY);
		int size_rel_x = scalePosX(ENEMY_WIDTH);
		int size_rel_y = scalePosY(ENEMY_HEIGHT);
		if (hardEnemies[a].isAlive)
		{	
			hardEnemies[a].enemyY += enemyspeed;
			drawHardEnemy(a);
			if (collision(pos_rel_x, pos_rel_y, size_rel_x, size_rel_y, scalePosX(player.playerX), scalePosY(player.playerY)))
			{
				endGame();
			}
			if (hardEnemies[a].enemyY >= 160)
			{
				hardEnemies[a].enemyY = 0;
			}
			// if ((hardEnemies[a].enemyY >= 200) && (easyEnemies[a].enemyY <= 45))
			// {
			// 	hardEnemies[a].enemyY = 160;
			// }
			// // space enemies apart
			// if ((hardEnemies[a].enemyY >= 200) && (easyEnemies[a].enemyY <= 45))
			// {
			// 	hardEnemies[a].enemyY = 160;
			// }
			// if ((easyEnemies[a].enemyY >= 120) && (hardEnemies[a].enemyY >= 170))
			// {
			// 	hardEnemies[a].enemyY = 160;
			// }
		}
	}
}

void playFastEnemy(){
	//draw Fast Enemy (BOSS)
	int pos_rel_x = scalePosX(fast.fastX);
	int pos_rel_y = scalePosX(fast.fastY);
	int size_rel_x = scalePosX(BOSS_WIDTH);
	int size_rel_y = scalePosY(BOSS_HEIGHT);
	drawFastEnemy();
	if (collision(pos_rel_x, pos_rel_y, size_rel_x, size_rel_y, scalePosX(player.playerX), scalePosY(player.playerY)))
	{
		endGame();
	}
	// fast.fastX += fastXSpeed;
	fast.fastY += fastYSpeed/2;
	if (fast.fastX >= 240)
	{
		fast.fastX = 0;
	}
	if (fast.fastY >= 200)
	{
		fast.fastY = 0;
	}

}

void endGame(){
	// start Game Over State
	estado = LOSING;
	signal(rendevouz_renderer);
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
