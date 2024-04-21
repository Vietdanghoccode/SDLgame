#include "Engine.h"


typedef std::pair<int, int> II;
typedef std::pair<int, std::pair<int, int>> IP;

Engine::Engine() {
	map = NULL;
	pacman = NULL;
	objectTexture = NULL;
	tickManager = NULL;
	Time = NULL;
	TextPoint = NULL;
	Point = 0;
	//sound = NULL;

}


Engine::~Engine() {
	map = NULL;
	delete map;

	pacman = NULL;
	delete pacman;

	objectTexture = NULL;
	delete objectTexture;

	tickManager = NULL;
	delete tickManager;

	Time = NULL;
	delete Time;

	TextPoint = NULL;
	delete TextPoint;

	//sound = NULL;
	//delete sound;

	

}
void Engine::init(SDL_Renderer*& renderer) {
	map = new Map();
	Time = new TextObject();
	TextPoint = new TextObject();
	//sound = new Sound();
	map->findingCrossRoad();
	map->NextCrossTileID();
	pacman = new Pacman();
	blinky = new Ghost(12, 11);
	pinky = new Ghost(13, 11); 
	inky = new Ghost(14, 11);
	clyde = new Ghost(15, 11); 

	objectTexture = new TextureSrc();
	objectTexture->loadTileTexture(renderer);
	objectTexture->loadPacmanAndGhostTexture(renderer);
	pacman->pushtoStack(1);
	tickManager = new TickManager();
	tickManager->resetTick();
	Time->SetColor(TextObject::WHITE_TEXT);
	TextPoint->SetColor(TextObject::WHITE_TEXT);
	srand(time(NULL));
	//sound->Init();
}

void Engine::revivalPacman() {
	pacman->respawn();
	delete blinky;
	blinky = new Ghost(12, 11);
	delete pinky;
	pinky = new Ghost(13, 11);
	delete inky;
	inky = new Ghost(14, 11);
	delete clyde;
	clyde = new Ghost(15, 11);
}

