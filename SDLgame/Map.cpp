#include "Map.h"

typedef std::pair< int, int> II;

bool firstInit = true;
int premanMap[31][28];


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
	return tile[y][x];
}

std::pair<int, int> Map::getnextCrossID(int x, int y, int dir) {
	return nextCrossID[y][x][dir];
}

bool Map::isWall(std::pair<int, int> tileID) {
	return tile[tileID.second][tileID.first] != 26
		&& tile[tileID.second][tileID.first] != 30
		&& tile[tileID.second][tileID.first] != 27;
}

bool Map::iscrossRoad(int x, int y) {
	int cnt = 0;
	if (markcross[y][x][UP]) ++cnt;
	if (markcross[y][x][RIGHT]) ++cnt;
	if (markcross[y][x][DOWN]) ++cnt;
	if (markcross[y][x][LEFT]) ++cnt;

	if (cnt >= 3) return true;
	if (cnt == 2) {
		if (markcross[y][x][UP] && markcross[y][x][DOWN]) return false;
		if (markcross[y][x][LEFT] && markcross[y][x][RIGHT]) return false;

		return true;
	}
	return false;
}

bool Map::canChangeDir(int x, int y, int newDir) {
	return markcross[y][x][newDir];
}

bool Map::besideCrossIsWall(std::pair<int, int> Cross, int newDir) {
	switch (newDir) {
	case UP:
		Cross.second -= 1;
		break;
	case DOWN:
		Cross.second += 1;
		break;
	case RIGHT:
		Cross.first += 1;
		break;
	case LEFT:
		Cross.first -= 1;
		break;
	}

	return isWall(Cross);
}

void Map::findingCrossRoad() {
	for (int x = 0; x < MAP_WIDTH; ++x) {
		for (int y = 0; y < MAP_HEIGHT; ++y) {
			for (int dir = 1; dir < 5; ++dir) {
				markcross[y][x][dir] = false;
			}
			if (tile[y][x] != 26 && tile[y][x] != 27 && tile[y][x] != 30) continue;

			if (y > 0 && (tile[y - 1][x] == 26 || tile[y - 1][x] == 27 || tile[y - 1][x] == 30)) markcross[y][x][UP] = true;
			if (y < 30 && (tile[y + 1][x] == 26 || tile[y + 1][x] == 27 || tile[y + 1][x] == 30)) markcross[y][x][DOWN] = true;
			if (x > 0 && (tile[y][x - 1] == 26 || tile[y][x - 1] == 27 || tile[y][x - 1] == 30)) markcross[y][x][LEFT] = true;
			if (x < 27 && (tile[y][x + 1] == 26 || tile[y][x + 1] == 27 || tile[y][x + 1] == 30)) markcross[y][x][RIGHT] = true;
		}
	}
}

void Map::NextCrossTileID() {
	//LEFT AND RIGHT
	for (int y = 0; y < MAP_HEIGHT; ++y) {
		//Left
		nextCrossID[y][0][LEFT] = II(-1, -1);
		for (int x = 1; x < MAP_WIDTH; ++x) {

			nextCrossID[y][x][LEFT] = II(-1, -1);
			if (!isWall(std::pair<int, int> (x, y))) {
				if (nextCrossID[y][x - 1][LEFT] != II(-1, -1)) {
					nextCrossID[y][x][LEFT] = nextCrossID[y][x-1][LEFT];
				}
				if (iscrossRoad(x - 1, y)) {
					nextCrossID[y][x][LEFT] = II(x - 1, y);
				}
			}
		}
		//Right
		nextCrossID[y][MAP_WIDTH - 1][RIGHT] = II(-1, -1);
		for (int x = MAP_WIDTH - 2; x >= 0; --x) {
			nextCrossID[y][x][RIGHT] = II(-1, -1);

			if (!isWall(std::pair<int, int>(x, y))) {
				if (nextCrossID[y][x + 1][RIGHT] != II(-1, -1)) {
					nextCrossID[y][x][RIGHT] = nextCrossID[y][x + 1][RIGHT];
				}
				if (iscrossRoad(x + 1, y)) nextCrossID[y][x][RIGHT] = II(x + 1, y);
			}
		}
	}
	//UP and DOWN
	for (int x = 0; x < MAP_WIDTH; ++x) {
		//UP
		nextCrossID[0][x][UP] = II(-1, -1);
		for (int y = 1; y < MAP_HEIGHT; ++y) {
			nextCrossID[y][x][UP] = II(-1, -1);

			if (!isWall(std::pair<int, int>(x, y))) {
				if (nextCrossID[y - 1][x][UP] != II(-1, -1)) {
					nextCrossID[y][x][UP] = nextCrossID[y - 1][x][UP];
				}
				if (iscrossRoad(x, y - 1)) {
					nextCrossID[y][x][UP] = II(x, y - 1);
				}
			}
		}
		//DOWN
		nextCrossID[MAP_HEIGHT - 1][x][DOWN] = II(-1, -1);
		for (int y = MAP_HEIGHT - 2; y >= 0; --y) {
			nextCrossID[y][x][DOWN] = II(-1, -1);

			if (!isWall(std::pair<int, int>(x, y))) {
				if (nextCrossID[y + 1][x][DOWN] != II(-1, -1)) {
					nextCrossID[y][x][DOWN] = nextCrossID[y+1][x][DOWN];
				}
				if (iscrossRoad(x, y + 1)) {
					nextCrossID[y][x][DOWN] = II(x, y + 1);
				}
			}
		}
	}
}

