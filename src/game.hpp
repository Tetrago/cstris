#pragma once

#include "board.hpp"
#include "dropper.hpp"

class Game
{
public:
	Game(int width = 10, int height = 20) noexcept;

	void step() noexcept;
	void left() noexcept;
	void right() noexcept;
	void rotate() noexcept;
	void drop() noexcept;
	void draw(int x, int y, int ppu = 30) const noexcept;

	const Board& board() const noexcept { return mBoard; }
private:
	Board mBoard;
	Dropper mDropper;
};
