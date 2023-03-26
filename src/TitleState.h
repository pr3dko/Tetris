#pragma once
#include "GameState.h"
#include "PlayButton.h"
#include <memory>

class TitleState : public GameState
{
public:
	TitleState(class Game* game);

	void HandleEvents() override;
	void Logic() override;
	void Render() override;

private:
	class Texture* mTitleImage{};
	std::unique_ptr<PlayButton> mPlayButton;
};