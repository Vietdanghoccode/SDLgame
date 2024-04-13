#include "Ghost.h"

Ghost::Ghost(int tileX, int tileY) :Object(tileX, tileY) {
	frighten = 0;
	dead = false;
	ghostDir = LEFT;
	destination.first = tileX, destination.second = tileY;
}

void Ghost::setDestination(int tileX, int tileY) {
	destination.first = tileX;
	destination.second = tileY;

}

void Ghost::moving() {
	int velX = 0; int velY = 0; int dir = 0;
	switch (ghostDir) {
	case UP:		velY -= ghostVelocity; dir = UP; break;
	case DOWN:		velY += ghostVelocity; dir = DOWN; break;
	case LEFT:		velX -= ghostVelocity; dir = LEFT; break;
	case RIGHT:		velX += ghostVelocity; dir = RIGHT; break;
	}

	changeVelocityDir(velX, velY, dir);
	move();

}