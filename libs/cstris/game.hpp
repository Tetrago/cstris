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
	void down() noexcept;
	void drop() noexcept;
	void swap() noexcept;
	void draw(int x, int y, int ppu = 30) const noexcept;

	const Board& board() const noexcept { return mBoard; }
	const Dropper& dropper() const noexcept { return mDropper; }
private:
	Board mBoard;
	Dropper mDropper;
};
