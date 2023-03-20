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
	void draw(int x, int y, int ppu) const noexcept;
	void shift(int d) noexcept;
	void rotate() noexcept;
	void swap() noexcept;

	auto begin() const noexcept { return mBag.rbegin(); }
	auto end() const noexcept { return mBag.rend(); }
private:
	void update() noexcept;
	void next() noexcept;
	void piece(Tetrimino tetrimino) noexcept;
	Tetrimino getTetriminoFromBag() noexcept;

	Board* const mBoard;
	Board mPiece;
	Bounds mBounds;
	int mX;
	int mY;
	int mLowestY;
	std::vector<Tetrimino> mBag;
	Tetrimino mCurrent;
	Tetrimino mHeld = Tetrimino::None;
	bool mLocked = false;
};