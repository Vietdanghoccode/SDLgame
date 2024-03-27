#pragma once
#include "SDL.h"
#include <SDL_image.h>
#include "Math.h"

class Entity
{
public:
	Entity() {};
	Entity(Vector2f p_pos, SDL_Texture* p_tex, SDL_Rect p_currentFrame);
	Vector2f& getPos();
	SDL_Rect getcurrentFrame();
	SDL_Texture* getTex();
protected:
	Vector2f pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};