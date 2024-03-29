#include "Map.h"


bool firstInit = true;
int premanMap[28][31];
Map::Map() {
	if (firstInit) {
		std::ifstream file("gfx/map.txt");
		if (file) {
			for (int i = 0; i < MAP_HEIGHT; ++i) {
				for (int j = 0; j < MAP_WIDTH; ++j) {
					file >> premanMap[i][j];
					if (premanMap[i][j] > 31 || premanMap[i][j] < 0) {
						Console->Status("Wrong Tile!");
						return;
					}
				}
			}
			Console->Status("Map read successfully!");
		}
		else {
			Console->Status("Error reading file!");
		}
	}
	for (int i = 0; i < MAP_HEIGHT; ++i) {
		for (int j = 0; j < MAP_WIDTH; ++j) {
			tile[i][j] = premanMap[i][j];
		}
	}
	
}

Map::~Map() {
	Console = NULL;
	delete Console;
}

int Map::getTileID(int x, int y) {
	return tile[x][y];
}

bool Map::isWall(std::pair<int, int> tileID) {
	return tile[tileID.second][tileID.first] != 26
		&& tile[tileID.second][tileID.first] != 30
		&& tile[tileID.second][tileID.first] != 27;
}