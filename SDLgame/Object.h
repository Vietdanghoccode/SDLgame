#pragma once

#include <algorithm>

class Object {
protected:
	int scrPosX, scrPosY;
	int velX = 0, velY = 0;
	int tileX, tileY;
	int dir = 1;
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

	int getOldDir() {
		return dir % 2;
	}

	void changeVelocityDir(int p_velX, int p_velY, int p_dir);

	void changePos(int& newPosX, int& newPosY);
	
};