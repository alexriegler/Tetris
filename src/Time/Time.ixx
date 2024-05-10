export module Time;

import std;

namespace ar
{
export auto GetTimeNow()
{
    return std::chrono::steady_clock::now();
}

export auto since(const std::chrono::steady_clock::time_point& start)
{
    const auto now = GetTimeNow();
    const auto duration = now - start;
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration);
}
}  // namespace ar