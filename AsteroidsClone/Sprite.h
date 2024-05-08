#include <SDL.h>
#include <SDL_ttf.h>

#pragma once
#define H_SPRITE

class Sprite
{
protected:
	SDL_Renderer* m_Renderer;
	SDL_Texture* m_Image;
	SDL_Rect m_SpritePosition;
	float m_Rotation;

public:
	Sprite(SDL_Renderer* renderer, int x, int y, int w, int h);
	Sprite(SDL_Renderer* renderer, char* file, int x, int y, int w, int h);
	~Sprite();

	virtual void Draw();
	
	void SetX(int x) { m_SpritePosition.x = x; }
	void SetY(int y) { m_SpritePosition.y = y; }
	void SetRotation(float degrees) { m_Rotation = degrees; };

	int GetX() { return m_SpritePosition.x; }
	int GetY() { return m_SpritePosition.y; }
	int GetW() { return m_SpritePosition.w; }
	int GetH() { return m_SpritePosition.h; }
	SDL_Rect& GetRect() { return m_SpritePosition; }
	
	virtual bool IsCollidingWith(Sprite* other);
};
