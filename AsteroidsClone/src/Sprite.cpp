#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* renderer, int x, int y, int w, int h)
{
	m_Renderer = renderer;
	m_SpritePosition.x = x;
	m_SpritePosition.y = y;
	m_SpritePosition.w = w;
	m_SpritePosition.h = h;
	m_Rotation = 0.0f;
	m_Image = nullptr;
}

Sprite::Sprite(SDL_Renderer* renderer, char* file, int x, int y, int w, int h)
{
	SDL_Surface* bmpFile = SDL_LoadBMP(file);
	m_Image = SDL_CreateTextureFromSurface(renderer, bmpFile);
	SDL_FreeSurface(bmpFile);
	m_Rotation = 0.0f;
	// iniitial position & w/h of sprite, based in incoming parameters
	
	m_SpritePosition.x = x;
	m_SpritePosition.y = y;
	m_SpritePosition.w = w;
	m_SpritePosition.h = h;

	m_Renderer = renderer;
}

Sprite::~Sprite()
{
	if (m_Image)
		SDL_DestroyTexture(m_Image);
}

void Sprite::Draw()
{
	if (m_Image)
		SDL_RenderCopyEx(m_Renderer, m_Image, NULL, &m_SpritePosition, m_Rotation, NULL, SDL_FLIP_NONE);
}

bool Sprite::IsCollidingWith(Sprite* other)
{
	return SDL_HasIntersection(&m_SpritePosition, &other->GetRect());
}