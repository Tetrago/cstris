#include "dropper.hpp"

#include <algorithm>
#include <random>

Dropper::Dropper(Board* board) noexcept
	: mBoard(board)
{
	next();
}

bool Dropper::step() noexcept
{
	++mY;
	if(!mBoard->intersects(mPiece, mX, mY) && mY + mBounds.maxY < mBoard->height()) return false;
	
	mBoard->overlay(mPiece, mX, mY - 1);
	mLocked = false;
	next();
	return true;
}

void Dropper::drop() noexcept
{
	while(!step());
}

void Dropper::draw(int x, int y, int ppu) const noexcept
{
	mPiece.draw(x + mX * ppu, y + mY * ppu, ppu);
	mPiece.draw(x + mX * ppu, y + mLowestY * ppu, ppu, true);
}

void Dropper::shift(int d) noexcept
{
	if(mBoard->intersects(mPiece, mX + d, mY)) return;

	mX += d;
	update();
}

void Dropper::rotate() noexcept
{
	Board piece = mPiece.rotate(Rotation::Clockwise);
	if(mBoard->intersects(piece, mX, mY)) return;

	mPiece = piece;
	mBounds = mPiece.bounds();
	update();
}

void Dropper::swap() noexcept
{
	if(mLocked) return;
	mLocked = true;

	Tetrimino tmp = mCurrent;
	piece(mHeld != Tetrimino::None ? mHeld : getTetriminoFromBag());
	mHeld = tmp;
}

void Dropper::update() noexcept
{
	mX = std::clamp(mX, -mBounds.minX, mBoard->width() - mBounds.maxX - 1);

	mLowestY = mY;
	while(1)
	{
		++mLowestY;
		if(!mBoard->intersects(mPiece, mX, mLowestY) && mLowestY + mBounds.maxY < mBoard->height()) continue;
	
		--mLowestY;
		break;
	}
}

void Dropper::next() noexcept
{
	piece(getTetriminoFromBag());
}

void Dropper::piece(Tetrimino tetrimino) noexcept
{
	mCurrent = tetrimino;
	mPiece = get_tetrimino(tetrimino);
	mBounds = mPiece.bounds();
	mX = mBoard->width() / 2 - mPiece.width() / 2;
	mY = 0;
	update();
}

Tetrimino Dropper::getTetriminoFromBag() noexcept
{
	if(mBag.size() < 7)
	{
		std::vector<Tetrimino> bag
		{
			Tetrimino::I,
			Tetrimino::O,
			Tetrimino::T,
			Tetrimino::J,
			Tetrimino::L,
			Tetrimino::S,
			Tetrimino::Z
		};

		std::shuffle(bag.begin(), bag.end(), std::default_random_engine());
		mBag.insert(mBag.begin(), bag.begin(), bag.end());
	}

	Tetrimino tetrimino = mBag.back();
	mBag.pop_back();
	return tetrimino;
}
