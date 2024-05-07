#include "GameObject.h"
#pragma once
#define H_ASTEROID

class Asteroid : public GameObject
{
private:
	GameObject* m_ExtraBullet;

public:
	Asteroid(SDL_Renderer* _renderer, char* _file, float _x, float _y, int _w, int _h);
	~Asteroid();
	GameObject* CreateBullet();
	void OnHit();
	GameObject* GetOtherBullet();
};
