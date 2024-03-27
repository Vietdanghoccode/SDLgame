#include "RenderWindow.h"

RenderWindow::RenderWindow(const char* p_tittle, int p_w, int p_h) :window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_tittle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		std::cout << "Window failed to init, ..." << SDL_GetError() << std::endl;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED && SDL_RENDERER_PRESENTVSYNC);
}


SDL_Texture* RenderWindow::loadTexture(const char* p_filepath)
{
	SDL_Texture* optimizetexture = NULL;
	SDL_Texture* texture = IMG_LoadTexture(renderer, p_filepath);
	if (texture == NULL) {
		std::cout << "Can't load the texture..." << SDL_GetError() << std::endl;
	}

	return texture;
}


void RenderWindow::cleanup()
{
	SDL_DestroyWindow(window);
}
void RenderWindow::clear() {
	SDL_RenderClear(renderer);

}
void RenderWindow::render(Entity& p_entity) {
	SDL_Rect src; // source
	src.x = p_entity.getcurrentFrame().x;
	src.y = p_entity.getcurrentFrame().y;
	src.w = p_entity.getcurrentFrame().w;
	src.h = p_entity.getcurrentFrame().h;

	SDL_Rect dst;// destination
	dst.x = p_entity.getPos().x;
	dst.y = p_entity.getPos().y;
	dst.w = p_entity.getcurrentFrame().w;
	dst.h = p_entity.getcurrentFrame().h;


	SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

void RenderWindow::display() 
{
	SDL_RenderPresent(renderer);
}
SDL_Renderer* RenderWindow::getRenderer() {
	return renderer;
}
