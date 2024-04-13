#include "Engine.h"


typedef std::pair<int, int> II;
typedef std::pair<int, std::pair<int, int>> IP;

Engine::Engine() {
	map = NULL;
	pacman = NULL;
	objectTexture = NULL;
}


Engine::~Engine() {
	map = NULL;
	delete map;

	pacman = NULL;
	delete pacman;

	objectTexture = NULL;
	delete objectTexture;
}
void Engine::init(SDL_Renderer*& renderer) {
	map = new Map();
	map->findingCrossRoad();
	map->NextCrossTileID();
	pacman = new Pacman();
	blinky = new Ghost(13, 11);
	pinky = new Ghost(14, 11); 
	inky = new Ghost(12, 11);
	clyde = new Ghost(15, 11); 

	objectTexture = new TextureSrc();
	objectTexture->loadTileTexture(renderer);
	objectTexture->loadPacmanAndGhostTexture(renderer);
	pacman->pushtoStack(1);
}

void Engine::handleEvent(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN) {
		if (e.key.keysym.sym == SDLK_DOWN
			|| e.key.keysym.sym == SDLK_UP
			|| e.key.keysym.sym == SDLK_LEFT
			|| e.key.keysym.sym == SDLK_RIGHT) {
			int newDir = 0;
			int lastDir = 0;
			int pacmanTileX = pacman->getTileX();
			int pacmanTileY = pacman->getTileY();
			int pacmanPosX = pacman->getPosX();
			int pacmanPosY = pacman->getPosY();
			if (!pacman->emptyDirStack()) lastDir = pacman->getDir();
			switch (e.key.keysym.sym) {
			case SDLK_UP:	newDir = 1; break;
			case SDLK_DOWN:	newDir = 3;	break;
			case SDLK_LEFT:	newDir = 4;	break;
			case SDLK_RIGHT:newDir = 2;	break;
			}
			if (lastDir == 0) {
				if (map->canChangeDir(pacmanTileX, pacmanTileY, newDir)) {
					pacman->pushtoStack(newDir);
				}
			}
			else {
				if (newDir % 2 == lastDir % 2) {// cung phuong
					if (map->canChangeDir(pacmanTileX, pacmanTileY, newDir)) {
						pacman->pushtoStack(newDir);
						if (!pacman->emptySpecial()) {
							pacman->eraseSpecial();
						}
					}
				}
				else {
					std::pair<int, int> nextCross = map->getnextCrossID(pacmanTileX, pacmanTileY, newDir);
					if (lastDir % 2 == 0 && newDir % 2 == 1) { // dang di doc thi re ngang
						if(pacmanPosY == pacmanTileY * 16) {
							if (map->canChangeDir(pacmanTileX, pacmanTileY, newDir)) {
								pacman->pushSpecialStack(newDir, II(pacmanTileX, pacmanTileY));
							}
							else if(nextCross != II(-1, -1) && !map->besideCrossIsWall(nextCross, newDir) && abs(pacmanPosX - nextCross.first * 16) <= 30) {
								pacman->pushSpecialStack(newDir, nextCross);
							}
						}
					}
					else if(lastDir % 2 == 1 && newDir % 2 == 0) {//dang di ngang thi re doc
						if (pacmanPosX == pacmanTileX * 16) {
							if (map->canChangeDir(pacmanTileX, pacmanTileY, newDir)) {
								pacman->pushSpecialStack(newDir, II(pacmanTileX, pacmanTileY));
							}
							else if(nextCross != II(-1, -1) && !map->besideCrossIsWall(nextCross,newDir)  &&abs(pacmanPosY - nextCross.second * 16) <= 30) {
								pacman->pushSpecialStack(newDir, nextCross);
							}
						}

					}
				}

			}
		}
	}
}

