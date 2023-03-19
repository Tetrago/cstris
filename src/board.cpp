#include "board.hpp"

#include <cstring>
#include <cassert>
#include <algorithm>

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

Board& Board::operator=(const Board& other) noexcept
{
	mWidth = other.mWidth;
	mHeight = other.mHeight;
	mTetriminoes = new Tetrimino[mWidth * mHeight];
	memcpy(mTetriminoes, other.mTetriminoes, sizeof(Tetrimino) * mWidth * mHeight);

	return *this;
}

Board::Board(Board&& other) noexcept
	: mWidth(other.mWidth)
	, mHeight(other.mHeight)
{
	mTetriminoes = other.mTetriminoes;
	other.mTetriminoes = nullptr;
}

Board& Board::operator=(Board&& other) noexcept
{
	mWidth = other.mWidth;
	mHeight = other.mHeight;
	mTetriminoes = other.mTetriminoes;

	other.mTetriminoes = nullptr;

	return *this;
}

void Board::set(int x, int y, Tetrimino tetrimino) noexcept
{
	mTetriminoes[y * mWidth + x] = tetrimino;
}

Board Board::rotate(Rotation rotation) const noexcept
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

void Board::draw(int x, int y, bool ghost, int ppu) const noexcept
{
	for(int dx = 0; dx < mWidth; ++dx)
	{
		for(int dy = 0; dy < mHeight; ++dy)
		{
			drawTetrimino(x + dx * ppu, y + (mHeight - dy - 1) * ppu, ppu, mTetriminoes[(mHeight - dy - 1) * mWidth + dx], ghost);
		}
	}
}

bool Board::intersects(const Board& board, int x, int y) const noexcept
{
	for(int dx = 0; dx < board.width(); ++dx)
	{
		for(int dy = 0; dy < board.height(); ++dy)
		{
			int bx = x + dx;
			int by = y + dy;

			if(bx < 0 || bx >= mWidth || by < 0 || by >= mHeight) continue;

			if(mTetriminoes[by * mWidth + bx] != Tetrimino::None
				&& board.mTetriminoes[dy * board.width() + dx] != Tetrimino::None)
			{
				return true;
			}
		}
	}

	return false;
}

void Board::overlay(const Board& board, int x, int y) noexcept
{
	for(int dx = 0; dx < board.width(); ++dx)
	{
		for(int dy = 0; dy < board.height(); ++dy)
		{
			int bx = x + dx;
			int by = y + dy;

			if(bx < 0 || bx >= mWidth || by < 0 || by >= mHeight) continue;

			Tetrimino piece = board.mTetriminoes[dy * board.width() + dx];
			if(piece == Tetrimino::None) continue;

			mTetriminoes[by * mWidth + bx] = piece;
		}
	}
}

Vector4 Board::bounds() const noexcept
{
	Vector4 bounds = { mWidth, mHeight, 0, 0 };

	for(int x = 0; x < mWidth; ++x)
	{
		for(int y = 0; y < mHeight; ++y)
		{
			if(mTetriminoes[y * mWidth + x] == Tetrimino::None) continue;

			bounds.x = std::min(static_cast<float>(x), bounds.x);
			bounds.y = std::min(static_cast<float>(y), bounds.y);
			bounds.z = std::max(static_cast<float>(x), bounds.z);
			bounds.w = std::max(static_cast<float>(y), bounds.w);
		}
	}

	return bounds;
}

void Board::drawTetrimino(int x, int y, int ppu, Tetrimino tetrimino, bool ghost) const noexcept
{
	if(tetrimino == Tetrimino::None) return;

	Color color = get_tetrimino_color(tetrimino);
	if(ghost)
	{
		color.a = 129;
	}

	DrawRectangle(x, y, ppu, ppu, color);
}
