#include <SDL.h>
#include "Sprite.h"
#include "Vector2.h"
#pragma once
#define H_GAMEOBJECT

class GameObject : public Sprite
{
protected:
	Vector2 m_Velocity;
	Vector2 m_Position;
	float m_RotationSpeed;
	char m_Type;
	bool m_ToBeDeleted;
	int m_Points;

public:
	GameObject(SDL_Renderer* renderer, char* file, float x, float y, int w, int h, int points, char type);
	GameObject(SDL_Renderer* renderer, char* file, float x, float y, int w, int h, int points, char type, Vector2 velocity);
	~GameObject();

	virtual void Move();
	void SetVelocity(float x, float y);
	void SetVelocity(Vector2 newVelocity);
	Vector2 GetVelocity();
	void SetPosition(float x, float y);
	Vector2 GetPosition();
	void Rotate(float radians);
	void SetDeleted(bool del);
	bool GetDeleted();
	int GetPoints();
	char GetType();
	virtual int OnHit(char otherType);
};