#include "Animation.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>

Animation::Animation(SDL_Renderer* renderer, char* imageFile, char* soundFile, int frameCount, int frameW, int frameH, int totalFrameW, int totalFrameH)
{
	m_Renderer = renderer;
	SDL_Surface* bmpFile = SDL_LoadBMP(imageFile);
	m_SpriteSheet = SDL_CreateTextureFromSurface(m_Renderer, bmpFile);
	SDL_FreeSurface(bmpFile);
	m_SoundEffect = Mix_LoadMUS(soundFile);

	m_Frames = std::vector<SDL_Rect*>();
	for (int i = 0; i < totalFrameH; i += frameH)
	{
		for (int j = 0; j < totalFrameW; j += frameW)
		{
			SDL_Rect* frame = new SDL_Rect();
			frame->x = j;
			frame->y = i;
			frame->w = frameW;
			frame->h = frameH;
			m_Frames.push_back(frame);
		}
	}
	currentFrame = 0;

	m_SpritePosition = SDL_Rect();
	isOver = false;
}

void Animation::StartAnim(Vector2 position)
{
	m_SpritePosition.x = position.GetX();
	m_SpritePosition.y = position.GetY();
	m_SpritePosition.w = 150;
	m_SpritePosition.h = 150;
	
	SDL_RenderCopy(m_Renderer, m_SpriteSheet, m_Frames[currentFrame], &m_SpritePosition);
	Mix_PlayMusic(m_SoundEffect, 0);
	++currentFrame;
}

void Animation::NextFrame()
{
	if (currentFrame != m_Frames.size())
	{
		SDL_RenderCopy(m_Renderer, m_SpriteSheet, m_Frames[currentFrame], &m_SpritePosition);
		++currentFrame;
	}
	else
	{
		isOver = true;
	}
}