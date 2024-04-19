#include "TextureSrc.h"


TextureSrc::TextureSrc() {
	tileTexture = NULL;
	pacmanTexture = NULL;
    ghostTexture = NULL;
    for (int i = 0; i < 5; ++i) ghostFrame[i] = 0;
}

TextureSrc::~TextureSrc() {
	SDL_DestroyTexture(tileTexture);
	tileTexture = NULL;
	SDL_DestroyTexture(pacmanTexture);
	pacmanTexture = NULL;
    SDL_DestroyTexture(ghostTexture);
    ghostTexture = NULL;
    for (int i = 0; i < 5; i++) {
        ghostFrame[i] = 0;
    }
}

bool TextureSrc::pacmanIsDead() {
    if (pacmanFrame == 110) {
        pacmanFrame = 0;
        return true;
    }  
    return false;
}
void TextureSrc::loadTileTexture(SDL_Renderer*& renderer) {
	SDL_Surface* Image = IMG_Load("gfx/Pacman Tile Labyrinth.png");
	if (Image == NULL) {
		Console->Status(IMG_GetError());

	}
	else {
		tileTexture = SDL_CreateTextureFromSurface(renderer, Image);

		int x = 0, y = 0;
		for (int i = 0; i < 32; ++i) {
			tileSprite[i] = { x, y, 16, 16 };
			y += 17;
			if (i % 4 == 3) x += 17, y = 0;
		}

		Console->Status("Tile texture got successfully");
	}

	SDL_FreeSurface(Image);
	Image = NULL;
}

void TextureSrc::renderTileTexture(SDL_Renderer*& renderer, int tileID, SDL_Rect* dsRect) {
	SDL_RenderCopy(renderer, tileTexture, &tileSprite[tileID], dsRect);
}

void TextureSrc::loadPacmanAndGhostTexture(SDL_Renderer*& renderer) {
    SDL_Surface* Image = IMG_Load("gfx/Pacman and Ghost Texture.png");

    if (Image == nullptr) {
        Console->Status(IMG_GetError());
    }
    else {
        pacmanTexture = SDL_CreateTextureFromSurface(renderer, Image);

        ghostTexture = pacmanTexture;

        int posTexX = 0, posTexY = 0;
        /// Pacman goes up
        for (int i = 0; i < 3; ++i) pacmanUP[i] = { posTexX, posTexY, 30, 30 }, posTexX += 31;
        /// Pacman goes down
        for (int i = 3; i < 6; ++i) pacmanDOWN[i % 3] = { posTexX, posTexY, 30, 30 }, posTexX += 31;
        /// Pacman goes left
        for (int i = 6; i < 9; ++i) pacmanLEFT[i % 3] = { posTexX, posTexY, 30, 30 }, posTexX += 31;
        /// Pacman goes right
        for (int i = 9; i < 12; ++i) pacmanRIGHT [i % 3] = { posTexX, posTexY, 30, 30 }, posTexX += 31;
        /// Pacman dead
        posTexX = 0;
        for (int i = 0; i < 11; ++i) pacmanDEAD[i] = { posTexX, 155, 30, 30 }, posTexX += 31;

        Console->Status("Pacman got successfully!");
        /// Ghost setup
        posTexX = 0; posTexY = 31;
        for (int i = 0; i < TOTAL_GHOST -1; ++i) {
            ghost[i][UP][0] = { posTexX, posTexY, 30, 30 }; posTexX += 31;
            ghost[i][UP][1] = { posTexX, posTexY, 30, 30 }; posTexX += 31;
            ghost[i][DOWN][0] = { posTexX, posTexY, 30, 30 }; posTexX += 31;
            ghost[i][DOWN][1] = { posTexX, posTexY, 30, 30 }; posTexX += 31;
            ghost[i][LEFT][0] = { posTexX, posTexY, 30, 30 }; posTexX += 31;
            ghost[i][LEFT][1] = { posTexX, posTexY, 30, 30 }; posTexX += 31;
            ghost[i][RIGHT][0] = { posTexX, posTexY, 30, 30 }; posTexX += 31;
            ghost[i][RIGHT][1] = { posTexX, posTexY, 30, 30 }; posTexX += 31;
            ghost[i][FRIGHTEN][0] = { posTexX, 31, 30, 30 }; posTexX += 31;
            ghost[i][FRIGHTEN][1] = { posTexX, 31, 30, 30 };
            posTexX = 0;
            posTexY += 31;
        }
        posTexX = 248; posTexY = 62;
        ghost[GHOST_SPIRIT][UP][0] = { posTexX, posTexY, 30, 30 };
        ghost[GHOST_SPIRIT][UP][1] = { posTexX, posTexY, 30, 30 }; posTexX += 31;
        ghost[GHOST_SPIRIT][DOWN][0] = { posTexX, posTexY, 30, 30 };
        ghost[GHOST_SPIRIT][DOWN][1] = { posTexX, posTexY, 30, 30 }; posTexX = 248; posTexY += 31;
        ghost[GHOST_SPIRIT][LEFT][0] = { posTexX, posTexY, 30, 30 };
        ghost[GHOST_SPIRIT][LEFT][1] = { posTexX, posTexY, 30, 30 }; posTexX += 31;
        ghost[GHOST_SPIRIT][RIGHT][0] = { posTexX, posTexY, 30, 30 };
        ghost[GHOST_SPIRIT][RIGHT][1] = { posTexX, posTexY, 30, 30 };
        

        Console->Status("Ghost Texture got successfully!");
    }
    SDL_FreeSurface(Image);
    Image = nullptr;
}

