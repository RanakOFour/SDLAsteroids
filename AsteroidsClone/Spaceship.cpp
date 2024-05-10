#include <SDL.h>
#include <math.h>
#include <iostream>
#include "Sprite.h"
#include "GameObject.h"
#include "Bullet.h"
#include "Spaceship.h"
#include "Vector2.h"

Spaceship::Spaceship(SDL_Renderer* renderer, char* file, int x, int y, int w, int h, int lives, int points, char type) :
	GameObject(renderer, file, (int)x, (int)y, w, h, points, type)
{
	m_Lives = lives;
	m_CanShoot = true;
	m_IsShooting = false;
}

void Spaceship::HandleInput()
{
	
}

GameObject* Spaceship::CreateBullet()
{
	m_IsShooting = false;
	//Calculate the correct position for the bullet (infront of the spaceship)
	float centreX = m_Position.GetX() + (m_SpritePosition.w / 2.0f) - 15.0f;
	float centreY = m_Position.GetY() + (m_SpritePosition.h / 2.0f) - 15.0f;
	float rotationRadians = m_Rotation * 0.01745329f;
	float sinRot = sinf(rotationRadians);
	float cosRot = cosf(-rotationRadians);

	float rotatedXRelativeToParent = (50.0f * sinRot);
	float rotatedYRelativeToParent = -(50.0f * cosRot);

	float adjustedX = rotatedXRelativeToParent + centreX;
	float adjustedY = rotatedYRelativeToParent + centreY;
	Bullet* toReturn = new Bullet(m_Renderer, (char*)"Assets/projectile.bmp", adjustedX, adjustedY, m_Rotation, 1000);
	toReturn->SetVelocity(0, 15);
	toReturn->Rotate(rotationRadians);
	return toReturn;
}

bool Spaceship::IsShooting()
{
	return m_IsShooting;
}

void Spaceship::SetShooting(bool canShoot)
{
	m_CanShoot = canShoot;
}

int Spaceship::GetLives()
{
	return m_Lives;
}

int Spaceship::OnHit(char type)
{
	return m_Points;
}