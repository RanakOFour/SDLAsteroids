#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "Game.h"
#include "Sprite.h"
#include "TextSprite.h"
#include "Asteroid.h"
#include "Player.h"
#include "Animation.h"

Game::Game()
{
	m_GameObjects = std::vector<GameObject*>();
	m_ObjectsInScene = 0;
	m_PlayerScore = 0;
	m_Color = SDL_Color();
	m_Color.r = 255; m_Color.b = 255; m_Color.g = 255; m_Color.a = 0;

	Initialise();

	m_Background = new Sprite(m_Renderer, (char*)"Assets/bkgd.bmp", 0, 0, 1920, 1080);
	m_ScoreText = new TextSprite(m_Renderer, (char*)"Assets/comicsans.ttf", (char*)"Score: 0", m_Color, 0, 0, 480, 200, 60);
	m_LivesText = new TextSprite(m_Renderer, (char*)"Assets/comicsans.ttf", (char*)"Lives: 3", m_Color, 0, 200, 160, 100, 48);
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

	m_Window = SDL_CreateWindow("Asteroidz", 0, 0, 1920, 1080, SDL_WINDOW_SHOWN);
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

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << ("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return -4;
	}

	if (TTF_Init() == -1)
	{
		std::cout << "Could not initialise text: " << TTF_GetError();
		return -5;
	}

	return 0;
}

bool Game::MenuLoop()
{
	bool exit{ false };
	SDL_Event e;
	TextSprite* nameText = new TextSprite(m_Renderer, (char*)"Assets/comicsans.ttf", (char*)"Asteroidz", m_Color, 480, 50, 960, 360, 72);
	Sprite* startGame = new Sprite(m_Renderer, (char*)"Assets/startButton.bmp", 300, 700, 400, 200);
	Sprite* quitGame = new Sprite(m_Renderer, (char*)"Assets/quitButton.bmp", 1200, 700, 400, 200);

	//Draw the menu once, because it's static
	SDL_RenderClear(m_Renderer);
	m_Background->Draw();
	nameText->Draw();
	startGame->Draw();
	quitGame->Draw();
	SDL_RenderPresent(m_Renderer);

	while (!m_IsGameOver)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				m_IsGameOver = true;
			}
			else if (e.type = SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					int x, y;
					Uint32 buttons = SDL_GetMouseState(&x, &y);

					//Use sprite collision to figure out where the mouse is
					Sprite buttonPress = Sprite(m_Renderer, (char*)"", x, y, 1, 1);
					buttonPress.Draw();
					if (buttonPress.IsCollidingWith(startGame))
					{
						return true;
					}
					else if (buttonPress.IsCollidingWith(quitGame))
					{
						m_IsGameOver = true;
					}
				}
			}
		}
	}

	return false;
}

void Game::GameLoop()
{
	m_IsGameOver = false;
	Uint64 totalFrames{ 0 };
	SDL_Event e;

	float frameTime = 16.666f;
	Player* player = new Player(m_Renderer, (char*)"Assets/ship.bmp", 885, 465, 94, 87, 3);
	m_GameObjects.push_back(player);
	++m_ObjectsInScene;

	Asteroid* ast = new Asteroid(m_Renderer, (char*)"Assets/asteroid.bmp", 0, 0, 300, 300, 100, Vector2(rand() % 6, rand() % 6));
	m_GameObjects.push_back(ast);
	++m_ObjectsInScene;

	while (!m_IsGameOver)
	{
		totalFrames++;

		Uint64 startPerf = SDL_GetPerformanceCounter();

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				m_IsGameOver = true;
			}
		}

		SDL_RenderClear(m_Renderer);
		m_Background->Draw();

		player->HandleInput();
		if (player->IsShooting())
		{
			m_GameObjects.push_back(player->CreateBullet());
			++m_ObjectsInScene;
		}

		for (int i = 0; i < m_ObjectsInScene; i++)
		{
			for (int j = 0; j < m_ObjectsInScene; j++)
			{
				if (i != j && m_GameObjects[i]->IsCollidingWith(m_GameObjects[j]))
				{
					//Pass through object type to OnHit
					m_PlayerScore += m_GameObjects[i]->OnHit(m_GameObjects[j]->GetType());

				}
			}
		}

		for (int i = 0; i < m_ObjectsInScene; i++)
		{
			//Puttiing the move & draw in collision would lead to incorrect collisions
			m_GameObjects[i]->Move();
			m_GameObjects[i]->Draw();
			if (m_GameObjects[i]->GetDeleted())
			{
				switch (m_GameObjects[i]->GetType())
				{
				case 'P':
					if (player->GetLives() == 0)
						m_IsGameOver = true;
					else
						RespawnPlayer(player);
					break;

				case 'A': //Spawn child asteroids & update score text
					CreateNewAsteroids(i);
					m_ScoreText->ChangeText(std::string("Score: " + std::to_string(m_PlayerScore)).c_str());
				case 'U':
				case 'B':
					player->SetShooting(true);
				default:
					delete m_GameObjects[i];
					m_GameObjects.erase(m_GameObjects.begin() + i);
					--m_ObjectsInScene;

					//Decrements I in order to perform logic on whatever new object takes the deleted one's place (if any)
					--i;
					break;
				}

			}
			else
			{
				m_GameObjects[i]->Draw();
			}
		}


		m_ScoreText->Draw();
		m_LivesText->Draw();
		SDL_RenderPresent(m_Renderer);

		float elapsedMS = (((float)(SDL_GetPerformanceCounter() - startPerf) / (float)SDL_GetPerformanceFrequency()) * 1000.0f);
		std::cout << elapsedMS << ", " << totalFrames << std::endl;

		if (elapsedMS < frameTime)
		{
			SDL_Delay((Uint32)(16.666f - elapsedMS));
		}
	}
}