void Engine::render(SDL_Renderer*& renderer) {
	SDL_Rect dsRect;
	++pacmanframe;
	++ghostframe;
	for(int i = 0; i < 28; ++i) {
		for (int j = 0; j < 31; ++j) {
			dsRect = { i * 16, j * 16, 16, 16 };
			objectTexture->renderTileTexture(renderer, map->getTileID(i, j), &dsRect);

		}
	}
	int dir = 0;
	
	if (!pacman->emptyDirStack()) dir = pacman->getDir();
 	objectTexture->renderPacmanTexture(renderer, pacman->getPosX(), pacman->getPosY(), dir, pacmanframe);
	objectTexture->renderGhostTexture(renderer, blinky->getPosX(), blinky->getPosY(), TextureSrc::BLINKY, blinky->getGhostDir(), ghostframe);
	objectTexture->renderGhostTexture(renderer, pinky->getPosX(), pinky->getPosY(), TextureSrc::PINKY, pinky->getGhostDir(), ghostframe);
	objectTexture->renderGhostTexture(renderer, inky->getPosX(), inky->getPosY(), TextureSrc::INKY, inky->getGhostDir(), ghostframe);
	objectTexture->renderGhostTexture(renderer, clyde->getPosX(), clyde->getPosY(), TextureSrc::CLYDE, clyde->getGhostDir(), ghostframe);

}

void Engine::loop() {
	int pacmanTileX = pacman->getTileX();
	int pacmanTileY = pacman->getTileY();
	int pacmanPosX = pacman->getPosX();
	int pacmanPosY = pacman->getPosY();
	int lastDir = 0;

	if (!pacman->emptyDirStack()) lastDir = pacman->getDir();

	if (lastDir != 0 && !pacman->isDead()) {
		if (pacmanTileX * 16 == pacman->getPosX() && pacmanTileY * 16 == pacman->getPosY()) {
			if (map->iscrossRoad(pacmanTileX, pacmanTileY)) {
				if (!pacman->emptySpecial()) pacman->turn();
			}
			if (map->canChangeDir(pacmanTileX, pacmanTileY, pacman->getDir())) pacman->moving();
			else pacman->stopmoving();
		}
		else {
			if (map->canChangeDir(pacmanTileX, pacmanTileY, lastDir)) pacman->moving();
			else {
				if (pacmanTileX * 16 == pacman->getPosX() && pacmanTileY * 16 != pacman->getPosY()) pacman->moving();
				else if (pacmanTileX * 16 != pacman->getPosX() && pacmanTileY * 16 == pacman->getPosY()) pacman->moving();
				else pacman->stopmoving();
			}
		}
	}

	
	// frighten
	/*
	if (typeOfCoin != Map::notCoin) {
		pacman->eatCoins();
		if (typeOfCoin == Map::superCoins) {
			blinky->setFrighten(true);
			pinky ->setFrighten(true);
			inky  ->setFrighten(true);
			clyde ->setFrighten(true);
		}
	}
	*/

	// Set up ghost target

	if (!pacman->isDead()) {
		if (!blinky->isFrighten()) {
			blinky->setDestination(pacmanTileX, pacmanTileY);
		}
		if (!pinky->isFrighten()) {
			switch (lastDir) {
			case Map::UP:
				pinky->setDestination(pacmanTileX, pacmanTileY - 4);
				break;
			case Map::DOWN:
				pinky->setDestination(pacmanTileX, pacmanTileY + 4);
				break;
			case Map::LEFT:
				pinky->setDestination(pacmanTileX - 4, pacmanTileY);
				break;
			case Map::RIGHT:
				pinky->setDestination(pacmanTileX + 4, pacmanTileY);
				break;
			case 0:
				pinky->setDestination(pacmanTileX, pacmanTileY);
				break;
			}
		}
		if (!inky->isFrighten()) {
			inky->setDestination(2 * pacmanTileX - blinky->getNextTileX(), 2 * pacmanTileY - blinky->getTileY());
		}
		if (!clyde->isFrighten()) {
			if ((pacmanTileX - clyde->getTileX()) * (pacmanTileX - clyde->getTileX()) + (pacmanTileY - clyde->getTileY()) * (pacmanTileY - clyde->getTileY()) >= 64)
				clyde->setDestination(Ghost::DEFAULT_CLYDE_TILE_X, Ghost::DEFAULT_CLYDE_TILE_Y);
			else
				clyde->setDestination(pacmanTileX, pacmanTileY);
		}
		

	}
	ghostMove(blinky);
	ghostMove(pinky);
	ghostMove(inky);
	ghostMove(clyde);
	
	pacman->goThroughTunnel();
	blinky->goThroughTunnel();
	pinky->goThroughTunnel();
	inky->goThroughTunnel();
	clyde->goThroughTunnel();

	map->eatenCoins(pacmanTileX, pacmanTileY);
	if (map->coin % 5 == 0) {
		map->randomBigCoin();
	}

	
}

