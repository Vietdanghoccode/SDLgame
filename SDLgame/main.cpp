#include "Window.h"

int main(int arfc, char* argv[]) {
	Window* window = new Window();
	window->initSDL();
	window->runGame();
	window->quitSDL();
	return 0;
}