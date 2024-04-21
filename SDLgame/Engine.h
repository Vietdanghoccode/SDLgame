#pragma once

#include <SDL.h>
#include <vector>
#include <string>
#include "TextureSrc.h"
#include "Map.h"
#include "Pacman.h"
#include "Ghost.h"
#include "TickManager.h"
#include "TextObject.h"
#include "Sound.h"
#include "Menu.h"


class Engine {

private:
	Sound* sound;
	Map* map;
	Pacman* pacman;
	Ghost* blinky;
	Ghost* pinky;
	Ghost* inky;
	Ghost* clyde; 
	TextureSrc* objectTexture;
	TextObject* Time;
	TextObject* TextPoint;
	TickManager* tickManager;
	int Point;

public:
	bool back_to_menu = false;

	Engine();
	~Engine();


	void init(SDL_Renderer*& renderer);

	void handleEvent(SDL_Event& e);

	void render(SDL_Renderer*& renderer);

	void loop();

	void ghostMove(Ghost*& ghost);

	void PacmanCollisionGhost(Ghost*& ghost);
	void revivalPacman();

	void resetTick() {
		tickManager->resetTick();
	}

	void renderGhost(SDL_Renderer*& renderer, Ghost*& ghost, int ghostID);

	void renderFoggy(Pacman* pacman, SDL_Renderer*& renderer);


};