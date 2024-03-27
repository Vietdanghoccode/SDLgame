#include "Entity.h"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex, SDL_Rect p_currentFrame) : pos(p_pos), tex(p_tex), currentFrame(p_currentFrame)
{
	
}

Vector2f& Entity::getPos() {
	return pos;
}

SDL_Rect Entity::getcurrentFrame() {
	return currentFrame;
}

SDL_Texture* Entity::getTex() {
	return tex;
}
