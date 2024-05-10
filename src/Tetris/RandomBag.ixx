export module RandomBag;

import RandomGenerator;
import Tetromino;

import std;

namespace ar
{
export class RandomBag : public RandomGenerator
{
public:
    // Constructor
    RandomBag()
        : mBag{defaultTetrominoSet}
        , mCount{bagSize}
        , mSwapBag{}
        , mSwapCount{0}
        , mUseSwapBag{false}
        , mSeed{static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count())}
    {
        std::shuffle(mBag.begin(), mBag.end(), std::default_random_engine(mSeed));
    }

    // Functions
    /// <summary>
    /// Returns the next random tetromino from the bag.
    /// </summary>
    /// <returns>The next random tetromino.</returns>
    Tetromino next() override
    {
        if (mUseSwapBag)
        {
            if (mSwapCount == 0)
            {
                mBag = defaultTetrominoSet;
                mCount = bagSize;
                std::shuffle(mBag.begin(), mBag.end(), std::default_random_engine(mSeed));
                mUseSwapBag = false;
                return grab_from_bag();
            }
            else
            {
                return grab_from_swap();
            }
        }
        else
        {
            if (mCount == 0)
            {
                mSwapBag = defaultTetrominoSet;
                mSwapCount = bagSize;
                std::shuffle(mSwapBag.begin(), mSwapBag.end(), std::default_random_engine(mSeed));
                mUseSwapBag = true;
                return grab_from_swap();
            }
            else
            {
                return grab_from_bag();
            }
        }
    }

private:
    // Functions
    /// <summary>
    /// Returns the next tetromino from the main bag.
    /// </summary>
    /// <returns>The next tetromino from the main bag.</returns>
    Tetromino& grab_from_bag()
    {
        if (mBag.empty())
        {
            throw std::runtime_error("Can't grab from an empty bag!");
        }
        Tetromino& tetromino = mBag[mCount - 1];
        mCount--;
        return tetromino;
    }

    /// <summary>
    /// Returns the next tetromino from the swap bag.
    /// </summary>
    /// <returns>The next tetromino from the swap bag.</returns>
    Tetromino& grab_from_swap()
    {
        if (mBag.empty())
        {
            throw std::runtime_error("Can't grab from an empty bag!");
        }
        Tetromino& tetromino = mSwapBag[mSwapCount - 1];
        mSwapCount--;
        return tetromino;
    }

    static constexpr int bagSize = 7;
    using Bag = std::array<Tetromino, bagSize>;

    // Data
    Bag mBag;
    int mCount;

    Bag mSwapBag;
    int mSwapCount;

    bool mUseSwapBag;

    unsigned int mSeed;
};
}  // namespace ar
