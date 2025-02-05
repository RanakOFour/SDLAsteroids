#include <SDL.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include "Game.h"
#include "MusicPlayer.h"
#include "Sprite.h"
#include "TextSprite.h"
#include "Asteroid.h"
#include "Player.h"
#include "UFO.h"
#include "Animation.h"

Game::Game()
{
	m_GameObjects = std::vector<GameObject*>();
	m_ObjectsInScene = 0;
	m_PlayerScore = 0;
	m_Color = SDL_Color();
	m_Color.r = 255; m_Color.b = 255; m_Color.g = 255; m_Color.a = 0;
	m_MusicPlayer = MusicPlayer();

	Initialise();

	m_Background = new Sprite(m_Renderer, (char*)"Assets/bkgd.bmp", 0, 0, 1920, 1080);
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

	m_Window = SDL_CreateWindow("Asteroidz", 0, 0, 1920, 1080, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
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
	TextSprite* nameText = new TextSprite(m_Renderer, (char*)"Assets/comicsans.ttf", (char*)"Asteroidz", m_Color, 480, 50, 960, 360, 72);
	Sprite* startGame = new Sprite(m_Renderer, (char*)"Assets/startButton.bmp", 300, 700, 400, 200);
	Sprite* quitGame = new Sprite(m_Renderer, (char*)"Assets/quitButton.bmp", 1250, 700, 400, 200);

	m_MusicPlayer.PlayMenu();
	//Draw the menu once, because it's static
	SDL_RenderClear(m_Renderer);
	m_Background->Draw();
	nameText->Draw();
	startGame->Draw();
	quitGame->Draw();
	SDL_RenderPresent(m_Renderer);

	SDL_Event e;

	while (!exit)
	{

		while (SDL_PollEvent(&e))
		{
			SDL_RaiseWindow(m_Window);
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
					Sprite buttonPress = Sprite(m_Renderer, x, y, 1, 1);
					buttonPress.Draw();
					if (buttonPress.IsCollidingWith(startGame))
					{
						delete nameText;
						delete startGame;
						delete quitGame;
						return true;
					}
					else if (buttonPress.IsCollidingWith(quitGame))
					{
						exit = true;
					}
				}
			}
		}
	}

	delete nameText;
	delete startGame;
	delete quitGame;

	return false;
}

bool Game::GameLoop()
{
	m_MusicPlayer.PlayBkgd();
	m_GameObjects = std::vector<GameObject*>();
	m_ObjectsInScene = 0;
	m_IsGameOver = false;

	//Calculate spawn frame for UFO
	int UFOSpawnNum = 600 + (rand() % 600);
	Uint64 totalFrames{ 0 };
	SDL_Event e;

	Player* player = new Player(m_Renderer, (char*)"Assets/ship.bmp", 885, 465, 94, 87);
	m_GameObjects.push_back(player);
	++m_ObjectsInScene;

	ShowTutorial();

	CreateAsteroids();

	TextSprite* m_ScoreText = new TextSprite(m_Renderer, (char*)"Assets/comicsans.ttf", (char*)"Score: 0", m_Color, 0, 0, 480, 150, 60);
	TextSprite* m_LivesText = new TextSprite(m_Renderer, (char*)"Assets/comicsans.ttf", (char*)"Lives: 3", m_Color, 0, 150, 160, 100, 48);

	while (!m_IsGameOver)
	{
		totalFrames++;
		Uint64 startPerf = SDL_GetPerformanceCounter();

		if (totalFrames > UFOSpawnNum)
		{
			SpawnUFO();
			UFOSpawnNum += 600 + (rand() % 600);
		}

		//Makes new asteroids when there are few enough of them left
		if (m_ObjectsInScene <= 2)
		{
			CreateAsteroids();
		}

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
			m_MusicPlayer.BulletSoundEffect();
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
			//Putting the move & draw in collision leads to incorrect collisions?
			if (m_GameObjects[i]->GetDeleted())
			{
				switch (m_GameObjects[i]->GetType())
				{
				case 'P':
					if (player->GetLives() == 0)
						m_IsGameOver = true;

					RespawnPlayer(player);
					m_LivesText->ChangeText(std::string("Lives: " + std::to_string(player->GetLives())).c_str());
					break;

				case 'A': //Spawn child asteroids & update score text
					CreateChildAsteroids(i);
				case 'U':
					m_ScoreText->ChangeText(std::string("Score: " + std::to_string(m_PlayerScore)).c_str());
					m_MusicPlayer.OtherHitEffect();
				case 'B':
					player->SetShooting(true);
				default:
					delete m_GameObjects[i];
					m_GameObjects.erase(m_GameObjects.begin() + i);
					--m_ObjectsInScene;

					//Decrements i in order to perform logic on whatever new object takes the deleted one's place (if any)
					--i;
					break;
				}

			}
			else
			{
				m_GameObjects[i]->Move();
				m_GameObjects[i]->Draw();
			}
		}

		m_ScoreText->Draw();
		m_LivesText->Draw();
		SDL_RenderPresent(m_Renderer);

		float elapsedMS = (((float)(SDL_GetPerformanceCounter() - startPerf) / (float)SDL_GetPerformanceFrequency()) * 1000.0f);
		std::cout << elapsedMS << ", " << totalFrames << std::endl;

		if (elapsedMS < 16.666f)
		{
			SDL_Delay((Uint32)(16.666f - elapsedMS));
		}
	}

	return GameOverScreen();
}

