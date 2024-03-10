#pragma once
#include "SDL.h"
#include <SDL_image.h>
#include "Math.h"

class Entity
{
public:
	Entity() {};
	Entity(Vector2f p_pos, SDL_Texture* p_tex);
	Vector2f& getPos();
	
	SDL_Texture* getTex();
	SDL_Rect getcurrentFrame();
protected:
	Vector2f pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};