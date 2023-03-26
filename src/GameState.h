#pragma once
#include <SDL.h>

class GameState
{
public:
	GameState(class Game* game) : mGame(game) {}
	virtual ~GameState() {}
	virtual void HandleEvents() = 0;
	virtual void Logic() = 0;
	virtual void Render() = 0;

protected:
	class Game* mGame;
};