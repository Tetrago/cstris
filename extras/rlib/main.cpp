#include <raylib.h>

#include <game.hpp>

constexpr Color BORDER_COLOR{ 129, 129, 129, 255 };
constexpr int PIXELS_PER_UNIT = 30;
constexpr int QUEUE_LENGTH = 4;

Color get_tetrimino_color(Tetrimino tetrimino) noexcept
{
	switch(tetrimino)
	{
	default:
	case Tetrimino::None: return Color{ 0, 0, 0, 255 };
	case Tetrimino::I: return Color{ 0, 255, 255, 255 };
	case Tetrimino::O: return Color{ 255, 255, 0, 255 };
	case Tetrimino::T: return Color{ 255, 0, 255, 255 };
	case Tetrimino::J: return Color{ 0, 0, 255, 255 };
	case Tetrimino::L: return Color{ 255, 129, 0, 255 };
	case Tetrimino::S: return Color{ 0, 255, 0, 255 };
	case Tetrimino::Z: return Color{ 255, 0, 0, 255 };
	}
}

void cstris_draw_block(int x, int y, int size, Tetrimino tetrimino, bool ghost)
{
	Color color = get_tetrimino_color(tetrimino);
	if(ghost)
	{
		color.a = 129;
	}

	DrawRectangle(x, y, size, size, color);
}

void draw_centered(Tetrimino tetrimino, int x, int y)
{
	const Board& board = get_tetrimino(tetrimino);

	float offset = (4 - board.width()) * 0.5f;
	board.draw(x + offset * PIXELS_PER_UNIT, y + offset * PIXELS_PER_UNIT, PIXELS_PER_UNIT);
}

int gFrameCount = 0;
int gLastKey = -1;
int gInputOffset;

bool is_key_down(int key) noexcept
{
	if(gLastKey != key)
	{
		if(!IsKeyDown(key)) return false;

		gLastKey = key;
		gInputOffset = gFrameCount % 3;

		return true;
	}
	else
	{
		if(!IsKeyDown(key))
		{
			gLastKey = -1;
			return false;
		}

		return (gFrameCount + gInputOffset) % 3 == 0;
	}
}

int main()
{
	Game game;

	InitWindow(game.board().width() * PIXELS_PER_UNIT + 4 * 2 * PIXELS_PER_UNIT, game.board().height() * PIXELS_PER_UNIT, "Cstris");
	SetTargetFPS(60);

	while(!WindowShouldClose())
	{
		if(++gFrameCount == 20)
		{
			game.step();
			gFrameCount = 0;
		}

		if(is_key_down(KEY_LEFT)) game.left();
		if(is_key_down(KEY_RIGHT)) game.right();
		if(is_key_down(KEY_DOWN)) game.down();
		if(IsKeyPressed(KEY_Z)) game.rotate();
		if(IsKeyPressed(KEY_C)) game.swap();
		if(IsKeyPressed(KEY_SPACE)) game.drop();

		BeginDrawing();

		ClearBackground({ 0, 0, 0, 255 });

		DrawRectangleLines(0, 0, 4 * PIXELS_PER_UNIT, 4 * PIXELS_PER_UNIT, BORDER_COLOR);
		draw_centered(game.dropper().held(), 0, 0);

		DrawRectangleLines((4 + game.board().width()) * PIXELS_PER_UNIT, 0, 4 * PIXELS_PER_UNIT, 4 * QUEUE_LENGTH * PIXELS_PER_UNIT, BORDER_COLOR);
		for(int i = 0; i < QUEUE_LENGTH; ++i)
		{
			draw_centered(game.dropper().bag()[game.dropper().bag().size() - i - 1], (4 + game.board().width()) * PIXELS_PER_UNIT, i * 4 * PIXELS_PER_UNIT);
		}

		DrawRectangleLines(4 * PIXELS_PER_UNIT, 0, game.board().width() * PIXELS_PER_UNIT, game.board().height() * PIXELS_PER_UNIT, BORDER_COLOR);
		game.draw(4 * PIXELS_PER_UNIT, 0);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}