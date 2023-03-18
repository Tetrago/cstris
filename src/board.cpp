#include "board.hpp"

#include <cstring>
#include <cassert>

Board::Board(int width, int height) noexcept
	: mWidth(width)
	, mHeight(height)
{
	mTetriminoes = new Tetrimino[mWidth * mHeight]{ Tetrimino::None };
}

Board::~Board() noexcept
{
	delete[] mTetriminoes;
}

Board::Board(const Board& other) noexcept
	: mWidth(other.mWidth)
	, mHeight(other.mHeight)
{
	mTetriminoes = new Tetrimino[mWidth * mHeight];
	memcpy(mTetriminoes, other.mTetriminoes, sizeof(Tetrimino) * mWidth * mHeight);
}

Board::Board(Board&& other) noexcept
	: mWidth(other.mWidth)
	, mHeight(other.mHeight)
{
	mTetriminoes = other.mTetriminoes;
	other.mTetriminoes = nullptr;
}

void Board::set(int x, int y, Tetrimino tetrimino) noexcept
{
	mTetriminoes[y * mWidth + x] = tetrimino;
}

Board Board::rotate(Rotation rotation) noexcept
{
	assert(mWidth == mHeight, "Cannot rotate rectangular board");
	assert(rotation != Rotation::None, "Cannot rotate zero rotation");

	Board board(mWidth, mHeight);

	for(int x = 0; x < mWidth; ++x)
	{
		for(int y = 0; y < mHeight; ++y)
		{
			int dx = mWidth - (y + 0.5f);
			board.mTetriminoes[x * mWidth + dx] = mTetriminoes[y * mWidth + x];
		}
	}

	if(rotation == Rotation::Clockwise) return board;
	return board.rotate(static_cast<Rotation>(static_cast<int>(rotation) - 1));
}

void Board::draw(int x, int y, bool ghost, int ppu) noexcept
{
	for(int dx = 0; dx < mWidth; ++dx)
	{
		for(int dy = 0; dy < mHeight; ++dy)
		{
			drawTetrimino(x + dx * ppu, y + (mHeight - dy - 1) * ppu, ppu, mTetriminoes[(mHeight - dy - 1) * mWidth + dx], ghost);
		}
	}
}

void Board::drawTetrimino(int x, int y, int ppu, Tetrimino tetrimino, bool ghost) noexcept
{
	Color color = get_tetrimino_color(tetrimino);
	if(ghost)
	{
		color.a = 129;
	}

	DrawRectangle(x, y, ppu, ppu, color);
	//DrawRectangleLines(x, y, ppu, ppu, { 0, 0, 0, 255 }); // Border
}
