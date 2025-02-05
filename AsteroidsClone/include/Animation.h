#include <SDL.h>
#include <vector>
#include "Vector2.h"

#pragma once
#define H_ANIMATION

class Animation
{
private:
	SDL_Renderer* m_Renderer;
	SDL_Texture* m_SpriteSheet;
	SDL_Rect m_SpritePosition;
	std::vector<SDL_Rect*> m_Frames;
	int currentFrame;

public:
	bool isOver;
	Animation(SDL_Renderer* renderer, char* imageFile, int frameCount, int frameW, int frameH, int totalFrameW, int totalFrameH);
	void StartAnim(Vector2 position);
	void NextFrame();
};

