#pragma once
#include <array>
#include <SDL.h>

static constexpr std::array<std::array<int, 16>, 7> tetrominos{
	{
		// ID: 0
		{0, 0, 1, 0,
		0, 0, 1, 0,
		0, 0, 1, 0,
		0, 0, 1, 0},
		// 1
		{0, 0, 1, 0,
		0, 1, 1, 0,
		0, 1, 0, 0,
		0, 0, 0, 0},
		// 2
		{0, 1, 0, 0,
		0, 1, 1, 0,
		0, 0, 1, 0,
		0, 0, 0, 0},
		// 3
		{0, 0, 0, 0,
		0, 1, 1, 0,
		0, 1, 1, 0,
		0, 0, 0, 0},
		// 4
		{0, 0, 1, 0,
		0, 1, 1, 0,
		0, 0, 1, 0,
		0, 0, 0, 0},
		// 5
		{0, 0, 0, 0,
		0, 1, 1, 0,
		0, 0, 1, 0,
		0, 0, 1, 0},
		// 6
		{0, 0, 0, 0,
		0, 1, 1, 0,
		0, 1, 0, 0,
		0, 1, 0, 0},
	}
};

static constexpr std::array<SDL_Color, 9> tetrominoColours{
	{
		// Tetrominos
		// 0
		{ 66, 239, 245, 255},
		// 1
		{ 255,   0,   0, 255 },
		// 2
		{ 0, 255,   0, 255 },
		// 3
		{ 255, 238,   0, 255 },
		// 4
		{ 187,   0, 255, 255 },
		// 5
		{ 255, 149,   0, 255 },
		// 6
		{ 0,   0, 255, 255 },

		// Other
		// 7: border cell
		{ 122, 122, 122, 255 },
		// 8: line clear
		{ 255, 255, 255, 255 }
	}
};