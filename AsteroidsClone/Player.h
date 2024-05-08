#include "GameObject.h"
#pragma once
#define H_PLAYER

class Player : public GameObject
{
private:
	int m_Lives;
	bool m_IsShooting;
	bool m_CanShoot;

public:
	Player(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h, int lives);
	void HandleInput();
	GameObject* CreateBullet();
	bool IsShooting();
	void SetShooting(bool canShoot);
	int GetLives();
	int OnHit(char otherType);
};