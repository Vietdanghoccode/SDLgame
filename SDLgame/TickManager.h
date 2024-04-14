#pragma once

#include <SDL.h>

class TickManager {
private:
	Uint32 lastTick;

	int currentStatus;
public:
	static const int FRIGHT_MODE = 0;
	static const int SCATTERING_MODE = 1; // tan bien
	static const int CHASING_MODE = 2; // tham do

	TickManager();

	int getStatus();

	void setStatus(int status);

	Uint32 getTime();

	void resetTick();

	void updateStatus();
};