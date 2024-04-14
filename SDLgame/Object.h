#pragma once

#include <algorithm>

class Object {
protected:
	int scrPosX, scrPosY;
	int velX = 0, velY = 0;
	int tileX, tileY;
	int dir;
	bool dead;
public:
	static const int UP = 1;
	static const int RIGHT = 2;
	static const int DOWN = 3;
	static const int LEFT = 4;
	static const int OBJECT_WIDTH = 30;
	static const int OBJECT_HEIGHT = 30;
	static const int SCREEN_WIDTH = 448;
	static const int SCREEN_HEIGHT = 496;

	Object(int p_tileX, int p_tileY, int p_velX = 0, int p_velY = 0);


	void move();

	int getPosX() const {
		return scrPosX;
	}
	int getPosY() const {
		return scrPosY;
	}

	int getTileX() {
		return tileX;
	}
	int getTileY() {
		return tileY;
	}

	bool isDead() {
		return dead;
	}
	void setDead(bool status) {
		dead = status;
	}
	void resetPacmanTile() {
		tileX = 13; tileY = 23;
		velX = velY = 0;
		scrPosX = tileX * 16;// note
		scrPosY = tileY * 16;
		dead = false;

	}

	void changeVelocityDir(int p_velX, int p_velY, int p_dir);

	void goThroughTunnel();
};