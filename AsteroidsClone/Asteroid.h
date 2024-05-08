#include "GameObject.h"
#pragma once
#define H_ASTEROID

class Asteroid : public GameObject
{
public:
	Asteroid(SDL_Renderer* renderer, char* file, float x, float y, int w, int h, int points, Vector2 velocity);
	~Asteroid();
	int OnHit(char otherType);
};
