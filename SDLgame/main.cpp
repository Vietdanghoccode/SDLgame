#include "RenderWindow.h"
#include "Entity.h"
#include <iostream>
#include <vector>
#include "utiliti.h"
#include "Map.h"
#include "Char.h"

//hieu ung nhan vat

//hieu ung dung yen

SDL_Rect gSpriteClips[] = {
(0,0,64,64), (64,0,64,64), (128,0,64,64),(192,0,64,64), (256,0,64,64), (320,0,64,64),(384,0,64,64)
};





SDL_Event event;

int main(int argc, char* argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO) > 0) {
		std::cout << "SDL_INIT FAILED..." << SDL_GetError() << std::endl;
	}

	if (!(IMG_Init(IMG_INIT_PNG))) {
		std::cout << "IMG_INIT has failed..." << SDL_GetError() << std::endl;
	}
	Tile* tileSet[TOTAL_TILES];

	RenderWindow window("SDL_game", 960, 540);

	// background
	SDL_Texture* background = window.loadTexture("gfx/background.png");
	SDL_Texture* Clip = window.loadTexture("gfx/thickldle.png");

	Entity bkground(Vector2f(0, 0), background, { 0,0,960,540 });
	



	
	int frame = 0;
	bool isrunning = true;
	SDL_Event event;

	while (isrunning)
	{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT) {
					isrunning = false;
				}
			}
		SDL_Rect currentClip = gSpriteClips[frame / 4];
		Entity spriteclip(Vector2f(0, 0), Clip, currentClip);
		
		window.clear();
		
		window.render(spriteclip);
		frame++;
		window.display();

	}

	window.cleanup();
	SDL_Quit();
	return 0;
}

