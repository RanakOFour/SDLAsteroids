#pragma once
#define H_SPRITE

#include <SDL.h>

class Sprite
{
protected:
	SDL_Renderer* m_renderer;
	SDL_Texture* m_image;
	SDL_Rect m_SpritePosition;
	float m_Rotation;

public:
	Sprite(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h);
	~Sprite();

	virtual void Draw();
	
	// setters
	void SetX(int _x) { m_SpritePosition.x = _x; }
	void SetY(int _y) { m_SpritePosition.y = _y; }

	// getters
	int GetX() { return m_SpritePosition.x; }
	int GetY() { return m_SpritePosition.y; }
	int GetW() { return m_SpritePosition.w; }
	int GetH() { return m_SpritePosition.h; }
	SDL_Rect& GetRect() { return m_SpritePosition; }
	
	virtual bool IsCollidingWith(Sprite* other);
};
