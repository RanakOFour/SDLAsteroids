#include <SDL.h>
#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h)
{
	SDL_Surface* bmpFile = SDL_LoadBMP(_file);
	m_image = SDL_CreateTextureFromSurface(_renderer, bmpFile);
	SDL_FreeSurface(bmpFile);
	m_Rotation = 0.0f;
	// iniitial position & w/h of sprite, based in incoming parameters
	
	m_SpritePosition.x = _x;
	m_SpritePosition.y = _y;
	m_SpritePosition.w = _w;
	m_SpritePosition.h = _h;

	m_renderer = _renderer;
}

Sprite::~Sprite()
{
	if (m_image)
		SDL_DestroyTexture(m_image);
}

void Sprite::Draw()
{
	if (m_image)
		SDL_RenderCopyEx(m_renderer, m_image, NULL, &m_SpritePosition, m_Rotation, NULL, SDL_FLIP_NONE);
}

bool Sprite::IsCollidingWith(Sprite* other)
{
	return SDL_HasIntersection(&m_SpritePosition, &other->GetRect());
}