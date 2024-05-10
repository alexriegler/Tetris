export module TetrominoObject;

export import Tetromino;

namespace ar
{
export struct TetrominoObject
{
    const auto operator[](int index) const { return mPiece[index]; }

    Tetromino mPiece{};
    int mX{};
    int mY{};
    int mRotation{};
};
}  // namespace ar
