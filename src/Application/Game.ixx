module;

#include <concepts>

export module Game;

namespace ar {
	export
	class Game {
	public:
		// Constructor
		Game() = default;
		virtual ~Game() {};

		// Functions
		// Event functions
		virtual void fixed_update() = 0;
		virtual void update() = 0;
		virtual void late_update() = 0;
		virtual void on_render() = 0;
		virtual void on_game_pause() = 0;

		// Accessor functions
		virtual bool is_running() const = 0;
		virtual bool is_paused() const = 0;
	};

	export
	template<class T>
	concept GameType = std::derived_from<T, Game>;
}