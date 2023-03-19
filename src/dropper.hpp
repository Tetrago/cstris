#pragma once

#include "board.hpp"
#include "tetrimino.hpp"

class Dropper
{
public:
	Dropper(Board* board) noexcept;

	void piece(Tetrimino tetrimino) noexcept;
	bool step() noexcept;
	void drop() noexcept;
	void draw(int ppu = 30) const noexcept;
	void shift(int d) noexcept;
	void rotate() noexcept;
private:
	void clamp() noexcept;

	Board* const mBoard;
	Board mPiece;
	Vector4 mBounds;
	int mX;
	int mY;
};