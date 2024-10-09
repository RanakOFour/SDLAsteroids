#include "GameObject.h"
#pragma once
#define H_ASTEROID

class Asteroid : public GameObject
{
private:
	void OnDeath();
public:
	Asteroid(std::vector<GameObject*> *objectsInScene, MusicPlayer* musicPlayer, SDL_Renderer* renderer, char* file, float x, float y, int w, int h, int points, Vector2 velocity);
	~Asteroid();
	void PerFrame();
	int OnHit(char otherType);
};
