#pragma once
#include "GameState.h"
#include "Texture.h"
#include "PlayButton.h"
#include <memory>

class GameOverState : public GameState
{
public:
	GameOverState(class Game* game);

	void HandleEvents() override;
	void Logic() override;
	void Render() override;

private:
	class Texture* mGameOverImage{};
	std::unique_ptr<PlayButton> mRetryButton;
	std::unique_ptr<Texture> mScoreText;
	int mScore{};
	int mHighScore{};
	bool mSoundPlayed{};
};