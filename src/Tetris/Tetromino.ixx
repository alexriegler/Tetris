export module Tetromino;

import std;

namespace ar
{
export struct Tetromino
{
    enum class Shape
    {
        I,
        J,
        L,
        O,
        S,
        Z,
        T
    };

    // Constructors
    Tetromino() = default;

    Tetromino(Shape shape, wchar_t symbol, int id, const std::wstring& piece)
        : mShape{shape}
        , mSymbol{symbol}
        , mId{id}
        , mPiece{piece}
    {
    }

    // Functions
    const wchar_t operator[](int idx) const { return mPiece[idx]; }

    // Data
    Shape mShape{};
    wchar_t mSymbol{};
    int mId{};
    std::wstring mPiece{};
};

#pragma region Tetromino wstrings
const std::wstring Ipiece{
    L"...."
    L"...."
    L"XXXX"
    L"...."};

const std::wstring Jpiece{
    L"...."
    L"X..."
    L"XXX."
    L"...."};

const std::wstring Lpiece{
    L"...."
    L"..X."
    L"XXX."
    L"...."};

const std::wstring Opiece{
    L"...."
    L".XX."
    L".XX."
    L"...."};

const std::wstring Spiece{
    L"...."
    L".XX."
    L"XX.."
    L"...."};

const std::wstring Zpiece{
    L"...."
    L"XX.."
    L".XX."
    L"...."};

const std::wstring Tpiece{
    L"...."
    L".X.."
    L"XXX."
    L"...."};
#pragma endregion

const Tetromino I_tetro{Tetromino::Shape::I, L'A', 1, Ipiece};
const Tetromino J_tetro{Tetromino::Shape::J, L'B', 2, Jpiece};
const Tetromino L_tetro{Tetromino::Shape::L, L'C', 3, Lpiece};
const Tetromino O_tetro{Tetromino::Shape::O, L'D', 4, Opiece};
const Tetromino S_tetro{Tetromino::Shape::S, L'E', 5, Spiece};
const Tetromino Z_tetro{Tetromino::Shape::Z, L'F', 6, Zpiece};
const Tetromino T_tetro{Tetromino::Shape::T, L'G', 7, Tpiece};

export const std::array defaultTetrominoSet = {I_tetro, J_tetro, L_tetro, O_tetro, S_tetro, Z_tetro, T_tetro};
}  // namespace ar
