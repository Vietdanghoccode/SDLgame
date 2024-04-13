#pragma once

#include <SDL.h>
#include <vector>
#include <string>
#include "TextureSrc.h"
#include "Map.h"
#include "Pacman.h"
#include "Ghost.h"


class Engine {

private:
	Map* map;
	Pacman* pacman;
	Ghost* blinky;
	Ghost* pinky;
	Ghost* inky;
	Ghost* clyde;
	TextureSrc* objectTexture;

	int pacmanframe = 0;
	int ghostframe = 0;
public:
	Engine();
	~Engine();


	void init(SDL_Renderer*& renderer);

	void handleEvent(SDL_Event& e);

	void render(SDL_Renderer*& renderer);

	void loop();

	void ghostMove(Ghost*& ghost);

};