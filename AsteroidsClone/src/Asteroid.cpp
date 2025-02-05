#include <SDL.h>
#include "Asteroid.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Vector2.h"

Asteroid::Asteroid(SDL_Renderer* renderer, char* file, float x, float y, int w, int h, int pointsToGive, Vector2 parentSpeed) 
	: GameObject(renderer, file, x, y, w, h, pointsToGive, 'A', parentSpeed)
{
}

Asteroid::~Asteroid()
{
}

int Asteroid::OnHit(char type)
{
	switch (type)
	{
	case 'B':
		m_ToBeDeleted = true;
		return m_Points;
	}

	return 0;
}