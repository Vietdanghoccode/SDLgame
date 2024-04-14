#include "TickManager.h"
#include <iostream>

TickManager::TickManager() {
	lastTick = 0;
	currentStatus = SCATTERING_MODE;
}

int TickManager::getStatus() {
	return currentStatus;

}
void TickManager::setStatus(int status) {
	currentStatus = status;
	lastTick = SDL_GetTicks();

}

void TickManager::resetTick() {
	lastTick = SDL_GetTicks();
}

void TickManager::updateStatus() {
	int timePass = (SDL_GetTicks() - lastTick) / 1000;

	if (currentStatus == SCATTERING_MODE && timePass == 7) {
		currentStatus = CHASING_MODE;
	}
	else if (currentStatus = CHASING_MODE && timePass == 20) {
		currentStatus = SCATTERING_MODE;
		resetTick();
	}
	else if (currentStatus == FRIGHT_MODE && timePass == 5) {
		currentStatus = SCATTERING_MODE;
		resetTick();
	}
}