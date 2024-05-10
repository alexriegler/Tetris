module;

#include <Windows.h>

export module Tetris;

export import Application;

import Drawable;
import Game;
import KeyboardInput;
import PlayingField;
import RandomBag;
import Score;
import Tetromino;

import std;

namespace ar
{
export class Tetris
{
public:
    // Type aliases
    template<typename... Types>
    using VariantOfReferences = std::variant<std::reference_wrapper<Types>...>;
    using Drawable = VariantOfReferences<PlayingField, Score>;
    using DrawableList = std::vector<Drawable>;

    // Constructor
    Tetris();

    // Functions
    // Event functions
    void fixed_update();
    void update();
    void late_update();
    void on_game_pause();

    // State functions
    bool is_running() const noexcept;
    bool is_paused() const noexcept;

    // Drawing functions
    DrawableList get_drawables() const;

private:
    // Data
    // Game state
    bool mIsRunning{true};
    bool mIsPaused{false};
    float mFixedDeltaTime{0.0f};
    float mDeltaTime{0.0f};

    // Game difficulty
    int mSpeed{20};
    int mSpeedCounter{0};
    bool mForceDown{false};
    int mPieceCount{0};

    // Input
    KeyboardInput mKeyboard{};

    RandomBag mRandomBag{};
    PlayingField mPlayingField{};
    Score mScore{};

    DrawableList mDrawables{};
};

static_assert(Game<Tetris>);
}  // namespace ar
