#pragma once
#include "Object.h"
#include <stack>

class Pacman : public Object {
private:
	int lifes = 3;
	std::stack<int> Direction;
	std::stack<	std::pair< int, std::pair< int, int> > > Special; 
public:
	int pacmanVelocity = 1;

	Pacman();

	~Pacman() {
		lifes = 0;
	}
	bool emptyDirStack() {
		return Direction.empty();
	}

	bool emptySpecial(){
		return Special.empty();
	}
	void pushtoStack(int newDir);

	void pushSpecialStack(int newDir, std::pair<int, int> nextCross);

	int getDir() {
		return Direction.top();
	}
	std::pair<int, int> getSpecial() {
		return Special.top().second;
	}
	void moving();
	void stopmoving();
	void turn();

	void eraseSpecial();

	bool getLife() {
		if (lifes > 0) lifes--;
		return (lifes > 0);
	}
	void respawn() {
		resetPacmanTile();
		while (!Direction.empty()) Direction.pop();
		eraseSpecial();
	}
	
};
