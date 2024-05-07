#include <iostream>
#include "Game.h"

int main(int argc, char* args[])
{
	Game* game = new Game();
	if (game != nullptr)
	{
		game->GameLoop();
		delete game;
	}
	else
	{
		std::cout << "Error creating game. Oops.";
	}

	return 0;
}