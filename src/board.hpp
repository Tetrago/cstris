#pragma once

#include <raylib.h>

#include "tetrimino.hpp"

class Board
{
public:
	Board(int width = 10, int height = 20) noexcept;
	~Board() noexcept;

	Board(const Board& other) noexcept;
	Board& operator=(const Board& other) noexcept;
	Board(Board&& other) noexcept;
	Board& operator=(Board&& other) noexcept;

	void set(int x, int y, Tetrimino tetrimino) noexcept;
	Board rotate(Rotation rotation) const noexcept;
	void draw(int x, int y, bool ghost = false, int ppu = 30) const noexcept;
	bool intersects(const Board& board, int x, int y) const noexcept;
	void overlay(const Board& board, int x, int y) noexcept;
	Vector4 bounds() const noexcept;

	int width() const { return mWidth; }
	int height() const { return mHeight; }
private:
	void drawTetrimino(int x, int y, int ppu, Tetrimino tetrimino, bool ghost) const noexcept;

	int mWidth;
	int mHeight;
	Tetrimino* mTetriminoes;
};