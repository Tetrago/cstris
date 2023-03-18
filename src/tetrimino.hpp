#pragma once

#include <raylib.h>

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

Color get_tetrimino_color(Tetrimino tetrimino) noexcept;

Rotation rotate_clockwise(Rotation rotation) noexcept;
Rotation rotate_counterclockwiise(Rotation rotation) noexcept;

Board get_tetrimino(Tetrimino tetrimino) noexcept;