void Game::CreateNewAsteroids(int baseIndex)
{
	if (m_GameObjects[baseIndex]->GetW() > 75)
	{
		float baseX = m_GameObjects[baseIndex]->GetX();
		float baseY = m_GameObjects[baseIndex]->GetY();
		int baseW = m_GameObjects[baseIndex]->GetW();
		int baseH = m_GameObjects[baseIndex]->GetH();
		int basePoints = m_GameObjects[baseIndex]->GetPoints();
		Vector2 baseV = m_GameObjects[baseIndex]->GetVelocity();

		Asteroid* newAsteroid1 = new Asteroid(m_Renderer, (char*)"Assets/asteroid.bmp", baseX + (baseW / 2), baseY, baseW / 2, baseH / 2, basePoints * 4, baseV);
		newAsteroid1->Rotate(0.5235988f);
		Asteroid* newAsteroid2 = new Asteroid(m_Renderer, (char*)"Assets/asteroid.bmp", baseX + (baseW / 2), baseY, baseW / 2, baseH / 2, basePoints * 4, baseV);
		newAsteroid2->Rotate(-0.5235988f);

		m_GameObjects.push_back(newAsteroid1);
		m_GameObjects.push_back(newAsteroid2);
		m_ObjectsInScene += 2;
	}
}

void Game::RespawnPlayer(Player* player)
{
	
	Animation explosion = Animation(m_Renderer, (char*)"Assets/explosion.bmp", (char*)"Assets/explosion.wav", 40, 125, 120, 1000, 600);
	explosion.StartAnim(player->GetPosition());
	while (!explosion.isOver)
	{
		SDL_RenderClear(m_Renderer);
		m_Background->Draw();


		for (int i = 0; i < m_ObjectsInScene; i++)
		{
			m_GameObjects[i]->Draw();
		}
		explosion.NextFrame();
		SDL_RenderPresent(m_Renderer);
		SDL_Delay(17);
	}

	player->SetPosition(960.0f, 540.0f);
	player->SetX(960);
	player->SetY(540);

	//Draws the screen with and without the player to simulate the character 'blinking' when respawning
	for (int i = 0; i < 2; i++)
	{
		SDL_RenderClear(m_Renderer);
		m_Background->Draw();


		for (int j = 1; j < m_ObjectsInScene; j++)
		{
			m_GameObjects[j]->Draw();
		}
		SDL_RenderPresent(m_Renderer);
		SDL_Delay(500);

		SDL_RenderClear(m_Renderer);
		m_Background->Draw();


		for (int j = 0; j < m_ObjectsInScene; j++)
		{
			m_GameObjects[j]->Draw();
		}
		SDL_RenderPresent(m_Renderer);
		SDL_Delay(500);
	}

	player->SetDeleted(false);
	m_ScoreText->ChangeText(std::string("Lives: " + std::to_string(player->GetLives())).c_str());
}