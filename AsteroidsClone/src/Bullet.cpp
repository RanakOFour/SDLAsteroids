#include "Bullet.h"
#include "GameObject.h"

Bullet::Bullet(SDL_Renderer* renderer, char* file, float parentX, float parentY, float parentRotation, float maxDistance)
	: GameObject(renderer, file, parentX, parentY, 30, 30, 0, 'B')
{
	m_DistanceTravelled = 0;
	m_MaxDistance = maxDistance;
}

Bullet::~Bullet()
{
}

void Bullet::Move()
{
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


	//Tracks distance travelled so it can despawn after a certain amount of time (~67 frames)
	m_DistanceTravelled += m_Velocity.GetMagnitude();
	if (m_DistanceTravelled >= m_MaxDistance)
	{
		m_ToBeDeleted = true;
	}
}

int Bullet::OnHit(char type)
{
	switch (type)
	{
	case 'A':
	case 'U':
		m_ToBeDeleted = true;
	}
	return 0;
}