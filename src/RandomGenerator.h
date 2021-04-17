#pragma once
#include "Tetromino.h"

namespace ar {
	class RandomGenerator
	{
	public:
		virtual Tetromino& next() = 0;
	};
}