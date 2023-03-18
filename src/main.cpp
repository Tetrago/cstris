#include <raylib.h>

#include "board.hpp"

int main()
{
	Board board;

	InitWindow(board.width() * 30, board.height() * 30, "Cstris");
	SetTargetFPS(60);

	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		board.draw(0, 0);

		get_tetrimino(Tetrimino::J).rotate(Rotation::Clockwise).draw(0, 0);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}