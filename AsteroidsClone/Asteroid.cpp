#include <SDL.h>
#include "Asteroid.h"
#include "GameObject.h"

Asteroid::Asteroid(SDL_Renderer* _renderer, char* _file, float _x, float _y, int _w, int _h) 
	: GameObject(_renderer, _file, _x, _y, _w, _h)
{

}

Asteroid::~Asteroid()
{
	delete m_Bullet;
	delete m_ExtraBullet;
}

GameObject* Asteroid::CreateBullet()
{

}