#include "Sound.h"

bool Sound::Init() {
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
		console->Status("Can't init SDL_MIXER \n");
		return false;
	}
	return true;
}
void Sound::Free() {
	Mix_Quit();
}
