#include <SDL.h>
#include <string>
#include "GameObject.h"
#pragma once
#define H_BULLET

class Bullet : public GameObject
{
protected:
	float m_DistanceTravelled;
	float m_MaxDistance;

public:
	Bullet(std::vector<GameObject*>* objectsInScene, MusicPlayer* musicPlayer, SDL_Renderer* _renderer, char* _file, float parentX, float parentY, float parentRotation, float maxDistance);
	~Bullet();
	void PerFrame();
	int OnHit(char otherType);
};