void TextureSrc::renderPacmanTexture(SDL_Renderer*& renderer, int posX, int posY, int status) {
    SDL_Rect srcRect, dsRect;
    dsRect = { posX - 7, posY - 7, 30, 30 };
    ++pacmanFrame;
    if (status != DEAD && pacmanFrame == 30) pacmanFrame = 0;
    int frame = pacmanFrame / 10;
    switch (status) {
    case 0: srcRect = pacmanUP[0]; break;
    case UP:    srcRect = pacmanUP[frame]; break;
    case RIGHT: srcRect = pacmanRIGHT[frame]; break;
    case DOWN:  srcRect = pacmanDOWN[frame]; break;
    case LEFT:  srcRect = pacmanLEFT[frame]; break;
    case DEAD: srcRect = pacmanDEAD[frame]; break;
    }

    SDL_RenderCopy(renderer, pacmanTexture, &srcRect, &dsRect);
}


void TextureSrc::renderGhostTexture(SDL_Renderer*& renderer, int posX, int posY, int ghostID, int status) {
    SDL_Rect srcRect, dsRect;
    dsRect = { posX - 7, posY - 7, 30, 30 };
    ghostFrame[ghostID] ++;
    if (ghostFrame[ghostID] == 14) ghostFrame[ghostID] = 0;
    int frame = ghostFrame[ghostID] / 7;


    switch (status) {
    case 0: srcRect = ghost[ghostID][UP][frame]; break;
    case UP:    srcRect = ghost[ghostID][UP][frame]; break;
    case RIGHT: srcRect = ghost[ghostID][RIGHT][frame]; break;
    case DOWN:  srcRect = ghost[ghostID][DOWN][frame]; break;
    case LEFT:  srcRect = ghost[ghostID][LEFT][frame]; break;
    case FRIGHTEN: srcRect = ghost[ghostID][FRIGHTEN][frame]; break;
    }

    SDL_RenderCopy(renderer, ghostTexture, &srcRect, &dsRect);
}

void TextureSrc::renderLifesPacman(int i, SDL_Renderer*& renderer) {
    SDL_Rect lifes[3];
    for (int j = 0; j < i; j++) {
        lifes[j].x = j * 20+ 10;
        lifes[j].y = 260;
        lifes[j].w = 20;
        lifes[j].h = 20;
    }
    for (int j = 0; j < i; j++) {
        SDL_RenderCopy(renderer, pacmanTexture, &pacmanRIGHT[1], &lifes[j]);
    }
}