void Engine::ghostMove(Ghost*& ghost) {
	int ghostTileX = ghost->getTileX();
	int ghostTileY = ghost->getTileY();
	int ghostPosX = ghost->getPosX();
	int ghostPosY = ghost->getPosY();
	int ghostOldDir = ghost->getGhostDir();
	int ghostNextTileX = ghost->getNextTileX();
	int ghostNextTileY = ghost->getNextTileY();
	// finding the road
	if (ghostTileX * 16 == ghostPosX && ghostTileY * 16 == ghostPosY) {
		if (map->iscrossRoad(ghostTileX, ghostTileY)) {
			// bfs algorithm
			int UP_DIS =	100000;
			int DOWN_DIS =	100000;
			int LEFT_DIS =	100000;
			int RIGHT_DIS = 100000;
			//UP
			if (map->canChangeDir(ghostTileX, ghostTileY, Map::UP)) {
				UP_DIS = map->bfs(ghostTileX, ghostTileY, ghost->getDestination(), Map::UP);
			}
			// DOWN
			if (map->canChangeDir(ghostTileX, ghostTileY, Map::DOWN)) {
				DOWN_DIS = map->bfs(ghostTileX, ghostTileY, ghost->getDestination(), Map::DOWN);
			}
			// LEFT
			if (map->canChangeDir(ghostTileX, ghostTileY, Map::LEFT)) {
				LEFT_DIS = map->bfs(ghostTileX, ghostTileY, ghost->getDestination(), Map::LEFT);
			}
			//RIGHT
			if (map->canChangeDir(ghostTileX, ghostTileY, Map::RIGHT)) {
				RIGHT_DIS = map->bfs(ghostTileX, ghostTileY, ghost->getDestination(), Map::RIGHT);
			}
			int distanceMIN;
			if (ghostOldDir == Map::UP) {
				distanceMIN = std::min(UP_DIS, std::min(LEFT_DIS, RIGHT_DIS));
				if (distanceMIN == UP_DIS) ghost->setDir(Map::UP);
				else if (distanceMIN == LEFT_DIS) ghost->setDir(Map::LEFT);
				else ghost->setDir(Map::RIGHT);
			}
			if (ghostOldDir == Map::DOWN) {
				distanceMIN = std::min(DOWN_DIS, std::min(LEFT_DIS, RIGHT_DIS));
				if (distanceMIN == DOWN_DIS) ghost->setDir(Map::DOWN);
				else if (distanceMIN == LEFT_DIS) ghost->setDir(Map::LEFT);
				else ghost->setDir(Map::RIGHT);
			}
			if (ghostOldDir == Map::LEFT) {
				distanceMIN = std::min(UP_DIS, std::min(DOWN_DIS, LEFT_DIS));
				if (distanceMIN == UP_DIS) ghost->setDir(Map::UP);
				else if (distanceMIN == DOWN_DIS) ghost->setDir(Map::DOWN);
				else ghost->setDir(Map::LEFT);
			}
			if (ghostOldDir == Map::RIGHT) {
				distanceMIN = std::min(UP_DIS, std::min(RIGHT_DIS, DOWN_DIS));
				if (distanceMIN == UP_DIS) ghost->setDir(Map::UP);
				else if (distanceMIN == RIGHT_DIS) ghost->setDir(Map::RIGHT);
				else ghost->setDir(Map::DOWN);
			}
			std::cout << UP_DIS << " " << RIGHT_DIS << " "<< DOWN_DIS << " " << LEFT_DIS << std::endl;
		}
		if (map->canChangeDir(ghostTileX, ghostTileY, ghost->getGhostDir())) ghost->moving();
	}
	else {
		if (map->canChangeDir(ghostTileX, ghostTileY, ghost->getGhostDir())) ghost->moving();
		else {
			if (ghostTileX * 16 == ghostPosX && ghostTileY * 16 != ghostPosY && ghost->getGhostDir() % 2 == 1) ghost->moving();
			else if (ghostTileY * 16 == ghostPosY && ghostTileX * 16 != ghostPosX && ghost->getGhostDir() % 2 == 0) ghost->moving();
		}
	}
}
