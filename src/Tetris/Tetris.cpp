module;

#include <Windows.h>
#include <wchar.h>

module Tetris;

import Drawable;

import std;

namespace ar
{
// Public functions
// Constructor
Tetris::Tetris()
{
    mPlayingField.ResetPiece(mRandomBag.next());

    mDrawables.emplace_back(mPlayingField);
    mDrawables.emplace_back(mScore);
}

// Functions
void Tetris::fixed_update()
{
    // GAME TIMING ===========================================
    // TODO: Fix hack for fixed update
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(50ms);
    mSpeedCounter++;
    mForceDown = (mSpeedCounter == mSpeed);

    // INPUT =================================================
    // TODO: Add up arrow for hard drop
    for (int k = 0; k < 4; k++)
    {
        // \x27		= Right arrow	VK_RIGHT
        // \x25		= Left arrow	VK_LEFT
        // \x28		= Down arrow	VK_DOWN
        // Z		= Z (rotate)	0x5A
        mKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;
    }

    // GAME LOGIC ============================================
    // Player movement
    // Right key pressed
    if (mKey[0])
    {
        mPlayingField.TryMovePieceRight();
    }
    // Left key pressed
    if (mKey[1])
    {
        mPlayingField.TryMovePieceLeft();
    }
    // Down key pressed
    if (mKey[2])
    {
        mPlayingField.TryMovePieceDown();
    }
    // Z key pressed (rotate)
    // Latches the rotation so that it does spin repetitively
    if (mKey[3])
    {
        if (!mRotateHold)
        {
            mPlayingField.TryRotatePieceClockwise();
        }
        mRotateHold = true;
    }
    else
    {
        mRotateHold = false;
    }

    // Game movement
    // If it's time to force the tetromino down
    if (mForceDown)
    {
        // Move piece down if it fits
        if (not mPlayingField.TryMovePieceDown())
        {
            mPlayingField.LockPiece();

            // Score
            mScore.AddPoints(25);
            if (const auto lines = mPlayingField.CountLines(); lines > 0)
            {
                mScore.AddPointsPerLine(static_cast<int>(lines));
            }

            mPlayingField.ResetPiece(mRandomBag.next());

            // Game continues if the pieces fits
            mIsRunning = mPlayingField.IsCurrentPieceInBounds();

            // Increment piece count and decrease ticks required to move piece (i.e., move faster)
            mPieceCount++;
            if (mPieceCount % 10 == 0)
            {
                if (mSpeed >= 10)
                {
                    mSpeed--;
                }
            }
        }

        mSpeedCounter = 0;
    }
}

// Does nothing
void Tetris::update()
{
    return;
}

// Does nothing
void Tetris::late_update()
{
    return;
}

// Does nothing
void Tetris::on_game_pause()
{
    return;
}

bool Tetris::is_running() const noexcept
{
    return mIsRunning;
}

bool Tetris::is_paused() const noexcept
{
    return mIsPaused;
}

Tetris::DrawableList Tetris::get_drawables() const
{
    return mDrawables;
}
}  // namespace ar
