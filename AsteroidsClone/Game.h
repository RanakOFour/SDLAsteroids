#include <SDL.h>
#include <vector>
#include "GameObject.h"

#pragma once
#define H_GAME

class Game
{
private:
	std::vector<GameObject*> m_gameObjects;
	int m_gameObjectSize;
	bool m_isGameOver;
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	int Initialise();

public:
	Game();
	~Game();
	void GameLoop();
};