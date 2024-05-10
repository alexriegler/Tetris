module;

#include <Windows.h>

export module KeyboardInput;

import Time;

import std;

namespace ar
{
export enum class Key : int
{
    RightArrow = VK_RIGHT,
    LeftArrow = VK_LEFT,
    DownArrow = VK_DOWN,
    UpArrow = VK_UP,
    ZKey = 'Z'
};

struct KeyState
{
    enum class State
    {
        None,
        Pressed,
        Held,
        Released
    };

    State mState{State::None};
    std::chrono::steady_clock::time_point mStartTime{};
};

export class KeyboardInput
{
public:
    void RegisterKey(Key key) { mKeyStates.insert({key, {}}); }

    void ProcessInput()
    {
        for (auto& [key, state] : mKeyStates)
        {
            const auto currentState = (0x8000 & GetAsyncKeyState(std::to_underlying(key))) != 0;
            if (currentState)
            {
                switch (state.mState)
                {
                    using enum KeyState::State;
                    case None:
                        state.mState = Pressed;
                        state.mStartTime = GetTimeNow();
                        break;
                    case Pressed:
                        state.mState = Held;
                        state.mStartTime = GetTimeNow();
                        break;
                    case Held:
                        // No change
                        break;
                    case Released:
                        state.mState = Pressed;
                        state.mStartTime = GetTimeNow();
                        break;
                }
            }
            else
            {
                switch (state.mState)
                {
                    using enum KeyState::State;
                    case None:
                        // No change
                        break;
                    case Pressed:
                        state.mState = Released;
                        state.mStartTime = GetTimeNow();
                        break;
                    case Held:
                        state.mState = Released;
                        state.mStartTime = GetTimeNow();
                        break;
                    case Released:
                        state.mState = None;
                        state.mStartTime = GetTimeNow();
                        break;
                }
            }
        }
    }

    bool KeyPressed(Key key) { return mKeyStates.at(key).mState == KeyState::State::Pressed; }
    bool KeyHeld(Key key) { return mKeyStates.at(key).mState == KeyState::State::Held; }

    bool KeyHeldFor(Key key, const std::chrono::milliseconds& duration)
    {
        const auto& [state, time] = mKeyStates.at(key);
        const bool keyHeld = state == KeyState::State::Held;
        const bool timeElapsed = since(time) >= duration;
        return keyHeld and timeElapsed;
    }
    bool KeyReleased(Key key) { return mKeyStates.at(key).mState == KeyState::State::Released; }

private:
    std::map<Key, KeyState> mKeyStates{};
};
}  // namespace ar