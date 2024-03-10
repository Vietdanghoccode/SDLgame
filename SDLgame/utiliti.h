#pragma once
#include <SDL.h>

namespace utils // tien ich
{
	inline float hireTumeInSecond()
	{
		float t = SDL_GetTicks();
		t *= 0.001f;

		return t;
	}
}