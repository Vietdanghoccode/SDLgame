#include "Object.h"
#include <iostream>
#include <cmath>

std::pair<int, int> nextTileID;

Object::Object(int p_tileX, int p_tileY, int p_velX, int p_velY) {
	tileX = p_tileX;
	tileY = p_tileY;
	if (velX != 0) this->velX = p_velX;
	if (velY != 0) this->velY = p_velY;

	this->scrPosX = tileX * 16;
	this->scrPosY = tileY * 16;
	dead = false;
}

void Object::move() {
	scrPosX += velX;
	scrPosY += velY;

	if (scrPosX % 16 == 0) tileX = scrPosX / 16;
	else tileX = (scrPosX + 8) / 16;
	if (scrPosY % 16 == 0) tileY = scrPosY / 16;
	else tileY = (scrPosY + 8) / 16;
}


void Object::changeVelocityDir(int p_velX, int p_velY, int p_dir) {
	this->velX = p_velX;
	this->velY = p_velY;
	this->dir = p_dir;
};


void Object::goThroughTunnel() {
	if (scrPosY == 224) {
		if (dir == LEFT && scrPosX == 0) {
			tileX = 27;
			scrPosX = 448;
		}
		else if(dir == RIGHT && scrPosX == 432){
			tileX = 0;
			scrPosX = 0;
		}
	}
}
