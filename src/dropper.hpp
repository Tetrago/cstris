#pragma once

#include <vector>

#include "board.hpp"
#include "tetrimino.hpp"

class Dropper
{
public:
	Dropper(Board* board) noexcept;

	bool step() noexcept;
	void drop() noexcept;
	void draw(int ppu = 30) const noexcept;
	void shift(int d) noexcept;
	void rotate() noexcept;
private:
	void update() noexcept;
	void next() noexcept;
	Tetrimino getTetriminoFromBag() noexcept;

	Board* const mBoard;
	Board mPiece;
	Board mGhost;
	Vector4 mBounds;
	int mX;
	int mY;
	int mLowestY;
	std::vector<Tetrimino> mBag;
};