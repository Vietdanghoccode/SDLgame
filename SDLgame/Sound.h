#pragma
#include <SDL_mixer.h>
#include "iostream"
#include "LogStatus.h"
#include "string"



class Sound {
private:
	LogStatus* console;
public:
	Sound() {
		console = new LogStatus;
	}
	~Sound() {
		delete console;
		console = NULL;
	}
	bool Init();
	void Free();
};