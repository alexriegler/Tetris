export module Renderer;

import Drawable;

import std;

namespace ar
{
export template<typename T>
concept Renderer = requires(T t, Drawable& d) {
    {
        t.draw(d)
    } -> std::same_as<void>;
    {
        t.draw_frame()
    } -> std::same_as<void>;
};
}  // namespace ar