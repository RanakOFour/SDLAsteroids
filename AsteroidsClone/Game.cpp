#include <SDL.h>
#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Game.h"
#include "Player.h"

Game::Game()
{
	m_gameObjects = std::vector<GameObject*>();
	m_gameObjectSize = 0;
	Initialise();
}

Game::~Game()
{
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

int Game::Initialise()
{
	//SDL_Init and SDL_PollEvents have to be contained within the same thread to work properly
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
		system("pause");
		return -1;
	}

	m_Window = SDL_CreateWindow("Asteroids", 0, 0, 1920, 1080, SDL_WINDOW_SHOWN);
	if (m_Window == nullptr)
	{
		std::cout << "Failed to create window : " << SDL_GetError();
		system("pause");
		return -2;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, 0, SDL_RENDERER_ACCELERATED);
	if (m_Renderer == nullptr)
	{
		std::cout << "Failed to create renderer : " << SDL_GetError();
		system("pause");
		return -3;
	}

	return 0;
}

void Game::GameLoop()
{
	Uint64 totalFrames{ 0 };
	bool exit{ false };
	SDL_Event e;

	float frameTime = 16.666f;
	Sprite* bkgd = new Sprite(m_Renderer, (char*)"Assets/bkgd.bmp", 0, 0, 1920, 1080);
	Player* player = new Player(m_Renderer, (char*)"Assets/ship.bmp", 1000, 1000, 150, 150, 3);
	m_gameObjects.push_back(player);
	++m_gameObjectSize;

	while (!exit)
	{
		totalFrames++;

		Uint64 startPerf = SDL_GetPerformanceCounter();

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				exit = true;
			}
		}

		SDL_RenderClear(m_Renderer);
		bkgd->Draw();

		player->HandleInput();
		if (player->IsShooting() && (player->GetBullet() == nullptr || player->GetBullet()->GetDeleted()))
		{
			m_gameObjects.push_back(player->CreateBullet(m_gameObjectSize));
			++m_gameObjectSize;
		}

		for (int i = 0; i < m_gameObjectSize; i++)
		{
			m_gameObjects[i]->Move();
			for (int j = 0; j < m_gameObjectSize; j++)
			{
				m_gameObjects[i]->IsCollidingWith(m_gameObjects[j]);
			}

			if (m_gameObjects[i]->GetDeleted())
			{
				m_gameObjects.erase(m_gameObjects.begin() + i);
				--m_gameObjectSize;
			}
			else
			{
				m_gameObjects[i]->Draw();
			}
		}
		SDL_RenderPresent(m_Renderer);

		float elapsedMS = (((float)(SDL_GetPerformanceCounter() - startPerf) / (float)SDL_GetPerformanceFrequency()) * 1000.0f);
		std::cout << elapsedMS << ", " << totalFrames << std::endl;

		if (elapsedMS < frameTime)
		{
			SDL_Delay((Uint32)(16.666f - elapsedMS));
		}
	}
}