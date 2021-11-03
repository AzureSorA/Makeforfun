#include"Game.h"

const int width = 640;
const int height = 480;

int main(int argc, char* argv[])
{
	Game* game = new Game();
	if (!game->init("Minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN))
	{
		return -1;
	}
	while (game->is_running())
	{
		game->handle_events();
		game->renderer();
	}
	game->quit();
	delete game;
	_CrtDumpMemoryLeaks();
	return 0;
}