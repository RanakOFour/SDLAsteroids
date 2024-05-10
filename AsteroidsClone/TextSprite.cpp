#include <SDL.h>
#include <SDL_ttf.h>
#include "TextSprite.h"


TextSprite::TextSprite(SDL_Renderer* renderer, char* fontFile, char* text, SDL_Color color, int x, int y, int w, int h, int textSize)
	: Sprite(renderer, x, y, w, h)
{
	m_Color = color;
	m_Text = text;
	m_TextSize = textSize;

	//Create font
	m_Font = TTF_OpenFont(fontFile, m_TextSize);
	
	//Make surface with font & text
	SDL_Surface* textSurface = TTF_RenderText_Solid(m_Font, m_Text.c_str(), m_Color);
	m_Image = SDL_CreateTextureFromSurface(m_Renderer, textSurface);
	SDL_FreeSurface(textSurface);
}

void TextSprite::ChangeText(const char* text)
 {
	m_Text = text;
	SDL_Surface* textSurface = TTF_RenderText_Solid(m_Font, m_Text.c_str(), m_Color);
	m_Image = SDL_CreateTextureFromSurface(m_Renderer, textSurface);
	SDL_FreeSurface(textSurface);
}