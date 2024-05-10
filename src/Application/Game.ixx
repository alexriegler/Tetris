export module Game;

import Drawable;

import std;

namespace ar
{
export template<class T>
concept Game = requires(T t, const T constT) {
    // Event functions
    {
        t.fixed_update()
    } -> std::same_as<void>;
    {
        t.update()
    } -> std::same_as<void>;
    {
        t.late_update()
    } -> std::same_as<void>;
    {
        t.on_game_pause()
    } -> std::same_as<void>;

    // Accessor functions
    {
        constT.is_running()
    } -> std::same_as<bool>;
    {
        constT.is_paused()
    } -> std::same_as<bool>;

    // Drawing
    constT.get_drawables();
    // TODO: Add return type checking for get_drawables
    // std::visit([]() {}, std::declval<decltype(constT.get_drawables())::value_type>());
};
}  // namespace ar
