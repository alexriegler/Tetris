export module RandomGenerator;

import Tetromino;

namespace ar
{
export class RandomGenerator
{
public:
    virtual Tetromino next() = 0;
};
}  // namespace ar
