export module RandomGenerator;

import Tetromino;

namespace ar
{
// TODO: Switch to concept?
export class RandomGenerator
{
public:
    virtual Tetromino next() = 0;
};
}  // namespace ar
