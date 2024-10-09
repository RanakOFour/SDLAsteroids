#include <SDL.h>
#include <vector>
#include "Asteroid.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Vector2.h"

Asteroid::Asteroid(std::vector<GameObject*>* objectsInScene, MusicPlayer* musicPlayer, SDL_Renderer* renderer, char* file, float x, float y, int w, int h, int pointsToGive, Vector2 parentSpeed)
	: GameObject(objectsInScene, musicPlayer, renderer, file, x, y, w, h, pointsToGive, 'A', parentSpeed)
{
}

Asteroid::~Asteroid()
{
}

void Asteroid::OnDeath()
{
	if (m_SpritePosition.w > 50)
	{
		//Create 2 asteroids rotated by PI/6 and moving away from eachother
		Asteroid* newAsteroid1 = new Asteroid(m_ObjectsInScene, m_musicPlayer, m_Renderer, (char*)"Assets/asteroid.bmp", m_SpritePosition.x + (m_SpritePosition.w * 0.5f), m_SpritePosition.y, m_SpritePosition.w * 0.5f, m_SpritePosition.h * 0.5f, m_Points * 4, m_Velocity);
		newAsteroid1->Rotate(0.5235988f);
		m_ObjectsInScene->push_back(newAsteroid1);

		newAsteroid1 = new Asteroid(m_ObjectsInScene, m_musicPlayer, m_Renderer, (char*)"Assets/asteroid.bmp", m_SpritePosition.x - (m_SpritePosition.w * 0.5f), m_SpritePosition.y, m_SpritePosition.w * 0.5f, m_SpritePosition.h * 0.5f, m_Points * 4, m_Velocity);
		newAsteroid1->Rotate(-0.5235988f);
		m_ObjectsInScene->push_back(newAsteroid1);
	}
}

void Asteroid::PerFrame()
{
	Move();
}

int Asteroid::OnHit(char type)
{
	switch (type)
	{
	case 'B':
		OnDeath();
		m_ToBeDeleted = true;
		return m_Points;
	}

	return 0;
}