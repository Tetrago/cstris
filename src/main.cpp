#include <raylib.h>

#include "board.hpp"
#include "dropper.hpp"

int main()
{
	Board board;
	Dropper dropper(&board);

	dropper.piece(Tetrimino::J);

	InitWindow(board.width() * 30, board.height() * 30, "Cstris");
	SetTargetFPS(60);

	while(!WindowShouldClose())
	{
		if(IsKeyDown(KEY_S))
		{
			dropper.step();
		}

		if(IsKeyPressed(KEY_LEFT)) dropper.shift(-1);
		if(IsKeyPressed(KEY_RIGHT)) dropper.shift(1);
		if(IsKeyPressed(KEY_Z)) dropper.rotate();
		if(IsKeyPressed(KEY_SPACE)) dropper.drop();

		BeginDrawing();
		ClearBackground(RAYWHITE);

		board.draw(0, 0);
		dropper.draw();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}