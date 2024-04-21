#pragma once
#include "Object.h"
#include <stack>

class Pacman : public Object {
private:
	int lifes = 3;
	int sight = 3;// 3 tile;
	std::stack<int> Direction;
	std::stack<	std::pair< int, std::pair< int, int> > > Special; 
public:
	int pacmanVelocity = 1;

	Pacman();

	~Pacman() {
		lifes = 0;
	}
	int getsight() {
		return sight;
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

	int getLife() {
		return lifes;
	}
	void respawn() {
		resetPacmanTile();
		while (!Direction.empty()) Direction.pop();
		eraseSpecial();
	}
	void decreaselife() {
		lifes--;
	}
	
};
