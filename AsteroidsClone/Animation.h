#include <SDL.h>
#include <SDL_mixer.h>
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
	Mix_Music* m_SoundEffect;
	int currentFrame;

public:
	bool isOver;
	Animation(SDL_Renderer* renderer, char* imageFile, char* soundFile, int frameCount, int frameW, int frameH, int totalFrameW, int totalFrameH);
	void StartAnim(Vector2 position);
	void NextFrame();
};