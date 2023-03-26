#pragma once
#include <SDL.h>
#include <unordered_map>
#include <string>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <memory>
#include "GameState.h"
#include "Texture.h"

class Game
{
	friend class GameState;
	friend class TitleState;
	friend class PlayState;
	friend class GameOverState;
	friend class PlayButton;
public:
	Game(int width, int height);
	~Game();
	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) = delete;

	enum class State { Null, Title, Play, GameOver, Quit };

	SDL_Renderer* GetRenderer() const { return mRenderer; }
	class Texture* GetTexture(const std::string& path);
	Mix_Chunk* GetSound(const std::string& path);
	Mix_Music* GetMusic(const std::string& path);
	TTF_Font* GetFont(const std::string& path, int fontSize);
	void PlaySound(const std::string& path);
	void PlayMusic(const std::string& path);
	void Run();

private:
	bool Initialise();
	void Delay(int time);
	void SetNextState(State nextState);
	void ChangeState();

	std::unordered_map<std::string, std::unique_ptr<Texture>> mTextures;
	std::unordered_map<std::string, Mix_Chunk*> mSoundFX;
	std::unordered_map<std::string, Mix_Music*> mMusic;
	std::unordered_map<std::string, TTF_Font*> mFonts;
	std::unique_ptr<GameState> mCurrentGameState;
	State mCurrentState{ State::Null };
	State mNextState{ State::Null };
	SDL_Window* mWindow{};
	SDL_Renderer* mRenderer{};
	int mWidth{};
	int mHeight{};
	bool mInitialised{};
	int mScore{};
	int mHighScore{};
};