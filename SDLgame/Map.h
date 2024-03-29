#pragma once

#include "LogStatus.h"
#include <iostream>
#include <fstream>

class Map {
private:
	static const int MAP_WIDTH = 31;
	static const int MAP_HEIGHT = 28;


	LogStatus* Console = new LogStatus("Map");
	int tile[MAP_HEIGHT][MAP_WIDTH];
public:
	Map();

	~Map();

	int getTileID(int x, int y);

	bool isWall(std::pair<int, int> tileID);
};
