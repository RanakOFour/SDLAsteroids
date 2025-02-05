#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <map>
#include "Asteroid.h"
#include "GameObject.h"
#include "Player.h"
#include "Sprite.h"
#include "TextSprite.h"
#include "MusicPlayer.h"

#pragma once
#define H_GAME

class Game
{
private:
	//Holds all GameObjects in the scene
	std::vector<GameObject*> m_GameObjects;

	//The number of objects currently in the scene
	int m_ObjectsInScene;
	int m_PlayerScore;
	bool m_IsGameOver;
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	SDL_Color m_Color;
	Sprite* m_Background;
	MusicPlayer m_MusicPlayer;
	int Initialise();

public:
	Game();
	~Game();
	bool MenuLoop();
	bool GameLoop();
	void ShowTutorial();
	void CreateAsteroids();
	void CreateChildAsteroids(int baseIndex);
	void RespawnPlayer(Player* player);
	void SpawnUFO();
	bool GameOverScreen();
	Vector2 GetFreeCoordinates(int initBounds);
};