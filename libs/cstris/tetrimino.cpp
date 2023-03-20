#include "tetrimino.hpp"

#include <unordered_map>

#include "board.hpp"

namespace
{
	std::unordered_map<Tetrimino, Board> gTetriminos
	{
		{ Tetrimino::I, []() -> Board
		{
			Board board(4, 4);
			board.set(0, 1, Tetrimino::I);
			board.set(1, 1, Tetrimino::I);
			board.set(2, 1, Tetrimino::I);
			board.set(3, 1, Tetrimino::I);

			return board;
		}()},
		{ Tetrimino::O, []() -> Board
		{
			Board board(2, 2);
			board.set(0, 0, Tetrimino::O);
			board.set(1, 0, Tetrimino::O);
			board.set(1, 1, Tetrimino::O);
			board.set(0, 1, Tetrimino::O);

			return board;
		}()},
		{ Tetrimino::T, []() -> Board
		{
			Board board(3, 3);
			board.set(0, 1, Tetrimino::T);
			board.set(1, 1, Tetrimino::T);
			board.set(2, 1, Tetrimino::T);
			board.set(1, 2, Tetrimino::T);

			return board;
		}()},
		{ Tetrimino::J, []() -> Board
		{
			Board board(3, 3);
			board.set(1, 0, Tetrimino::J);
			board.set(1, 1, Tetrimino::J);
			board.set(0, 2, Tetrimino::J);
			board.set(1, 2, Tetrimino::J);

			return board;
		}()},
		{ Tetrimino::L, []() -> Board
		{
			Board board(3, 3);
			board.set(1, 0, Tetrimino::L);
			board.set(1, 1, Tetrimino::L);
			board.set(1, 2, Tetrimino::L);
			board.set(2, 2, Tetrimino::L);

			return board;
		}()},
		{ Tetrimino::S, []() -> Board
		{
			Board board(3, 3);
			board.set(1, 1, Tetrimino::S);
			board.set(2, 1, Tetrimino::S);
			board.set(1, 2, Tetrimino::S);
			board.set(0, 2, Tetrimino::S);

			return board;
		}()},
		{ Tetrimino::Z, []() -> Board
		{
			Board board(3, 3);
			board.set(0, 1, Tetrimino::Z);
			board.set(1, 1, Tetrimino::Z);
			board.set(1, 2, Tetrimino::Z);
			board.set(2, 2, Tetrimino::Z);

			return board;
		}()}
	};
}

Rotation rotate_clockwise(Rotation rotation) noexcept
{
	switch(rotation)
	{
	default:
	case Rotation::None: return Rotation::Clockwise;
	case Rotation::Clockwise: return Rotation::Half;
	case Rotation::Half: return Rotation::Counterclockwise;
	case Rotation::Counterclockwise: return Rotation::None;
	}
}

Rotation rotate_counterclockwiise(Rotation rotation) noexcept
{
	switch(rotation)
	{
	default:
	case Rotation::None: return Rotation::Counterclockwise;
	case Rotation::Clockwise: return Rotation::None;
	case Rotation::Half: return Rotation::Clockwise;
	case Rotation::Counterclockwise: return Rotation::Half;
	}
}

Board get_tetrimino(Tetrimino tetrimino) noexcept
{
	return gTetriminos[tetrimino];
}
