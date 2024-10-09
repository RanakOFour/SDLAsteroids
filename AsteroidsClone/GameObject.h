#include <SDL.h>
#include <vector>
#include "Sprite.h"
#include "Vector2.h"
#include "MusicPlayer.h"
#pragma once
#define H_GAMEOBJECT

class GameObject : public Sprite
{
protected:
	std::vector<GameObject*> *m_ObjectsInScene;
	MusicPlayer* m_musicPlayer;
	Vector2 m_Velocity;
	Vector2 m_Position;
	float m_RotationSpeed;
	char m_Type;
	bool m_ToBeDeleted;
	int m_Points;

public:
	GameObject(std::vector<GameObject*>* objectsInScene, MusicPlayer* musicPlayer, SDL_Renderer* renderer, char* file, float x, float y, int w, int h, int points, char type);
	GameObject(std::vector<GameObject*>* objectsInScene, MusicPlayer* musicPlayer, SDL_Renderer* renderer, char* file, float x, float y, int w, int h, int points, char type, Vector2 velocity);
	~GameObject();

	virtual void PerFrame();
	virtual void Move();
	virtual int OnHit(char otherType);
	void Rotate(float radians);

	//Getters & setters
	void SetVelocity(float x, float y);
	void SetVelocity(Vector2 newVelocity);
	Vector2 GetVelocity();
	void SetPosition(float x, float y);
	Vector2 GetPosition();
	void SetDeleted(bool del);
	bool GetDeleted();
	int GetPoints();
	char GetType();
};