#pragma once
#include "TextureSrc.h"
#include "TextObject.h"
#include "LogStatus.h"
class Menu {
private:
	SDL_Rect button[2];
	TextObject text_menu[2];
	LogStatus* console;
public:
	SDL_Event* menuEvent;
	bool selected[3] = { 0, 0 };
	Menu();
	~Menu();
	
	int MenuLoop(SDL_Renderer* renderer);
	bool checkFocusOnButton(int x, int y, SDL_Rect& rect);


};