bool Map::eatenCoins(int pacmanTileX, int pacmanTileY) {
	if (tile[pacmanTileY][pacmanTileX] == 26) {
		tile[pacmanTileY][pacmanTileX] = 30;
		coin++;
		return true;
	} else if (tile[pacmanTileY][pacmanTileX] == 27) {
		tile[pacmanTileY][pacmanTileX] = 30;
		existBcoin --;
		return true;
	}
	return 0;
}
void Map::randomBigCoin() {
	if (existBcoin >= 2) {
		return;
	}
	int posX = rand() % 28;
	int posY = rand() % 31;
	while (tile[posX][posY] != 30) {
		posX = rand() % 28;
		posY = rand() % 31;
	}
	tile[posX][posY] = 27;
	existBcoin++;
	
}

int Map::bfs(int tileX, int tileY, std::pair<int , int> target, int dir) {
	// refresh 
	bool visited[31][28];// da tham hay chua
	int distance[31][28];// khoang cach tu o bat dau toi o (i, j)


	int dx[4] = { -1, 0, 0, 1 };
	int dy[4] = { 0, -1, 1, 0 };

	for (int i = 0; i < 31; i++) {
		for (int j = 0; j < 28; j++) {
			visited[i][j] = 0;
			distance[i][j] = 0;
		}
	}
	if (dir == UP) {
		visited[tileX - 1][tileY] = 1;
		visited[tileX + 1][tileY] = 1;
		visited[tileX][tileY + 1] = 1;
	}
	if (dir == DOWN) {
		visited[tileX - 1][tileY] = 1;
		visited[tileX + 1][tileY] = 1;
		visited[tileX][tileY - 1] = 1;
	}
	if (dir == LEFT) {
		visited[tileX][tileY - 1] = 1;
		visited[tileX + 1][tileY] = 1;
		visited[tileX][tileY + 1] = 1;
	}
	if (dir == RIGHT) {
		visited[tileX - 1][tileY] = 1;
		visited[tileX][tileY - 1] = 1;
		visited[tileX][tileY + 1] = 1;
	}

	// starting finding path
	std::queue< std::pair<int, int>> q;
	q.push({ tileX, tileY });
	visited[tileX][tileY] = 1;
	distance[tileX][tileY] = 0;
	while (!q.empty()) {
		std::pair<int, int> top = q.front();
		q.pop();
		for (int k = 0; k < 4; k++) {
			int besideX = top.first + dx[k];
			int besideY = top.second + dy[k];
			if (besideX >= 0 && besideX <= 27 && besideY >= 0 && besideY <= 30
				&& visited[besideX][besideY] == 0 && (getTileID(besideX,besideY) == 30||getTileID(besideX, besideY) == 26||getTileID(besideX, besideY) == 27) ) {
				distance[besideX][besideY] = distance[top.first][top.second] + 1;
				if (distance[target.first][target.second] != 0) break;
				q.push({ besideX, besideY });
				visited[besideX][besideY] = 1;
			}
		}
	}
	return distance[target.first][target.second];
}