#pragma once

#include <SDL.h>
#include <vector>
#include <string>
#include "TextureSrc.h"
#include "Map.h"
#include "Pacman.h"




class Engine {

private:
	Map* map;
	Pacman* pacman;
	TextureSrc* objectTexture;

public:
	Engine();
	~Engine();


	void init(SDL_Renderer*& renderer);

	void handleEvent(SDL_Event& e);

	void render(SDL_Renderer*& renderer);

	void loop();

};