export module Score;

import Drawable;

import std;

namespace ar
{
export class Score : public Drawable
{
public:
    ~Score() { std::println("Game Over! Score: {}", mScore); }

    void AddPoints(int points) { mScore += points; }

    void AddPointsPerLine(int lines)
    {
        // Lines are worth: lines^2 * 100
        mScore += (1 << lines) * 100;
    }

    auto GetScore() const { return mScore; }

private:
    int mScore{0};
};
}  // namespace ar