#include "Object.h"
#include <iostream>
#include <cmath>

std::pair<int, int> nextTileID;

Object::Object(int p_tileX, int p_tileY, int p_velX, int p_velY) {
	tileX = p_tileX;
	tileY = p_tileY;
	if (velX != 0) velX = p_velX;
	if (velY != 0) velY = p_velY;

	this->scrPosX = tileX * 16;
	this->scrPosY = tileY * 16;
}

void Object::move() {
	scrPosX += velX;
	scrPosY += velY;

	if (scrPosX % 16 == 0 && scrPosY % 16 == 0) {
		tileX = scrPosX / 16;
		tileY = scrPosY / 16;
	}
}

void Object::stop() {
	velX = 0;
	velY = 0;
	scrPosX = tileX * 16;
	scrPosY = tileY * 16;
}

void Object::changeVelocityDir(int p_velX, int p_velY, int p_dir) {
	velX = p_velX;
	velY = p_velY;
	dir = p_dir;
};

void Object::changePos(int& newtileX, int& newtileY) {
	scrPosX = newtileX * 16;
	scrPosY = newtileY * 16;
	tileX = newtileX;
	tileY = newtileY;
}

std::pair<int, int> Object::getNextTileID(int tempDir) {
	if (tempDir == 0) tempDir = dir;
	nextTileID = { tileX, tileY };
	switch (tempDir) {
	case 1: nextTileID.second -= 1; break;
	case 2: nextTileID.first += 1; break;
	case 3: nextTileID.second += 1; break;
	case 4: nextTileID.first -= 1; break;
	}
	return nextTileID;

}