#include "Spaceship.h"
#include "Player.h"


Player::Player(std::vector<GameObject*>* objectsInScene, MusicPlayer* musicPlayer, SDL_Renderer* renderer, char* file, int x, int y, int w, int h)
	: Spaceship(objectsInScene, musicPlayer, renderer, file, x, y, w, h, 3, 0, 'P')
{

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

	if (key[SDL_SCANCODE_SPACE] && m_CanShoot)
	{
		m_CanShoot = false;
		m_IsShooting = true;
		CreateBullet();
	}
}

void Player::PerFrame()
{
	HandleInput();
	Move();
}

int Player::OnHit(char type)
{
	switch (type)
	{
	case 'B':
		break;
	default:
		--m_Lives;
		m_ToBeDeleted = true;
	}
	return 0;
}