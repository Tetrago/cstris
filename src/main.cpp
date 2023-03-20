#include <raylib.h>

#include "game.hpp"

int main()
{
	Game game;

	InitWindow(game.board().width() * 30, game.board().height() * 30, "Cstris");
	SetTargetFPS(60);

	while(!WindowShouldClose())
	{
		if(IsKeyDown(KEY_S))
		{
			game.step();
		}

		if(IsKeyPressed(KEY_LEFT)) game.left();
		if(IsKeyPressed(KEY_RIGHT)) game.right();
		if(IsKeyPressed(KEY_Z)) game.rotate();
		if(IsKeyPressed(KEY_SPACE)) game.drop();

		BeginDrawing();
		ClearBackground({ 0, 0, 0, 255 });
		game.draw(0, 0);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}