#pragma once

#include <concepts>

namespace ar {
	class Game {
	public:
		// Constructor
		Game() = default;
		virtual ~Game() {};

		// Functions
		// Event functions
		virtual void fixed_update() = 0;

		// TODO: Need these?
		//void update();
		//void late_update();

		virtual void on_render() = 0;

		// TODO: Need this?
		//void on_game_pause();

		// Accessor functions
		virtual bool is_running() const = 0;
		virtual bool is_paused() const = 0;
	};

	template<class T>
	concept GameType = std::derived_from<T, Game>;
}