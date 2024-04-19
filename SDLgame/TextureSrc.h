#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "LogStatus.h"

class TextureSrc {
private:
	LogStatus* Console = new LogStatus("TextureSrc");

	SDL_Texture* tileTexture;
	SDL_Rect tileSprite[32];

	SDL_Texture* pacmanTexture;
	SDL_Rect pacmanUP[3];
	SDL_Rect pacmanDOWN[3];
	SDL_Rect pacmanLEFT[3];
	SDL_Rect pacmanRIGHT[3];
	SDL_Rect pacmanDEAD[11];


	SDL_Texture* ghostTexture;
	SDL_Rect ghost[5][6][2];

	int pacmanFrame;
	int ghostFrame[5]; // blinky, pinky, inky, clyde, sprit


public:

	static const int UP = 1;
	static const int RIGHT = 2;
	static const int DOWN = 3;
	static const int LEFT = 4;

	static const int FRIGHTEN = 5;
	static const int DEAD = 5;


	static const int BLINKY = 0;
	static const int PINKY = 1;
	static const int INKY = 2;
	static const int CLYDE = 3;
	static const int GHOST_SPIRIT = 4; // hon ma cua con ghost
	static const int TOTAL_GHOST = 5;


	TextureSrc();
	~TextureSrc();

	bool pacmanIsDead();

	void loadTileTexture(SDL_Renderer*& renderer);
	void renderTileTexture(SDL_Renderer*& renderer, int tileID, SDL_Rect* dsRect);

	void loadPacmanAndGhostTexture(SDL_Renderer*& renderer);

	void renderPacmanTexture(SDL_Renderer*& renderer, int posX, int posY, int status);

	void renderGhostTexture(SDL_Renderer*& renderer, int posX, int posY, int ghostID, int status);

	void renderLifesPacman(int i, SDL_Renderer *& renderer);
	
};