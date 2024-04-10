#pragma once
#include "Object.h"
#include <SDL.h>
#include <stack>

class Pacman : public Object {
private:
	int eatenCoins;
	std::stack<int> Direction;
	std::stack<	std::pair< int, std::pair< int, int> > > Special; 
public:
	static const int pacmanVelocity = 1;

	Pacman();

	~Pacman() {
		eatenCoins = 0;
	}
	
	bool emptyDirStack() {
		return Direction.empty();
	}

	bool emptySpecial(){
		return Special.empty();
	}
	void pushtoStack(int newDir);

	void pushSpecialStack(int newDir, std::pair<int, int> nextCross);

	int getDir() const {
		return Direction.top();
	}
	std::pair<int, int> getSpecial() {
		return Special.top().second;
	}
	void moving();
	void stopmoving();
	void turn();

	void handleEvent(SDL_Event &e);

	void eraseSpecial();

	void eatCoins() {
		++eatenCoins;
	}

};
