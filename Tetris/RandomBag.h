#pragma once

#include "RandomGenerator.h"
#include "Tetromino.h"
#include <array>

namespace Tetris
{
	class RandomBag : public RandomGenerator 
	{
	public:
		// Constructor
		RandomBag();
		
		// Functions
		Tetromino& next() override;

	private:
		// Functions
		Tetromino& grab_from_bag();
		Tetromino& grab_from_swap();

		// Data
		static constexpr int s_bag_size = 7;
		std::array<Tetromino, s_bag_size> m_bag;
		int m_count;

		std::array<Tetromino, s_bag_size> m_swap_bag;
		int m_swap_count;

		bool m_use_swap_bag;

		unsigned int seed;
	};
}