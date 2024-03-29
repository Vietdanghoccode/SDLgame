#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>
#include "LogStatus.h"
#include "Engine.h"
//
class Window {
private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	Engine* engine = nullptr;

	LogStatus* Console = new LogStatus("Window");

	bool Running = false;
	

public:
	static const int SCREEN_WIDTH = 448;
	static const int SCREEN_HEIGHT = 496;
	const std::string WINDOW_TITTLE = "Pacman";
	
	Window();

	~Window();

	void initSDL();

	void quitSDL();

	void runGame();

};