void Game::ShowTutorial()
{
	SDL_RenderClear(m_Renderer);

	Sprite* tutorialText = new Sprite(m_Renderer, (char*)"Assets/tutorial.bmp", 274, 117, 1208, 587);
	Sprite* start = new Sprite(m_Renderer, (char*)"Assets/startButton.bmp", 700, 700, 480, 200);
	bool exit{ false };

	tutorialText->Draw();
	start->Draw();
	SDL_RenderPresent(m_Renderer);


	SDL_Event e;
	while (!exit)
	{

		while (SDL_PollEvent(&e))
		{
			SDL_RaiseWindow(m_Window);
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
					Sprite buttonPress = Sprite(m_Renderer, x, y, 1, 1);
					buttonPress.Draw();
					if (buttonPress.IsCollidingWith(start))
					{
						exit = true;
					}
				}
			}
		}
	}

	delete tutorialText;
	delete start;
}


void Game::CreateAsteroids()
{
	//Create 4 asteroids in the corners of the map and rotate them by a random amount
	Asteroid* ast = new Asteroid(m_Renderer, (char*)"Assets/asteroid.bmp", 0, 0, 200, 200, 100, Vector2(4, 4));
	ast->Rotate(rand() % 6);
	m_GameObjects.push_back(ast);

	ast = new Asteroid(m_Renderer, (char*)"Assets/asteroid.bmp", 1720, 0, 200, 200, 100, Vector2(4, 4));
	ast->Rotate(rand() % 6);
	m_GameObjects.push_back(ast);

	ast = new Asteroid(m_Renderer, (char*)"Assets/asteroid.bmp", 0, 880, 200, 200, 100, Vector2(4, 4));
	ast->Rotate(rand() % 6);
	m_GameObjects.push_back(ast);

	ast = new Asteroid(m_Renderer, (char*)"Assets/asteroid.bmp", 1720, 880, 200, 200, 100, Vector2(4, 4));
	ast->Rotate(rand() % 6);
	m_GameObjects.push_back(ast);

	m_ObjectsInScene += 4;
}

void Game::CreateChildAsteroids(int baseIndex)
{
	if (m_GameObjects[baseIndex]->GetW() > 50)
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
	m_MusicPlayer.PlayerHitEffect();

	//Play explosion effect
	Animation explosion = Animation(m_Renderer, (char*)"Assets/explosion.bmp", 40, 125, 120, 1000, 600);
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

	Vector2 pos = GetFreeCoordinates(300);

	player->SetPosition(pos.GetX(), pos.GetY());
	player->SetX(pos.GetX());
	player->SetY(pos.GetY());

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
	player->SetVelocity(0, 0);
}

void Game::SpawnUFO()
{
	Vector2 pos = GetFreeCoordinates(200);

	UFO* ufo = new UFO(m_Renderer, (char*)"Assets/ufo.bmp", pos.GetX() - 100, pos.GetY() - 100, 150, 150);
	m_GameObjects.push_back(ufo);
	++m_ObjectsInScene;
}

bool Game::GameOverScreen()
{
	m_MusicPlayer.StopCurrentTrack();
	m_MusicPlayer.GameOver();
	bool exit = false;
	SDL_Event e;
	TextSprite* gameOverScreen = new TextSprite(m_Renderer, (char*)"Assets/comicsans.ttf", (char*)"GAME OVER", m_Color, 480, 50, 960, 310, 72);
	TextSprite* restart = new TextSprite(m_Renderer, (char*)"Assets/comicsans.ttf", (char*)"Restart", m_Color, 700, 500, 400, 150, 48);
	TextSprite* returnToMenu = new TextSprite(m_Renderer, (char*)"Assets/comicsans.ttf", (char*)"Return to Menu", m_Color, 625, 700, 600, 300, 48);

	gameOverScreen->Draw();
	restart->Draw();
	returnToMenu->Draw();
	SDL_RenderPresent(m_Renderer);

	while (!exit)
	{
		while (SDL_PollEvent(&e))
		{
			SDL_RaiseWindow(m_Window);
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
					Sprite buttonPress = Sprite(m_Renderer, x, y, 1, 1);
					buttonPress.Draw();
					if (buttonPress.IsCollidingWith(restart))
					{
						return true;
					}
					else if (buttonPress.IsCollidingWith(returnToMenu))
					{
						exit = true;
					}
				}
			}
		}
	}

	return false;
}

Vector2 Game::GetFreeCoordinates(int initBounds)
{
	int collidedObjects = 0;
	int xPos = 0;
	int yPos = 0;
	do
	{
		collidedObjects = 0;
		xPos = abs(rand() % (1920 - initBounds));
		yPos = abs(rand() % (1080 - initBounds));
		Sprite test = Sprite(m_Renderer, xPos, yPos, initBounds, initBounds);
		for (int i = 0; i < m_ObjectsInScene; i++)
		{
			if (test.IsCollidingWith(m_GameObjects[i]))
			{
				++collidedObjects;
			}
		}

		//Progressively checks smaller areas
		--initBounds;
	} while (collidedObjects > 0);
	initBounds /= 2;

	return Vector2(xPos, yPos);
}

