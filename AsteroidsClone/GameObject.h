#include <SDL.h>
#include "Sprite.h"
#include "Vector2.h"
#pragma once
#define H_GAMEOBJECT

class GameObject : public Sprite
{
protected:
	GameObject* m_Bullet;
	Vector2 m_Velocity;
	Vector2 m_Position;
	float m_RotationSpeed;
	bool m_isShooting;
	bool m_toBeDeleted;

public:
	GameObject(SDL_Renderer* _renderer, char* _file, float _x, float _y, int _w, int _h);
	~GameObject();

	virtual void Move();
	void SetVelocity(float x, float y);
	void Rotate(float radians);
	bool IsShooting();
	bool GetDeleted();
	virtual GameObject* CreateBullet();
	GameObject* GetBullet();
};