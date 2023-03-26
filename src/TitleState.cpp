#include "TitleState.h"
#include "Texture.h"
#include "Game.h"
#include "PlayButton.h"

TitleState::TitleState(Game* game) : 
	GameState{ game },
	mTitleImage{ game->GetTexture("images/title_screen.png") },
	mPlayButton{ std::make_unique<PlayButton>(game, (game->mWidth - 150) / 2, 650, 150, 50) }
{
	mPlayButton->SetSprite(Button::ButtonSprite::MouseOut, "images/play_button.png");
	mPlayButton->SetSprite(Button::ButtonSprite::MouseOver, "images/play_button_mouseover.png");
}

void TitleState::HandleEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
		{
			mGame->SetNextState(Game::State::Quit);
		}

		mPlayButton->HandleEvent(&e);
	}
}

void TitleState::Logic()
{

}

void TitleState::Render()
{
	SDL_SetRenderDrawColor(mGame->mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mGame->mRenderer);

	mTitleImage->Render(0, 0);
	mPlayButton->Render();

	SDL_RenderPresent(mGame->mRenderer);
}