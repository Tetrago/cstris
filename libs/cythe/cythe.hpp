#pragma once

#include <vector>

namespace cythe
{
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

	class Interface
	{
	public:
		virtual ~Interface() noexcept = default;

		virtual void left() = 0;
		virtual void right() = 0;
		virtual void drop() = 0;
		virtual void swap() = 0;

		virtual std::vector<bool> getBoard() const = 0;
		virtual Tetrimino getCurrent() const = 0;
		virtual Tetrimino getHeld() const = 0;
		virtual bool running() const = 0;

		virtual int width() const noexcept = 0;
		virtual int height() const noexcept = 0;
	};

	class Cythe
	{
	public:
		Cythe(Interface* interface) noexcept;

		void run() noexcept;
	private:
		struct Permutation
		{
			int offset;
			int score;
		};

		std::vector<Permutation> getPermutations(Tetrimino tetrimino) const noexcept;

		Interface* mInterface;
	};
}
