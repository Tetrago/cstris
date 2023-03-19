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
	if(!mBoard->intersects(mPiece, mX, mY) && mY + mBounds.w < mBoard->height()) return false;
	
	mBoard->overlay(mPiece, mX, mY - 1);
	next();
	return true;
}

void Dropper::drop() noexcept
{
	while(!step());
}

void Dropper::draw(int ppu) const noexcept
{
	mPiece.draw(mX * ppu, mY * ppu, false, ppu);
	mGhost.draw(mX * ppu, mLowestY * ppu, true, ppu);
}

void Dropper::shift(int d) noexcept
{
	mX += d;
	update();
}

void Dropper::rotate() noexcept
{
	mPiece = mPiece.rotate(Rotation::Clockwise);
	mBounds = mPiece.bounds();
	update();
}

void Dropper::update() noexcept
{
	mX = std::clamp(mX, -static_cast<int>(mBounds.x), mBoard->width() - static_cast<int>(mBounds.z) - 1);

	mGhost = mPiece;
	mLowestY = mY;
	Vector4 bounds = mGhost.bounds();
	
	while(1)
	{
		++mLowestY;
		if(!mBoard->intersects(mGhost, mX, mLowestY) && mLowestY + bounds.w < mBoard->height()) continue;
	
		--mLowestY;
		break;
	}
}

void Dropper::next() noexcept
{
	mPiece = get_tetrimino(getTetriminoFromBag());
	mBounds = mPiece.bounds();
	mX = mBoard->width() / 2 - mPiece.width() / 2;
	mY = 0;
	update();
}

Tetrimino Dropper::getTetriminoFromBag() noexcept
{
	if(mBag.empty())
	{
		mBag = std::vector<Tetrimino>
		{
			Tetrimino::I,
			Tetrimino::O,
			Tetrimino::T,
			Tetrimino::J,
			Tetrimino::L,
			Tetrimino::S,
			Tetrimino::Z
		};

		std::shuffle(mBag.begin(), mBag.end(), std::default_random_engine());
	}

	Tetrimino tetrimino = mBag.back();
	mBag.pop_back();
	return tetrimino;
}
