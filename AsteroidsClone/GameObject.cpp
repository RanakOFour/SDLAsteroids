#include <iostream>
#include <math.h>
#include "Vector2.h"
#include "GameObject.h"
#include "Bullet.h"

GameObject::GameObject(std::vector<GameObject*>* objectsInScene, MusicPlayer* musicPlayer, SDL_Renderer* renderer, char* file, float x, float y, int w, int h, int points, char type) :
	Sprite(renderer, file, (int)x, (int)y, w, h)
{
	m_ObjectsInScene = objectsInScene;
	m_musicPlayer = musicPlayer;
	m_Velocity = Vector2(0.0f, 0.0f);
	m_Position = Vector2(x, y);
	m_RotationSpeed = 0.0f;
	m_ToBeDeleted = false;
	m_Points = points;
	m_Type = type;
};

GameObject::GameObject(std::vector<GameObject*>* objectsInScene, MusicPlayer* musicPlayer, SDL_Renderer* renderer, char* file, float x, float y, int w, int h, int points, char type, Vector2 parentVelocity) :
	Sprite(renderer, file, (int)x, (int)y, w, h)
{
	m_ObjectsInScene = objectsInScene;
	m_musicPlayer = musicPlayer;
	m_Velocity = parentVelocity;
	m_Position = Vector2(x, y);
	m_RotationSpeed = 0.0f;
	m_ToBeDeleted = false;
	m_Points = points;
	m_Type = type;
	m_Rotation = (int)parentVelocity.GetMagnitude();

};

GameObject::~GameObject()
{}

void GameObject::PerFrame()
{
	Move();
}

void GameObject::Move()
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
}

int GameObject::OnHit(char type)
{
	m_ToBeDeleted = true;
	return m_Points;
}

void GameObject::Rotate(float radians)
{
	float xForY = m_Velocity.GetX();
	m_Velocity.SetX(-((m_Velocity.GetX() * cosf(radians)) - (m_Velocity.GetY() * sinf(-radians))));
	m_Velocity.SetY((xForY * sinf(radians)) + (m_Velocity.GetY() * cosf(-radians)));
}

void GameObject::SetVelocity(float x, float y)
{
	m_Velocity.SetX(x);
	m_Velocity.SetY(-y);
}

void GameObject::SetVelocity(Vector2 newVelocity)
{
	m_Velocity = newVelocity;
}

Vector2 GameObject::GetVelocity()
{
	return m_Velocity;
}

void GameObject::SetPosition(float x, float y)
{
	m_Position = Vector2(x, y);
}

Vector2 GameObject::GetPosition()
{
	return m_Position;
}

void GameObject::SetDeleted(bool del)
{
	m_ToBeDeleted = false;
}

bool GameObject::GetDeleted()
{
	return m_ToBeDeleted;
}

int GameObject::GetPoints()
{
	return m_Points;
}

char GameObject::GetType()
{
	return m_Type;
}