#include <iostream>
#include <math.h>
#include "Vector2.h"
#include "GameObject.h"
#include "Bullet.h"

GameObject::GameObject(SDL_Renderer* _renderer, char* _file, float _x, float _y, int _w, int _h) :
	Sprite(_renderer, _file, (int)_x, (int)_y, _w, _h)
{
	m_Bullet = nullptr;
	m_Velocity = Vector2(0.0f, 0.0f);
	m_Position = Vector2(_x, _y);
	m_RotationSpeed = 0.0f;
	m_isShooting = false;
	m_toBeDeleted = false;
};

GameObject::~GameObject()
{}

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

void GameObject::SetVelocity(float x, float y)
{
	m_Velocity.SetX(x);
	m_Velocity.SetY(-y);
}

void GameObject::Rotate(float radians)
{
	float xForY = m_Velocity.GetX();
	m_Velocity.SetX(-((m_Velocity.GetX() * cosf(radians)) - (m_Velocity.GetY() * sinf(-radians))));
	m_Velocity.SetY((xForY * sinf(radians)) + (m_Velocity.GetY() * cosf(-radians)));
}

bool GameObject::IsShooting()
{
	return m_isShooting;
}

bool GameObject::GetDeleted()
{
	return m_toBeDeleted;
}

GameObject* GameObject::CreateBullet()
{
	return nullptr;
}

GameObject* GameObject::GetBullet()
{
	return m_Bullet;
}