#include "dropper.hpp"

#include <algorithm>

Dropper::Dropper(Board* board) noexcept
	: mBoard(board)
{}

void Dropper::piece(Tetrimino tetrimino) noexcept
{
	mPiece = get_tetrimino(tetrimino);
	mBounds = mPiece.bounds();
	mX = mBoard->width() / 2 - mPiece.width() / 2;
	mY = 0;
}

bool Dropper::step() noexcept
{
	if(!mBoard->intersects(mPiece, mX, mY) && mY + mBounds.w + 1 < mBoard->height())
	{
		mY += 1;
		return false;
	}

	mBoard->overlay(mPiece, mX, mY);
	return true;
}

void Dropper::drop() noexcept
{
	while(!step());
}

void Dropper::draw(int ppu) const noexcept
{
	mPiece.draw(mX * ppu, mY * ppu, ppu);
}

void Dropper::shift(int d) noexcept
{
	mX += d;
	clamp();
}

void Dropper::rotate() noexcept
{
	mPiece = mPiece.rotate(Rotation::Clockwise);
	mBounds = mPiece.bounds();
	clamp();
}

void Dropper::clamp() noexcept
{
	mX = std::clamp(mX, -static_cast<int>(mBounds.x), mBoard->width() - static_cast<int>(mBounds.z) - 1);
}