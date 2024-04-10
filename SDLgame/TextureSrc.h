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

public:

	static const int UP = 1;
	static const int RIGHT = 2;
	static const int DOWN = 3;
	static const int LEFT = 4;


	TextureSrc();
	~TextureSrc();

	void loadTileTexture(SDL_Renderer*& renderer);
	void renderTileTexture(SDL_Renderer*& renderer, int tileID, SDL_Rect* dsRect);

	void loadPacmanTexture(SDL_Renderer*& renderer);

	void renderPacmanTexture(SDL_Renderer*& renderer, int posX, int posY, int dir, int &frame);
};