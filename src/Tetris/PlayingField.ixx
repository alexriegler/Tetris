export module PlayingField;

import TetrominoObject;
import Drawable;

import std;

namespace ar
{
export class PlayingField : public Drawable
{
public:
    static constexpr auto defaultFieldWidth = 10;
    static constexpr auto defaultFieldHeight = 20;

    using PixelType = unsigned char;
    using FieldBuffer = std::array<PixelType, defaultFieldWidth * defaultFieldHeight>;

    PlayingField()
    {
        // Create playing field boundary
        for (int x = 0; x < mFieldWidth; x++)
        {
            for (int y = 0; y < mFieldHeight; y++)
            {
                // TODO: Fix space representation
                // TODO: Can this just set 9/borders since brace init is used?
                // 9 represents a border
                // 0 represents a empty space
                mField[y * mFieldWidth + x] = (x == 0 || x == mFieldWidth - 1 || y == mFieldHeight - 1) ? 9 : 0;
            }
        }
    }

    bool TryMovePieceRight()
    {
        if (DoesPieceFit(mCurrentPiece.mX + 1, mCurrentPiece.mY, mCurrentPiece.mRotation))
        {
            ++mCurrentPiece.mX;
            return true;
        }
        return false;
    }

    bool TryMovePieceLeft()
    {
        if (DoesPieceFit(mCurrentPiece.mX - 1, mCurrentPiece.mY, mCurrentPiece.mRotation))
        {
            mCurrentPiece.mX--;
            return true;
        }
        return false;
    }

    bool TryMovePieceDown()
    {
        if (DoesPieceFit(mCurrentPiece.mX, mCurrentPiece.mY + 1, mCurrentPiece.mRotation))
        {
            mCurrentPiece.mY++;
            return true;
        }
        return false;
    }

    // TODO: Verify that this is actually rotating clockwise
    bool TryRotatePieceClockwise()
    {
        if (DoesPieceFit(mCurrentPiece.mX, mCurrentPiece.mY, mCurrentPiece.mRotation + 1))
        {
            mCurrentPiece.mRotation++;
            return true;
        }
        return false;
    }

    void LockPiece()
    {
        // Lock the current piece in the field
        for (int px = 0; px < 4; px++)
        {
            for (int py = 0; py < 4; py++)
            {
                if (mCurrentPiece[Rotate(px, py, mCurrentPiece.mRotation)] == L'X')
                {
                    SetPixel(mCurrentPiece.mX + px, mCurrentPiece.mY + py, mCurrentPiece.mPiece.id);
                }
            }
        }
    }

    auto CountLines()
    {
        // Check for horizontal lines
        // Check 4 rows of tetromino for lines
        for (int py = 0; py < 4; py++)
        {
            // Boundary check
            if (mCurrentPiece.mY + py < mFieldHeight - 1)
            {
                bool bLine = true;
                // Exclude first and last column in check (since they are empty)
                for (int px = 1; px < mFieldWidth - 1; px++)
                {
                    bLine &= (mField[(mCurrentPiece.mY + py) * mFieldWidth + px]) != 0;
                }

                if (bLine)
                {
                    // Remove line (set to '=')
                    for (int px = 1; px < mFieldWidth - 1; px++)
                    {
                        // TODO: Change constant 8 to enum or something
                        mField[(mCurrentPiece.mY + py) * mFieldWidth + px] = 8;
                    }

                    mLines.push_back(mCurrentPiece.mY + py);
                }
            }
        }
        return mLines.size();
    }

    auto& GetLines() { return mLines; }

    void ResetPiece(const Tetromino& tetromino)
    {
        // Choose the next piece and reset the piece position and rotation
        mCurrentPiece.mPiece = tetromino;
        mCurrentPiece.mX = mFieldWidth / 2 - 2;
        mCurrentPiece.mY = 0;
        mCurrentPiece.mRotation = 0;
    }

    bool IsCurrentPieceInBounds() const
    {
        return DoesPieceFit(mCurrentPiece.mX, mCurrentPiece.mY, mCurrentPiece.mRotation);
    }

    int GetFieldWidth() const { return mFieldWidth; }
    int GetFieldHeight() const { return mFieldHeight; }
    const FieldBuffer& GetField() const { return mField; }

    PixelType operator()(int x, int y) const { return mField[y * mFieldWidth + x]; }
    PixelType& operator()(int x, int y) { return mField[y * mFieldWidth + x]; }
    PixelType& operator[](int index) { return mField[index]; }

    const TetrominoObject& GetCurrentPiece() const { return mCurrentPiece; }

private:
    void SetPixel(int x, int y, PixelType newValue) { mField[y * mFieldWidth + x] = newValue; }

    /// <summary>
    /// Checks whether the current piece fits in a given location.
    /// </summary>
    /// <param name="nPosX">The x position of the top left corner of the tetromino.</param>
    /// <param name="nPosY">The y position of the top left corner of the tetromino.</param>
    /// <param name="nRotation">The degree of rotation: 0 = none, 1 = 90, 2 = 180, 3 = 270.</param>
    /// <returns>True, if the piece fits; false, otherwise.</returns>
    bool DoesPieceFit(int nPosX, int nPosY, int nRotation) const
    {
        for (int px = 0; px < 4; px++)
        {
            for (int py = 0; py < 4; py++)
            {
                // Get index into piece
                int pi = Rotate(px, py, nRotation);

                // Get index into field
                int fi = (nPosY + py) * mFieldWidth + (nPosX + px);

                // Check array bounds
                if (nPosX + px >= 0 && nPosX + px < mFieldWidth)
                {
                    if (nPosY + py >= 0 && nPosY + py < mFieldHeight)
                    {
                        // Detect collision (check if piece fits in location
                        if (mCurrentPiece[pi] == L'X' && mField[fi] != 0)
                        {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    // Field info
    const int mFieldWidth{defaultFieldWidth};
    const int mFieldHeight{defaultFieldHeight};
    FieldBuffer mField{};

    TetrominoObject mCurrentPiece{.mPiece = {}, .mX = defaultFieldWidth / 2 - 2, .mY = 0, .mRotation = {}};

    std::vector<int> mLines{};  // Number of lines cleared
};
}  // namespace ar