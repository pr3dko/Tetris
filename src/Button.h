#pragma once
#include <SDL.h>
#include <string>
#include <unordered_map>

class Button
{
public:
	enum class ButtonSprite { MouseOut, MouseOver };

	Button(class Game* game, int x, int y, int w, int h);
	virtual ~Button();
	void SetPosition(int x, int y);
	virtual void HandleEvent(SDL_Event* e) = 0;
	void Render();
	void SetSprite(ButtonSprite sprite, const std::string& spritePath);

protected:
	class Game* mGame{};
	std::unordered_map<ButtonSprite, class Texture*> mSpriteMap;
	SDL_Rect mRect{};
	ButtonSprite mCurrentSprite{ ButtonSprite::MouseOut };
};