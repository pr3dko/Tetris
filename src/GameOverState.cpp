#include "GameOverState.h"
#include "Game.h"
#include "PlayButton.h"

GameOverState::GameOverState(Game* game) :
	GameState{ game },
	mRetryButton{ std::make_unique<PlayButton>(game, (game->mWidth - 150) / 2, 650, 150, 50)},
	mScoreText{ std::make_unique<Texture>(game->GetRenderer()) }
{
	mGameOverImage = game->GetTexture("images/game_over_screen.png");
	mRetryButton->SetSprite(Button::ButtonSprite::MouseOut, "images/retry_button.png");
	mRetryButton->SetSprite(Button::ButtonSprite::MouseOver, "images/retry_button_mouseover.png");
	mScore = game->mScore;
	mHighScore = game->mHighScore;
}

void GameOverState::HandleEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
		{
			mGame->SetNextState(Game::State::Quit);
		}

		mRetryButton->HandleEvent(&e);
	}
}

void GameOverState::Logic()
{
	if (Mix_Playing(-1) == 0 && !mSoundPlayed)
	{
		mGame->PlaySound("audio/game_over.wav");
		mSoundPlayed = true;
	}
}

void GameOverState::Render()
{
	SDL_SetRenderDrawColor(mGame->mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mGame->mRenderer);

	mGameOverImage->Render(0, 0);
	mScoreText->CreateFromText("Score: " + std::to_string(mScore), mGame->GetFont("fonts/font.ttf", 28), SDL_Color{ 255,255,255 });
	mScoreText->Render((mGame->mWidth- mScoreText->GetWidth()) / 2, 300);
	mScoreText->CreateFromText("Best score: " + std::to_string(mHighScore), mGame->GetFont("fonts/font.ttf", 28), SDL_Color{ 255,255,255 });
	mScoreText->Render((mGame->mWidth- mScoreText->GetWidth()) / 2, 350);
	mRetryButton->Render();

	SDL_RenderPresent(mGame->mRenderer);
}