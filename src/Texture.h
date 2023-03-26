#pragma once
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class Texture
{
public:
	Texture(SDL_Renderer* renderer);
	~Texture();
	Texture(const Texture&) = delete;
	Texture(Texture&&) = delete;
	Texture& operator=(const Texture&) = delete;
	Texture& operator=(Texture&&) = delete;

	bool LoadFromFile(const std::string& path);
	bool CreateFromText(const std::string& text, TTF_Font* font, SDL_Color colour);
	void Render(int x, int y, SDL_Rect* clip = nullptr);
	void Render(int x, int y, int w, int h, SDL_Rect* clip = nullptr);

	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }

private:
	void Free();

	SDL_Texture* mTexture{};
	SDL_Renderer* mRenderer{};
	int mWidth{};
	int mHeight{};
};