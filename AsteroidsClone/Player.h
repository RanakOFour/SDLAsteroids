#include "GameObject.h"
#pragma once
#define H_PLAYER

class Player : public GameObject
{
private:
	int m_Lives;

public:
	Player(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h, int lives);
	void HandleInput();
	GameObject* CreateBullet(int index);
	int GetLives();
};