void Engine::handleEvent(SDL_Event& e) {
	//Mix_Music* theme = Mix_LoadMUS("sound/Theme.wav");
	if (e.type == SDL_KEYDOWN) {
		/*if (theme != NULL) {
			if (Mix_PlayingMusic() == 0) {
				Mix_PlayMusic(theme, 0);
			}
			if (e.key.keysym.sym == SDLK_m) {
				if (Mix_PausedMusic() == 1) {
					Mix_ResumeMusic();
				}
				else {
					Mix_PauseMusic();
				}
			}
		}
		else {
			std::cout << "Theme is null";
		}
		*/
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
			if (pacman->isDead()) {
				return;
			}
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
				if (pacman->getPosX() == pacman->getTileX() * 16 || pacman->getPosY() == pacman->getTileY() * 16) {
					if (newDir % 2 == lastDir % 2) {// cung phuong
						if (map->canChangeDir(pacmanTileX, pacmanTileY, newDir)) {
							pacman->pushtoStack(newDir);
							pacman->eraseSpecial();
						}
					}
					else {
						std::pair<int, int> nextCross = map->getnextCrossID(pacmanTileX, pacmanTileY, newDir);
						if (lastDir % 2 == 0 && newDir % 2 == 1) { // dang di doc thi re ngang
							if (pacmanPosY == pacmanTileY * 16) {
								if (map->canChangeDir(pacmanTileX, pacmanTileY, newDir)) {
									pacman->pushSpecialStack(newDir, II(pacmanTileX, pacmanTileY));
								}
								else if (nextCross != II(-1, -1) && !map->besideCrossIsWall(nextCross, newDir) && abs(pacmanPosX - nextCross.first * 16) <= 30) {
									pacman->pushSpecialStack(newDir, nextCross);
								}
							}
						}
						else if (lastDir % 2 == 1 && newDir % 2 == 0) {//dang di ngang thi re doc
							if (pacmanPosX == pacmanTileX * 16) {
								if (map->canChangeDir(pacmanTileX, pacmanTileY, newDir)) {
									pacman->pushSpecialStack(newDir, II(pacmanTileX, pacmanTileY));
								}
								else if (nextCross != II(-1, -1) && !map->besideCrossIsWall(nextCross, newDir) && abs(pacmanPosY - nextCross.second * 16) <= 30) {
									pacman->pushSpecialStack(newDir, nextCross);
								}
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
	for(int i = 0; i < 28; ++i) {
		for (int j = 0; j < 31; ++j) {
			dsRect = { i * 16, j * 16, 16, 16 };
			objectTexture->renderTileTexture(renderer, map->getTileID(i, j), &dsRect);

		}
	}
	int dir = 0;
	
	if (!pacman->emptyDirStack()) dir = pacman->getDir();

	if (pacman->isDead()) {
		if (objectTexture->pacmanIsDead()) {
			if (pacman->getLife()) { 
				revivalPacman(); 
				pacman->decreaselife();
			}
			else {
				init(renderer);
				back_to_menu = true;
			}

        }
        else objectTexture->renderPacmanTexture(renderer, pacman->getPosX(), pacman->getPosY(), TextureSrc::DEAD);
	}
	else {
		objectTexture->renderPacmanTexture(renderer, pacman->getPosX(), pacman->getPosY(), dir);
		renderGhost(renderer, blinky, TextureSrc::BLINKY);
		renderGhost(renderer, pinky, TextureSrc::PINKY);
		renderGhost(renderer, inky, TextureSrc::INKY);
		renderGhost(renderer, clyde, TextureSrc::CLYDE);
	}

	// Time
	std::string str_Time = "Time: ";
	Uint32 currentTime = tickManager->getTime() / 1000;
	Uint32 valTime = 300 - currentTime;
	if (valTime <= 0) {
		pacman->setDead(true);
	}
	else {
		str_Time = str_Time + std::to_string(valTime);
		Time->SetText(str_Time);
		Time->LoadFromRenderText(Time->fontTime, renderer);
		Time->RenderText(renderer, 13, 180);
	}
	// Point
	Point = map->coin *10;
	TextPoint->SetText("Point: " + std::to_string(Point));
	TextPoint->LoadFromRenderText(Time->fontTime, renderer);
	TextPoint->RenderText(renderer, 13, 162);

	//life 
	objectTexture->renderLifesPacman(pacman->getLife(), renderer);
	//foggy
	objectTexture->loadFoggyTexture(renderer);
	renderFoggy(pacman, renderer);
}

void Engine::loop() {
	//Mix_Chunk* eaten = Mix_LoadWAV("sound/eaten.wav");

	tickManager->updateStatus();

	if (pacman->isDead()) {
		return;
	}
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
	if (map->isBcoin(pacmanTileX, pacmanTileY)) {
		tickManager->setStatus(TickManager::FRIGHT_MODE);
		blinky->setFrighten(true); blinky->setDir((blinky->getGhostDir() + 2) % 4);
		pinky->setFrighten(true); pinky->setDir((pinky->getGhostDir() + 2) % 4);
		inky->setFrighten(true); inky->setDir((inky->getGhostDir() + 2) % 4);
		clyde->setFrighten(true); clyde->setDir((clyde->getGhostDir() + 2) % 4);

	}


	if (map->eatenCoins(pacmanTileX, pacmanTileY)) {
		//Mix_PlayChannel(-1, eaten, 0);
	}

	if (map->coin % 5 == 0) {
		map->randomBigCoin();
	}
	if (tickManager->getStatus() == TickManager::SCATTERING_MODE) {
		blinky->setScattering(true);
		pinky->setScattering(true);
		inky->setScattering(true);
		clyde->setScattering(true);
	}
	else {
		blinky->setScattering(false);
		pinky->setScattering(false);
		inky->setScattering(false);
		clyde->setScattering(false);
	}


	// Set up ghost target

	if (!pacman->isDead()) {

		// blinky
		if (blinky->isDead()) {
			blinky->setDestination(12, 11);
			
		}
		else if (blinky->isScattering()) {
			blinky->setDestination(Ghost::DEFAULT_BLINKY_TILE_X, Ghost::DEFAULT_BLINKY_TILE_Y);
		}
		else {
			blinky->setDestination(pacmanTileX, pacmanTileY);
		}

		// pinky
		if (pinky->isDead()) {
			pinky->setDestination(13, 11);
		}
		else if (pinky->isScattering()) {
			pinky->setDestination(Ghost::DEFAULT_PINKY_TILE_X, Ghost::DEFAULT_PINKY_TILE_Y);
		}
		else if (!pinky->isFrighten()) {
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
		// inky
		if (inky->isDead()) {
			inky->setDestination(14, 11);
		}
		else if (inky->isScattering()) {
			inky->setDestination(Ghost::DEFAULT_INKY_TILE_X, Ghost::DEFAULT_INKY_TILE_Y);
		}
		else if (!inky->isFrighten()) {
			inky->setDestination(2 * pacmanTileX - blinky->getNextTileX(), 2 * pacmanTileY - blinky->getTileY());
		}


		// clyde
		if (clyde->isDead()) {
			clyde->setDestination(15, 11);
		}
		else if (!clyde->isFrighten()) {
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

	PacmanCollisionGhost(blinky);
	PacmanCollisionGhost(pinky);
	PacmanCollisionGhost(inky);
	PacmanCollisionGhost(clyde);

	
}

void Engine::ghostMove(Ghost*& ghost) {
	int ghostTileX = ghost->getTileX();
	int ghostTileY = ghost->getTileY();
	int ghostPosX = ghost->getPosX();
	int ghostPosY = ghost->getPosY();
	int ghostOldDir = ghost->getGhostDir();
	int ghostNextTileX = ghost->getNextTileX();
	int ghostNextTileY = ghost->getNextTileY();
 	if (ghostTileX * 16 == ghostPosX && ghostTileY * 16 == ghostPosY) {
		if (map->iscrossRoad(ghostTileX, ghostTileY)) {
			if (ghost->isFrighten()) {
				int ghost_newdir = rand() % 4;
				while (ghost_newdir == ghostOldDir || !map->canChangeDir(ghostTileX, ghostTileY, ghost_newdir)) {
					ghost_newdir++;
				}
				ghost->setDir(ghost_newdir);

			}
			else {
				// bfs algorithm
				int UP_DIS = 100000;
				int DOWN_DIS = 100000;
				int LEFT_DIS = 100000;
				int RIGHT_DIS = 100000;
				//UP
				if (map->canChangeDir(ghostTileX, ghostTileY, Map::UP)) {
					UP_DIS = map->bfs(ghostTileX, ghostTileY, ghost->getDestination(), Map::UP);
					if (UP_DIS == 0) UP_DIS = 100000;
				}
				// DOWN
				if (map->canChangeDir(ghostTileX, ghostTileY, Map::DOWN)) {
					DOWN_DIS = map->bfs(ghostTileX, ghostTileY, ghost->getDestination(), Map::DOWN);
					if (DOWN_DIS == 0) DOWN_DIS = 10000;
				}
				// LEFT
				if (map->canChangeDir(ghostTileX, ghostTileY, Map::LEFT)) {
					LEFT_DIS = map->bfs(ghostTileX, ghostTileY, ghost->getDestination(), Map::LEFT);
					if (LEFT_DIS == 0) LEFT_DIS = 10000;
				}
				//RIGHT
				if (map->canChangeDir(ghostTileX, ghostTileY, Map::RIGHT)) {
					RIGHT_DIS = map->bfs(ghostTileX, ghostTileY, ghost->getDestination(), Map::RIGHT);
					if (RIGHT_DIS == 0) {
						RIGHT_DIS = 100000;
					}
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
			}
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
	// toi dich thi hoi sinh
	if (ghost->isDead() && ghostPosX == ghostNextTileX * 16 && ghostPosY == ghostNextTileY * 16) {
		ghost->setDead(false);
	}
}

void Engine::PacmanCollisionGhost(Ghost*& ghost) {
	if (ghost->isDead()) return;
		if ((pacman->getPosX() == ghost->getPosX() && pacman->getTileY() == ghost->getTileY()) ||
			(pacman->getPosY() == ghost->getPosY() && pacman->getTileX() == ghost->getTileX())) {
			if (ghost->isFrighten()) {

				ghost->setDead(true);
				ghost->setFrighten(false);
			}
			else {
				pacman->setDead(true);
			}
		}
}

void Engine::renderGhost(SDL_Renderer*& renderer, Ghost*& ghost, int ghostID) {
	if (ghost->isDead()) {
		objectTexture->renderGhostTexture(renderer, ghost->getPosX(), ghost->getPosY(), TextureSrc::GHOST_SPIRIT, ghost->getGhostDir());

	}
	else if(ghost->isFrighten()) {
		objectTexture->renderGhostTexture(renderer, ghost->getPosX(), ghost->getPosY(), ghostID, TextureSrc::FRIGHTEN);
	}
	else {
		objectTexture->renderGhostTexture(renderer, ghost->getPosX(), ghost->getPosY(), ghostID, ghost->getGhostDir());
	}
}

void Engine::renderFoggy(Pacman* pacman, SDL_Renderer*& renderer) {
	std::pair<std::pair<int, int>, int> pacmanTile = map->LoadFoggy(pacman);
	int tileX = pacmanTile.first.first;
	int tileY = pacmanTile.first.second;
	int range = pacmanTile.second;
	int lastDir = 0;
	int defaultSight = 2;
	if (map->isBcoin(pacman->getTileX(),pacman->getTileY())) {
		defaultSight = 4;
	}
	std::cout << defaultSight;
	if (!pacman->emptyDirStack()) lastDir = pacman->getDir();
	
	SDL_Rect dsRect;
	for (int i = 0; i < 28; ++i) {
		for (int j = 0; j < 31; ++j) {
			if (abs(i - tileX) <= defaultSight && abs(j - tileY) <= defaultSight || 
				( i >= 0 && i <= 5 && j >= 10 && j <= 12) ||
				(i >= 0 && i <= 5 && j >= 16 && j <= 17)
				) continue;

			else {
				if (lastDir == Map::UP) {
					if (0 <= (-tileY + j)&&(j - tileY ) <= range + 2 && abs (i - tileX )<= 2) {
						continue;
					}
				}
				else if (lastDir == Map::DOWN) {
					if (0 <= (tileY - j) &&(tileY - j) <= range + 2 && abs(i - tileX) <= 2) {
						continue;
					}
				}
				else if (lastDir == Map::LEFT) {
					if ( 0 <= (- tileX + i) &&(i - tileX) <= range + 2 && abs(j - tileY) <= 2) {
						continue;
					}
				}
				else if (lastDir == Map::RIGHT) {
					if (0 <= (tileX - i) && ( tileX - i) <= range + 2 && abs(j - tileY) <= 2) {
						continue;
					}
				}
			}
			
			dsRect = { i * 16, j * 16, 16, 16 };
			objectTexture->RenderFoggy(renderer, &dsRect);
		}
	}
}