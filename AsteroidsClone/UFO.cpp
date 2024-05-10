#include "UFO.h"
#include <random>

UFO::UFO(SDL_Renderer* renderer, char* file, int x, int y, int w, int h)
	: Spaceship(renderer, file, x, y, w, h, 1, 1000, 'U')
{
	m_ReachedPosition = true;
	m_SelectedPosition = Vector2(0, 0);
};

void UFO::Move()
{
	if (m_ReachedPosition)
	{
		//Select random position on the map
		m_SelectedPosition = Vector2(5 + (rand() % 1920), 5 + (rand() % 1080));

		//Distance from currentPosition to selected position
		Vector2 hereToThere = m_SelectedPosition - m_Position;

		//Travel to selectedPositon with a speed of 6
		m_Velocity = hereToThere.Normalized() * 6;
	}

	//Stores a float position to avoid losing resolution on sub 1.0f speeds
	m_Rotation += m_RotationSpeed;
	m_Position += m_Velocity;

	//Check for screen-wrapping
	if (m_Position.GetX() + (m_SpritePosition.w / 2) > 1920.0f)
	{
		m_Position.IncrementX(-1920.0f);
	}
	else if (m_Position.GetX() + (m_SpritePosition.w / 2) < 0.0f)
	{
		m_Position.IncrementX(1920.0f);
	}

	if (m_Position.GetY() + (m_SpritePosition.h / 2) < 0)
	{
		m_Position.IncrementY(1080.0f);
	}
	else if (m_Position.GetY() + (m_SpritePosition.h / 2) > 1080)
	{
		m_Position.IncrementY(-1080.0f);
	}

	m_SpritePosition.x = (int)m_Position.GetX();
	m_SpritePosition.y = (int)m_Position.GetY();
}

int UFO::OnHit(char type)
{
	switch (type)
	{
	case 'B':
		m_ToBeDeleted = true;
		return m_Points;

	case 'U':
	case 'A': 
		m_ToBeDeleted = true;
		break;
	}
	return 0;
}