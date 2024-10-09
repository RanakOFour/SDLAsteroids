#include "Spaceship.h"
#pragma once
#define H_PLAYER

class Player : public Spaceship
{

public:
	Player(std::vector<GameObject*>* objectsInScene, MusicPlayer* musicPlayer, SDL_Renderer* renderer, char* file, int x, int y, int w, int h);
	void HandleInput();
	void PerFrame();
	int OnHit(char type);
};