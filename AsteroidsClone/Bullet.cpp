#include "Bullet.h"
#include "GameObject.h"

Bullet::Bullet(std::vector<GameObject*>* objectsInScene, MusicPlayer* musicPlayer, SDL_Renderer* renderer, char* file, float parentX, float parentY, float parentRotation, float maxDistance)
	: GameObject(objectsInScene, musicPlayer, renderer, file, parentX, parentY, 30, 30, 0, 'B')
{
	m_DistanceTravelled = 0;
	m_MaxDistance = maxDistance;
}

Bullet::~Bullet()
{
}

void Bullet::PerFrame()
{
	if (m_DistanceTravelled >= m_MaxDistance)
	{
		m_ToBeDeleted = true;
	}
	Move();

	//Tracks distance travelled so it can despawn after a certain amount of time (~67 frames)
	m_DistanceTravelled += m_Velocity.GetMagnitude();
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