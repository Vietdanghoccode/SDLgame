
#include "RenderWindow.h"
#include "Entity.h"
#include <iostream>
#include <vector>
#include "utiliti.h"
#include "MainCharacter.h"
SDL_Event event;

int main(int argc, char* argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO) > 0) {
		std::cout << "SDL_INIT FAILED..." << SDL_GetError() << std::endl;
	}

	if (!(IMG_Init(IMG_INIT_PNG))) {
		std::cout << "IMG_INIT has failed..." << SDL_GetError() << std::endl;
	}


	RenderWindow window("SDL_game", 960, 540);


	SDL_Texture* grassTexture = window.loadTexture("gfx/ground_grass_1.png");
	SDL_Texture* foo = window.loadTexture("gfx/foo.png");

	std::vector <Entity> entities = { Entity(Vector2f(30,0), grassTexture)
						, Entity(Vector2f(30,30), grassTexture)
	};
	mainCharacter c(Vector2f(0, 30), foo);

	bool isrunning = true;
	SDL_Event event;
	const float timestep = 0.01f;
	float accumulator = 0.0f; // bo tich luy
	float currentTime = utils::hireTumeInSecond();

	while (isrunning)
	{
		//get fps
		int startTicks = SDL_GetTicks();
		float newTime = utils::hireTumeInSecond();
		float frameTime = newTime - currentTime;

		currentTime = newTime;
		accumulator += frameTime;
		while (accumulator >= timestep)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT) {
					isrunning = false;
				}
			}
			accumulator -= timestep;
			std::cout << utils::hireTumeInSecond() << std::endl;
		}

		const float alpha = accumulator / timestep; // 50%




		window.clear();
		for (Entity& e : entities) {
			window.render(e);
		}

		window.render(c);
		std::cout << utils::hireTumeInSecond() << std::endl;

		window.display();

		int frameTicks = SDL_GetTicks() - startTicks;
		if (frameTicks > window.getRefreshRate()) {
			SDL_Delay(window.getRefreshRate() - frameTicks);
		}

	}

	window.cleanup();
	SDL_Quit();
	return 0;
}
