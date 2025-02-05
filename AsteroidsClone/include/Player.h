#include "Spaceship.h"
#pragma once
#define H_PLAYER

class Player : public Spaceship
{

public:
	Player(SDL_Renderer* renderer, char* file, int x, int y, int w, int h);
	void HandleInput();
	int OnHit(char type);
};