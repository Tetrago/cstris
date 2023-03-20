#pragma once

class Board;

enum class Tetrimino
{
	None = 0,
	I,
	O,
	T,
	J,
	L,
	S,
	Z
};

enum class Rotation
{
	None = 0,
	Clockwise,
	Half,
	Counterclockwise
};

Rotation rotate_clockwise(Rotation rotation) noexcept;
Rotation rotate_counterclockwiise(Rotation rotation) noexcept;

Board get_tetrimino(Tetrimino tetrimino) noexcept;
