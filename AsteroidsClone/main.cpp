#include <iostream>
#include "Game.h"

int main(int argc, char* args[])
{
	std::srand(time(NULL));
	Game* game = new Game();
	if (game != nullptr)
	{
		if (game->MenuLoop())
		{
			game->GameLoop();
		}
		delete game;
	}
	else
	{
		std::cout << "Error creating game. Oops.";
	}

	return 0;
}