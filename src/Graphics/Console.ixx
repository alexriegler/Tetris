module;

#include <Windows.h>
#include <wchar.h>

export module Console;

import Renderer;

import Drawable;
import PlayingField;
import Tetromino;
import Score;

import std;

namespace ar
{
export class Console
{
public:
    Console()
    {
        // Setup console to be used as screen buffer
        std::ranges::fill(mScreen, L' ');

        mConsoleHandle =
            CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        SetConsoleActiveScreenBuffer(mConsoleHandle);
    }

    ~Console()
    {
        // NOTE: The console handle must be closed before writing to std::cout.
        CloseHandle(mConsoleHandle);
    }

    void draw(Drawable&) { throw std::runtime_error("Not implemented!"); }

    void draw(PlayingField& playingField)
    {
        // Draw playing field
        for (int x = 0; x < playingField.GetFieldWidth(); ++x)
        {
            for (int y = 0; y < playingField.GetFieldHeight(); ++y)
            {
                // Symbol key:
                // Index	Char	Represents
                // ______________________________
                //   0	|	( )	  |	empty space
                //  1-7	|  (A-G)  |	tetrominoes
                //   8	|	(=)	  |	   line
                //   9	|	(#)	  |	  border
                mScreen[(y + 2) * mScreenWidth + (x + 2)] = L" ABCDEFG=#"[playingField(x, y)];
            }
        }

        // Draw current piece
        for (int px = 0; px < 4; px++)
        {
            for (int py = 0; py < 4; py++)
            {
                const auto& piece = playingField.GetCurrentPiece();
                if (piece[Rotate(px, py, piece.mRotation)] == L'X')
                {
                    mScreen[(piece.mY + py + 2) * mScreenWidth + (piece.mX + px + 2)] = piece.mPiece.symbol;
                }
            }
        }

        // Draw line animation
        // TODO: Don't do game logic in render
        auto& lines = playingField.GetLines();
        if (lines.size() > 0)
        {
            // Display frame (hacky draw lines)
            WriteConsoleOutputCharacter(
                mConsoleHandle, mScreen.data(), mScreenWidth * mScreenHeight, {0, 0}, &mBytesWritten);

            // For ms suffix
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(400ms);  // Delay a bit

            // Move lines down
            for (auto v : lines)
            {
                for (int px = 1; px < playingField.GetFieldWidth() - 1; ++px)
                {
                    for (int py = v; py > 0; py--)
                    {
                        playingField(px, py) = playingField(px, py - 1);
                    }
                    playingField[px] = 0;
                }
            }

            lines.clear();
        }
    }

    void draw(const Score& score)
    {
        // Draw score
        // TODO: dont use magic numbers
        // TODO: Create layout manager
        swprintf_s(&mScreen[2 * mScreenWidth + 10 + 6], 16, L"SCORE: %8d", score.GetScore());
    }

    void draw_frame()
    {
        // Display frame
        WriteConsoleOutputCharacter(
            mConsoleHandle, mScreen.data(), mScreenWidth * mScreenHeight, {0, 0}, &mBytesWritten);
    }

private:
    static constexpr auto defaultScreenWidth = 120;
    static constexpr auto defaultScreenHeight = 30;
    using ConsoleBuffer = std::array<wchar_t, defaultScreenWidth * defaultScreenHeight>;

    int mScreenWidth{defaultScreenWidth};    // Console screen size x (columns)
    int mScreenHeight{defaultScreenHeight};  // Console screen size y (rows)
    ConsoleBuffer mScreen{};                 // Console screen to be used as screen buffer

    HANDLE mConsoleHandle{nullptr};

    DWORD mBytesWritten{0};
};

static_assert(Renderer<Console>);
}  // namespace ar
