#include <SDL.h>
#include <math.h>
#include <iostream>
#include "Sprite.h"
#include "GameObject.h"
#include "Bullet.h"
#include "Player.h"
#include "Vector2.h"

Player::Player(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h, int lives) :
	GameObject(_renderer, _file, (int)_x, (int)_y, _w, _h)
{
	m_Lives = lives;
	m_isShooting = false;
}

void Player::HandleInput()
{
	const Uint8* key = SDL_GetKeyboardState(NULL);

	float speedMagnitude = m_Velocity.GetMagnitude();

	//Rotation normally stored as degrees for SDL_RednerCopyEx
	float rotationInRadians = (m_Rotation * 0.01745329f);

	//Apply acceleration
	if (speedMagnitude < 10.0f)
	{
		if (key[SDL_SCANCODE_W])
		{
			m_Velocity += Vector2(0.5f * sinf(rotationInRadians), -(0.5f * cosf(rotationInRadians)));
		}
		else if (key[SDL_SCANCODE_S])
		{
			m_Velocity -= Vector2(0.4f * sinf(rotationInRadians), -(0.4f * cosf(rotationInRadians)));
		}
	}

	//Decelerate the player when keys are not pressed OR decelerate slightly so that player's current direction is accounted for in the next frame
	if ((speedMagnitude > 0.0f && !key[SDL_SCANCODE_W] && !key[SDL_SCANCODE_S]) || speedMagnitude > 9.8f)
	{
		if (fabs(speedMagnitude) < 0.3f)
		{
			m_Velocity.SetX(0.0f);
			m_Velocity.SetY(0.0f);
		}
		else
		{
			//Speed slowly decreases frame by frame
			m_Velocity *= 0.9f;
		}
	}

	//Apply rotation acceleration
	if (fabs(m_RotationSpeed) < 4.0f)
	{
		if (key[SDL_SCANCODE_A])
		{
			m_RotationSpeed -= 1.0f;
		}
		else if (key[SDL_SCANCODE_D])
		{
			m_RotationSpeed += 1.0f;
		}

		//flip rotation if too big
		if (m_Rotation > 360.0f)
		{
			m_Rotation -= 720.0f;
		}
		else if (m_Rotation < -360.0f)
		{
			m_Rotation += 720.0f;
		}
	}

	//Decelerate rotation when not pressing rotation keys
	if (fabs(m_RotationSpeed) > 0.0f && !key[SDL_SCANCODE_A] && !key[SDL_SCANCODE_D])
	{
		if (fabs(m_RotationSpeed) < 1.0f)
		{
			m_RotationSpeed = 0.0f;
		}
		else
		{
			//Rotation speed slowly decreases frame by frame
			m_RotationSpeed *= 0.8f;
		}
	}


	if (key[SDL_SCANCODE_SPACE] && (m_Bullet == nullptr || m_Bullet->GetDeleted()))
	{
		m_isShooting = true;
	}
}

GameObject* Player::CreateBullet(int index)
{
	m_isShooting = false;
	if (m_Bullet != nullptr)
	{
		delete m_Bullet;
	}
	//Calculate the correct position for the bullet (infront of the airplane)
	float centreX = m_Position.GetX() + (m_SpritePosition.w / 2.0f) - 15.0f;
	float centreY = m_Position.GetY() + (m_SpritePosition.h / 2.0f) - 15.0f;
	float rotationRadians = m_Rotation * 0.01745329f;
	float sinRot = sinf(rotationRadians);
	float cosRot = cosf(-rotationRadians);

	float rotatedXRelativeToParent = (50.0f * sinRot);
	float rotatedYRelativeToParent = -(50.0f * cosRot);

	float adjustedX = rotatedXRelativeToParent + centreX;
	float adjustedY = rotatedYRelativeToParent + centreY;
	m_Bullet = new Bullet(m_renderer, (char*)"Assets/projectile.bmp", adjustedX, adjustedY, m_Rotation, 1000);
	m_Bullet->SetVelocity(0, 15);
	m_Bullet->Rotate(rotationRadians);
	return m_Bullet;
}