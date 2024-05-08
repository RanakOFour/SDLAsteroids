#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Sprite.h"
#pragma once
#define H_TEXTSPRITE

class TextSprite : public Sprite
{
private:
	TTF_Font* m_Font;
	SDL_Color m_Color;
	std::string m_Text;
	int m_TextSize;

public:
	TextSprite(SDL_Renderer* renderer, char* fontFile, char* text, SDL_Color color, int x, int y, int w, int h, int textSize);
	void ChangeText(const char* newText);
};