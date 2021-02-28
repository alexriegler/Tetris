#pragma once
#include "Tetromino.h"

namespace Tetris
{
	class RandomGenerator
	{
	public:
		virtual Tetromino& next() = 0;
	};
}