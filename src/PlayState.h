#pragma once
#include "GameState.h"
#include <vector>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <unordered_map>
#include "Timer.h"
#include <array>
#include "Constants.h"
#include <memory>
#include "Texture.h"

struct Tetromino
{
	int mID{};
	int mRotation{};
	int mPosX{};
	int mPosY{};
	int mVelX{};
	int mVelY{};
	bool mRotating{};
};

class PlayState : public GameState
{
public:
	PlayState(class Game* game);

	void HandleEvents() override;
	void Logic() override;
	void Render() override;

private:
	bool PieceFits(int tetromino, int rotation, int posX, int posY);
	int Rotate(int x, int y, int r);
	void DrawCell(int x, int y, SDL_Color colour);
	void DrawCellOutline(int x, int y, SDL_Color colour);

	enum class CellEntry {I, Z, S, O, T, L, J, Border, LineClear, Empty};
	std::array<CellEntry, Constants::numColumns * Constants::numRows> mField;

	static const int initialSpeed{ 80 };

	bool mRotateHold{};
	bool mHardDropHold{};
	bool mMoveDown{};
	bool mHardDrop{};
	bool mAlreadySwapped{};
	bool mFirstKeyPress{ true };

	int mSpeed{ initialSpeed };
	int mSpeedCounter{};
	int mTotalLinesCleared{};

	int mScore{};
	std::unique_ptr<Texture> mScoreText;
	int mNextPieceID{};
	Tetromino mCurrentPiece{};
	std::vector<int> mLinesCleared;
	Timer mTimer{};
	int mKeyPressCooldown{};
};