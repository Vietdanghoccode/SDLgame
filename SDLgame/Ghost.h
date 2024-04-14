#pragma once
#include "Object.h"
#include "algorithm"

class Ghost : public Object {
private:
	std::pair<int, int > destination;
	int frighten;
	int ghostDir;
	bool scattering;
public:
	static const int ghostVelocity = 1;// thay doi toc do sau
	static const int DEFAULT_BLINKY_TILE_X = 27;
	static const int DEFAULT_BLINKY_TILE_Y = 30;
	static const int DEFAULT_PINKY_TILE_X = 27;
	static const int DEFAULT_PINKY_TILE_Y = 1;
	static const int DEFAULT_INKY_TILE_X = 27;
	static const int DEFAULT_INKY_TILE_Y = 1;
	static const int DEFAULT_CLYDE_TILE_X = 1;
	static const int DEFAULT_CLYDE_TILE_Y = 30;

	Ghost(int tileX, int tileY);

	int getNextTileX() {
		return destination.first;
	}
	int getNextTileY() {
		return destination.second;

	}
	std::pair<int, int> getDestination() {
		return destination;
	}

	int getGhostDir() {
		return ghostDir;
	}

	void setDir(int dir) {
		ghostDir = dir;
	}
	void setFrighten(bool status) {
		if (status) frighten = 500; // thoi gian so hai
		else frighten = 0;
	}


	bool isFrighten() {
		if (frighten > 0) --frighten;
		return (frighten > 0);
	}

	void setScattering(bool status) {
		scattering = status;
	}

	bool isScattering() {
		return scattering;
	}
	void setDestination(int tileX, int tileY);

	void moving();
};