#pragma once
#include "Object.h"
#include <SDL.h>

class Pacman : public Object {
private:
	int eatenCoins;
public:
	static const int pacmanVelocity = 2;

	Pacman();

	~Pacman() {
		eatenCoins = 0;
	}
	
	void manageMove();

	void handleEvent(SDL_Event &e);

};
