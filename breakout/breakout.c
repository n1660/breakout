#include <SDL.h>
#include <SDL_main.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <Math.h>
#include <Windows.h>

typedef struct Stage {
	int ID;
	int amountStones;
	SDL_Color color;
} Stage;

void initializeTargets(Stage level, SDL_Rect* Amount);
SDL_Color newColor(int r, int g, int b, int a);
Stage createLevel(int amountStones, SDL_Color color);
void initializeLevel(SDL_Rect* level);
void loadLevel(int newlvlid);

SDL_Renderer* renderer;
SDL_Rect* level;
SDL_Rect stone;
SDL_Rect currentStone;
int quit = 0;
int stoneAmount;
int colorAmount = 1;
int winx;
int winy;
int stonewidth = 40;
int stoneheigth = 20;
int lvlid = 1;
int currentLevel = 1;
Stage* levels;
SDL_Color* lvlColors;

//main
int main(int argc, char* argv[]) {


	level = (SDL_Rect*)malloc(100 * sizeof(SDL_Rect));
	levels = (Stage*)malloc(100 * sizeof(Stage));
	lvlColors = (SDL_Color*)malloc(colorAmount);

	if (level == NULL) {
		printf("level = NULL\n");
		return -1;
	}

	if (levels == NULL) {
		printf("levels = NULL\n");
		return -1;
	}

	if (lvlColors == NULL) {
		printf("lvlColors = NULL\n");
		return -1;
	}

	//initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		fprintf(stderr, "Fehler: %s\n", SDL_GetError());
		return -1;
	}
	//initialize SDL end

	createLevel(25, newColor(0xff, 0x77, 0x77, 0xff));

	//get displaysize
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	winx = DM.w;
	winy = DM.h;
	//get displaysize end

	SDL_Window* window = SDL_CreateWindow("breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winx, winy, SDL_WINDOW_FULLSCREEN_DESKTOP);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	printf("vor load");
	initializeLevel(level);
	loadLevel(lvlid);
	printf("for loop");

	//stages
	createLevel(25, newColor(0xff, 0x77, 0x77, 0xff));
	//stages end

	//gameloop
	while (!quit) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, levels[currentLevel - 1].color.r, levels[currentLevel - 1].color.g, levels[currentLevel - 1].color.b, SDL_ALPHA_OPAQUE);
		printf("vor for");
		for (int row = 0; row < (levels[currentLevel - 1].amountStones); row++) {
			for (int col = 0; col < (levels[currentLevel - 1].amountStones); col++) {
				for (int row = 0; row < (levels[currentLevel - 1].amountStones / (winx / stonewidth)); row++) {
					for (int col = 0; col < (levels[currentLevel - 1].amountStones % (winx / stonewidth)); col++) {
						SDL_RenderFillRect(renderer, &level);
					}
				}
			}
		}
		SDL_RenderPresent(renderer);
	}
	//<-- gameloop
}

//initialize rects
void initializeTargets(Stage level, SDL_Rect* Amount) {
	for (int i = 0; i < stoneAmount; i++) {
		SDL_Rect rect = { 0, 0, 0, 0 };
		Amount[i] = rect;
	}
}

//initialize level
void initializeLevel(SDL_Rect* level) {
	for (int i = 0; i < stoneAmount; i++) {
		stone = level[i];
		stone.x = i * 40;
		stone.y = ((stonewidth + 5) * i) / winx;
		stone.w = stonewidth;
		stone.h = stoneheigth;
	}
}

Stage createLevel(int amountStones, SDL_Color color) {
	levels = (Stage*)malloc(lvlid * sizeof(Stage));
	Stage newLevel = { lvlid, amountStones, color };
	levels[lvlid - 1] = newLevel;
	lvlid++;
	return newLevel;
}

SDL_Color newColor(int r, int g, int b, int a) {
	SDL_Color color = { r, g, b, a };
	lvlColors[colorAmount] = color;
	colorAmount++;
	return color;
}

void loadLevel(int newlvlid) {
	int row = 0, col = 0;
	printf("vor for II");
	for (int i = 0; i < levels[currentLevel].amountStones; i++) {
		currentStone = level[i];
		currentStone.x = i * 40;
		currentStone.y = ((stonewidth + 5) * i) / winx;
		currentStone.w = stonewidth;
		currentStone.h = stoneheigth;
		printf("for II -> for III\n");
		for (row = 0; row < (winx / stonewidth); row++) {
			for (col = 0; col < (winx % stonewidth); col++) {
				SDL_RenderFillRect(renderer, &currentStone);
			}
		}
	}
}