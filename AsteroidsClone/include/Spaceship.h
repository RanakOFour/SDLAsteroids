#include "GameObject.h"

#pragma once
#define H_SHIP

class Spaceship : public GameObject
{
protected:
	int m_Lives;
	bool m_IsShooting;
	bool m_CanShoot;

public:
	Spaceship(SDL_Renderer* renderer, char* file, int x, int y, int w, int h, int lives, int points, char type);
	virtual void HandleInput();
	GameObject* CreateBullet();
	bool IsShooting();
	void SetShooting(bool canShoot);
	int GetLives();
	int OnHit(char otherType);
};