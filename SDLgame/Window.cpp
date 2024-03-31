#include "Window.h"
#include "LogStatus.h"

Window::Window() {
	window = NULL;
	renderer = NULL;
	engine = NULL;

}

Window::~Window() {
	engine = nullptr;

	
	if (renderer != NULL) {
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}
	if (window != NULL) {
		SDL_DestroyWindow(window);
		window = NULL;
	}

}

void Window::initSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		Console->Status(SDL_GetError());
	}
	else {
		window = SDL_CreateWindow(WINDOW_TITTLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		Console->Status("Window opened successfully!");
		Running = true;

		if (window == nullptr) {
			Console->Status(SDL_GetError());
		}
		else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			Console->Status("Renderer created successfully!");
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear"); // phon to anh len ro hon
			SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT); // khong bien doi kich thuoc anh khi thay doi size window

		}

	}
}

void Window::quitSDL() {
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	atexit(SDL_Quit);
	return;
}
void Window::runGame() {

	SDL_Event e;
	engine = new Engine();
	engine->init(renderer);

	while (Running) {

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) Running = false;
			engine->handleEvent(e);

		}

		engine->loop();
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		SDL_RenderClear(renderer);

		engine->render(renderer);

		SDL_RenderPresent(renderer);

	}
}