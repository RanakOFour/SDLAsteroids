#include <iostream>
#include "Game.h"

int main(int argc, char* args[])
{
	std::srand(time(NULL));
	bool exitGame = true;

	Game* game = new Game();
	if (game != nullptr)
	{
		while (exitGame)
		{
			exitGame = game->MenuLoop();
			if (exitGame)
			{
				//Gameloop return true when pressing restart, and false when returning to menu
				while (game->GameLoop())
				{

				}
			}
		}


		delete game;
	}
	else
	{
		std::cout << "Error creating game. Oops.";
	}

	return 0;
}