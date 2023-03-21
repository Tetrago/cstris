#pragma once

#include "tetrimino.hpp"

struct Bounds
{
	int minX;
	int minY;
	int maxX;
	int maxY;
};

extern void cstris_draw_block(int x, int y, int size, Tetrimino tetrimino, bool ghost);

class Board
{
public:
	Board() noexcept;
	Board(int width, int height) noexcept;
	~Board() noexcept;

	Board(const Board& other) noexcept;
	Board& operator=(const Board& other) noexcept;
	Board(Board&& other) noexcept;
	Board& operator=(Board&& other) noexcept;

	void set(int x, int y, Tetrimino tetrimino) noexcept;
	Board rotate(Rotation rotation) const noexcept;
	void draw(int x, int y, int ppu, bool ghost = false) const noexcept;
	bool intersects(const Board& board, int x, int y) const noexcept;
	void overlay(const Board& board, int x, int y) noexcept;
	Bounds bounds() const noexcept;
	int consolidate() noexcept;

	int width() const { return mWidth; }
	int height() const { return mHeight; }
private:
	int mWidth;
	int mHeight;
	Tetrimino* mTetriminoes;
};