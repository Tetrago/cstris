#include <raylib.h>

#include <game.hpp>

constexpr Color BORDER_COLOR{ 57, 57, 57, 255 };
constexpr int BORDER_SIZE = 20;
constexpr int PIXELS_PER_UNIT = 30;
constexpr int QUEUE_LENGTH = 4;
constexpr float UI_SCALE = 0.75f;

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

void draw_ui_tetrimino(Tetrimino tetrimino, int x, int y)
{
	const Board& board = get_tetrimino(tetrimino);

	float offset = (4 - board.width()) * 0.5f + board.width() * (1 - UI_SCALE) * 0.5f;
	board.draw(x + offset * PIXELS_PER_UNIT, y + offset * PIXELS_PER_UNIT, PIXELS_PER_UNIT * UI_SCALE);
}

void draw_grid(int x, int y, int width, int height, int ppu)
{
	for(int dx = 1; dx < width; ++dx)
	{
		for(int dy = 1; dy < height; ++dy)
		{
			DrawEllipse(x + dx * ppu, y + dy * ppu, 1, 1, BORDER_COLOR);
		}
	}
}

int gFrameCount = 0;
bool gKeyPressed;
int gInputOffset = -1;

bool is_key_down(int key) noexcept
{
	if(!IsKeyDown(key)) return false;
	gKeyPressed = true;

	if(gInputOffset == -1)
		gInputOffset = gFrameCount % 4;
		
	return (gFrameCount - gInputOffset) % 4 == 0;
}

int main()
{
	Game game;

	const int width = game.board().width() * PIXELS_PER_UNIT + 4 * 2 * PIXELS_PER_UNIT + BORDER_SIZE * 2;
	const int height = game.board().height() * PIXELS_PER_UNIT + BORDER_SIZE * 2;

	InitWindow(width, height, "Cstris");
	SetTargetFPS(60);

	while(!WindowShouldClose())
	{
		if(++gFrameCount == 20)
		{
			game.step();
			gFrameCount = 0;
		}

		gKeyPressed = false;

		if(is_key_down(KEY_LEFT)) game.left();
		if(is_key_down(KEY_RIGHT)) game.right();
		if(is_key_down(KEY_DOWN)) game.down();
		if(IsKeyPressed(KEY_Z)) game.rotate();
		if(IsKeyPressed(KEY_C)) game.swap();
		if(IsKeyPressed(KEY_SPACE)) game.drop();

		if(!gKeyPressed)
			gInputOffset = -1;

		BeginDrawing();

		DrawRectangleGradientV(0, 0, width, height, { 0, 0, 0, 255, }, { 20, 20, 20, 255 });

		DrawRectangle(BORDER_SIZE, BORDER_SIZE, 4 * PIXELS_PER_UNIT, 4 * PIXELS_PER_UNIT, { 0, 0, 0, 255 });
		DrawRectangleLines(BORDER_SIZE, BORDER_SIZE, 4 * PIXELS_PER_UNIT, 4 * PIXELS_PER_UNIT, BORDER_COLOR);
		draw_ui_tetrimino(game.dropper().held(), BORDER_SIZE, BORDER_SIZE);

		DrawRectangle(BORDER_SIZE + (4 + game.board().width()) * PIXELS_PER_UNIT, BORDER_SIZE + 0, 4 * PIXELS_PER_UNIT, 4 * QUEUE_LENGTH * PIXELS_PER_UNIT, { 0, 0, 0, 255 });
		DrawRectangleLines(BORDER_SIZE + (4 + game.board().width()) * PIXELS_PER_UNIT, BORDER_SIZE + 0, 4 * PIXELS_PER_UNIT, 4 * QUEUE_LENGTH * PIXELS_PER_UNIT, BORDER_COLOR);
		for(int i = 0; i < QUEUE_LENGTH; ++i)
		{
			draw_ui_tetrimino(game.dropper().bag()[game.dropper().bag().size() - i - 1], BORDER_SIZE + (4 + game.board().width()) * PIXELS_PER_UNIT, BORDER_SIZE + i * 4 * PIXELS_PER_UNIT);
		}

		DrawRectangle(BORDER_SIZE + 4 * PIXELS_PER_UNIT, BORDER_SIZE, game.board().width() * PIXELS_PER_UNIT, game.board().height() * PIXELS_PER_UNIT, { 0, 0, 0, 255 });
		DrawRectangleLines(BORDER_SIZE + 4 * PIXELS_PER_UNIT, BORDER_SIZE, game.board().width() * PIXELS_PER_UNIT, game.board().height() * PIXELS_PER_UNIT, BORDER_COLOR);
		draw_grid(BORDER_SIZE + 4 * PIXELS_PER_UNIT, BORDER_SIZE, game.board().width(), game.board().height(), PIXELS_PER_UNIT);
		game.draw(BORDER_SIZE + 4 * PIXELS_PER_UNIT, BORDER_SIZE);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}