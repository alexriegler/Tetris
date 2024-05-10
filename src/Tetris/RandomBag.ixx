export module RandomBag;

import RandomGenerator;
import Tetromino;

import std;

namespace ar
{
static constexpr int s_bag_size = 7;

export class RandomBag : public RandomGenerator
{
public:
    // Constructor
    RandomBag()
        : m_bag {default_tetromino_set}
        , m_count {s_bag_size}
        , m_swap_bag {}
        , m_swap_count {0}
        , m_use_swap_bag {false}
        , seed {static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count())}
    {
        std::shuffle(m_bag.begin(), m_bag.end(), std::default_random_engine(seed));
    }

    // Functions
    /// <summary>
    /// Returns the next random tetromino from the bag.
    /// </summary>
    /// <returns>The next random tetromino.</returns>
    Tetromino next() override
    {
        if (m_use_swap_bag)
        {
            if (m_swap_count == 0)
            {
                m_bag = default_tetromino_set;
                m_count = s_bag_size;
                std::shuffle(m_bag.begin(), m_bag.end(), std::default_random_engine(seed));
                m_use_swap_bag = false;
                return grab_from_bag();
            }
            else
            {
                return grab_from_swap();
            }
        }
        else
        {
            if (m_count == 0)
            {
                m_swap_bag = default_tetromino_set;
                m_swap_count = s_bag_size;
                std::shuffle(m_swap_bag.begin(), m_swap_bag.end(), std::default_random_engine(seed));
                m_use_swap_bag = true;
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
        if (m_bag.empty())
        {
            throw std::runtime_error("Can't grab from an empty bag!");
        }
        Tetromino& tetromino = m_bag[m_count - 1];
        m_count--;
        return tetromino;
    }

    /// <summary>
    /// Returns the next tetromino from the swap bag.
    /// </summary>
    /// <returns>The next tetromino from the swap bag.</returns>
    Tetromino& grab_from_swap()
    {
        if (m_bag.empty())
        {
            throw std::runtime_error("Can't grab from an empty bag!");
        }
        Tetromino& tetromino = m_swap_bag[m_swap_count - 1];
        m_swap_count--;
        return tetromino;
    }

    // Data
    std::array<Tetromino, s_bag_size> m_bag;
    int m_count;

    std::array<Tetromino, s_bag_size> m_swap_bag;
    int m_swap_count;

    bool m_use_swap_bag;

    unsigned int seed;
};
}  // namespace ar
