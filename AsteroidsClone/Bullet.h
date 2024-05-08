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
	Bullet(SDL_Renderer* _renderer, char* _file, float parentX, float parentY, float parentRotation, float maxDistance);
	~Bullet();
	void Move();
	int OnHit(char otherType);
};