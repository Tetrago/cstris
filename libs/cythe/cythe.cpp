#include "cythe.hpp"

#include <numeric>

namespace cythe
{
	Cythe::Cythe(Interface* interface) noexcept
		: mInterface(interface)
	{}

	void Cythe::run() noexcept
	{
		if(mInterface->getHeld() == Tetrimino::None)
		{
			mInterface->swap();
		}

		while(mInterface->running())
		{
			auto permutations = getPermutations(mInterface->getCurrent());
			auto held = getPermutations(mInterface->getHeld());

			int div = permutations.size();
			permutations.insert(permutations.end(), held.begin(), held.end());

			int index = 0;
			int score = std::numeric_limits<int>::max();
			int offset = 0;

			for(int i = 0; i < permutations.size(); ++i)
			{
				const auto& p = permutations[i];
				if(p.score <= score) continue;

				index = i;
				score = p.score;
				offset = p.offset;
			}

			if(index >= div)
				mInterface->swap();

			while(offset != 0)
			{
				if(offset > 0)
					mInterface->right();
				else
					mInterface->left();
			}

			mInterface->drop();
		}
	}

	std::vector<Cythe::Permutation> Cythe::getPermutations(Tetrimino tetrimino) const noexcept
	{

	}
}
