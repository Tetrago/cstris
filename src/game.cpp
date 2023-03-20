#include "game.hpp"

Game::Game(int width, int height) noexcept
	: mBoard(width, height)
	, mDropper(&mBoard)
{}

void Game::step() noexcept
{
	mDropper.step();
}

void Game::left() noexcept
{
	mDropper.shift(-1);
}

void Game::right() noexcept
{
	mDropper.shift(1);
}

void Game::rotate() noexcept
{
	mDropper.rotate();
}

void Game::down() noexcept
{
	mDropper.step();
}

void Game::drop() noexcept
{
	mDropper.drop();
}

void Game::draw(int x, int y, int ppu) const noexcept
{
	mBoard.draw(x, y, ppu);
	mDropper.draw(x, y, ppu);
}
