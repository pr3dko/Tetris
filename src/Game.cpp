#include "Game.h"
#include <stdio.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Timer.h"
#include "GameState.h"
#include "TitleState.h"
#include <stdlib.h>
#include <time.h>
#include "Texture.h"
#include "PlayState.h"
#include "Constants.h"
#include "GameOverState.h"

Game::Game(int width, int height) :
	mWidth{ width },
	mHeight{ height }
{
	if (!Initialise())
	{
		printf("Failed to initialise game.\n");
	}
	else
	{
		mInitialised = true;
	}

	mCurrentGameState = std::make_unique<TitleState>(this);

	srand(static_cast<unsigned int>(time(nullptr)));
}

Game::~Game()
{
	for (auto& [path, chunk] : mSoundFX)
	{
		Mix_FreeChunk(chunk);
		chunk = nullptr;
	}

	for (auto& [path, music] : mMusic)
	{
		Mix_FreeMusic(music);
		music = nullptr;
	}

	for (auto& [path, font] : mFonts)
	{
		TTF_CloseFont(font);
		font = nullptr;
	}

	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	mWindow = nullptr;
	mRenderer = nullptr;

	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}

bool Game::Initialise()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL failed to initialise. Error: %s\n", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth, mHeight, SDL_WINDOW_SHOWN);
	if (!mWindow)
	{
		printf("Failed to create window. Error: %s\n", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!mRenderer)
	{
		printf("Failed to create renderer. Error: %s\n", SDL_GetError());
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer failed to initialise. Error: %s\n", Mix_GetError());
		return false;
	}

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf failed to initialise. Error: %s\n", TTF_GetError());
		return false;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image failed to initialise. Error: %s\n", IMG_GetError());
		return false;
	}

	return true;
}

void Game::Delay(int time)
{
	int timeout = SDL_GetTicks() + time;
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout));
}

Texture* Game::GetTexture(const std::string& path)
{
	if (mTextures.find(path) == mTextures.end())
	{
		mTextures.emplace(path, std::make_unique<Texture>(mRenderer));
		if (!mTextures[path]->LoadFromFile(path))
		{
			printf("Failed to load texture at %s.\n", path.c_str());
		}
	}

	return mTextures[path].get();
}

Mix_Chunk* Game::GetSound(const std::string& path)
{
	if (!mSoundFX[path])
	{
		mSoundFX[path] = Mix_LoadWAV(path.c_str());
		if (!mSoundFX[path])
		{
			printf("Failed to load sound at %s. Error: %s\n", path.c_str(), Mix_GetError());
		}
	}

	return mSoundFX[path];
}

Mix_Music* Game::GetMusic(const std::string& path)
{
	if (!mMusic[path])
	{
		mMusic[path] = Mix_LoadMUS(path.c_str());
		if (!mMusic[path])
		{
			printf("Failed to load music at %s. Error: %s\n", path.c_str(), Mix_GetError());
		}
	}

	return mMusic[path];
}

TTF_Font* Game::GetFont(const std::string& path, int fontSize)
{
	if (!mFonts[path])
	{
		mFonts[path] = TTF_OpenFont(path.c_str(), fontSize);
		if (!mFonts[path])
		{
			printf("Failed to load font at %s. Error: %s\n", path.c_str(), TTF_GetError());
		}
	}

	return mFonts[path];
}

void Game::Run()
{
	if (mInitialised)
	{
		Timer fpsTimer;
		while (mCurrentState != State::Quit)
		{
			fpsTimer.Start();

			mCurrentGameState->HandleEvents();
			mCurrentGameState->Logic();
			ChangeState();
			mCurrentGameState->Render();

			int frameTicks = fpsTimer.GetTicks();
			if (frameTicks < 1000 / Constants::fps)
			{
				SDL_Delay(1000 / Constants::fps - frameTicks);
			}
		}
	}
	else
	{
		printf("Error: cannot run uninitialised game.\n");
	}
}

void Game::SetNextState(State nextState)
{
	if (mNextState != State::Quit)
	{
		mNextState = nextState;
	}
}

void Game::ChangeState()
{
	if (mNextState != State::Null)
	{
		switch (mNextState)
		{
			case State::Play:
				mCurrentGameState.reset(new PlayState(this));
				break;
			case State::GameOver:
				mCurrentGameState.reset(new GameOverState(this));
				break;
		}

		mCurrentState = mNextState;
		mNextState = State::Null;
	}
}

void Game::PlaySound(const std::string& path)
{
	if (!mSoundFX[path])
	{
		mSoundFX[path] = Mix_LoadWAV(path.c_str());
		if (!mSoundFX[path])
		{
			printf("Failed to load sound at %s. Error: %s\n", path.c_str(), Mix_GetError());
			return;
		}
	}

	Mix_PlayChannel(-1, mSoundFX[path], 0);
}

void Game::PlayMusic(const std::string& path)
{
	if (!mMusic[path])
	{
		mMusic[path] = Mix_LoadMUS(path.c_str());
		if (!mMusic[path])
		{
			printf("Failed to load music at %s. Error: %s\n", path.c_str(), Mix_GetError());
			return;
		}
	}

	if (!Mix_PlayingMusic())
	{
		Mix_PlayMusic(mMusic[path], -1);
	}
}