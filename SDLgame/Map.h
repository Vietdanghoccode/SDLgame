#pragma once

#include "LogStatus.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <queue>


class Map {
private:
	static const int MAP_WIDTH = 28;
	static const int MAP_HEIGHT = 31;
	

	LogStatus* Console = new LogStatus("Map");
	int tile[MAP_HEIGHT][MAP_WIDTH];
	std::pair<int, int> nextCrossID[MAP_HEIGHT][MAP_WIDTH][5]; // 5 la so huong di chuyen
	bool markcross[MAP_HEIGHT][MAP_WIDTH][5];

	
public:
	
	int coin = 0;
	int existBcoin = 0;
	static const int UP = 1;
	static const int RIGHT = 2;
	static const int DOWN = 3;
	static const int LEFT = 4;
	Map();

	~Map();

	int getTileID(int x, int y);

	std::pair<int, int> getnextCrossID(int x, int y, int dir);

	bool isWall(std::pair<int, int> tileID);

	bool iscrossRoad(int y, int x);

	bool canChangeDir(int x, int y, int newDir);

	bool besideCrossIsWall(std::pair< int, int> Cross, int newDir);

	void findingCrossRoad();// do ca map xem co nhung crossroad nao

	void NextCrossTileID(); // nhap du lieu vao mang nextcrosstileid, tra ra vi tri cua loi re gan nhat co huong la direction

	bool eatenCoins(int pacmanTileX, int pacmanTileY);

	void randomBigCoin();

	int bfs(int tileX, int tileY, std::pair<int , int> target, int dir);

};
