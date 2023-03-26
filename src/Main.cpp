#include "Game.h"
#include "Constants.h"

int main(int argc, char* argv[])
{
	Game game(Constants::screenWidth, Constants::screenHeight);

	game.Run();

	return 0;
}