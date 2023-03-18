#pragma once

#include <raylib.h>

#include "tetrimino.hpp"

class Board
{
public:
	Board(int width = 10, int height = 20) noexcept;
	~Board() noexcept;

	Board(const Board& other) noexcept;
	Board& operator=(const Board&) = delete;
	Board(Board&& other) noexcept;
	Board& operator=(Board&&) = delete;

	void set(int x, int y, Tetrimino tetrimino) noexcept;
	Board rotate(Rotation rotation) noexcept;
	void draw(int x, int y, bool ghost = false, int ppu = 30) noexcept;

	int width() const { return mWidth; }
	int height() const { return mHeight; }
private:
	void drawTetrimino(int x, int y, int ppu, Tetrimino tetrimino, bool ghost) noexcept;

	int const mWidth;
	int const mHeight;
	Tetrimino* mTetriminoes;
};