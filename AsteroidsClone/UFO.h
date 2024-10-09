#include "Spaceship.h"

#pragma once
#define H_UFO

class UFO : public Spaceship
{
private:
	bool m_ReachedPosition;
	Vector2 m_SelectedPosition;
public:
	UFO(std::vector<GameObject*>* objectsInScene, MusicPlayer* musicPlayer, SDL_Renderer* renderer, char* file, int x, int y, int w, int h);
	void PerFrame();
	void Move();
	int OnHit(char type);
};