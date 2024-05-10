export module Application;

export import Game;
export import Renderer;

namespace ar
{
export template<Game G, Renderer R>
class Application
{
public:
    // Constructor
    // TODO: Add constructor for game so that commandline options can be passed to it

    // Functions
    void run()
    {
        while (mGame.is_running())
        {
            mGame.fixed_update();
            mGame.update();
            mGame.late_update();

            for (const auto& drawableVar : mGame.get_drawables())
            {
                std::visit(
                    [this](auto&& drawable)
                    {
                        auto& ref = drawable.get();
                        this->mRenderer.draw(ref);
                    },
                    drawableVar);
            }
            mRenderer.draw_frame();

            if (mGame.is_paused())
            {
                mGame.on_game_pause();
            }
        }
    }

private:
    // Data
    G mGame{};
    R mRenderer{};
};
}  // namespace ar
