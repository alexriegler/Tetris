#pragma once

#include "Game.h"

namespace ar {
	template<GameType T>
	class Application {
	public:
		// Constructor
		Application() : m_game{} {}
		// TODO: Add ability to construct application from game so that commandline options can be passed to it

		// Function
		void run() {
			while (m_game.is_running()) {
				m_game.fixed_update();

				/*m_game.update();
				m_game.late_update();*/

				m_game.on_render();

				/*if (m_game.is_paused()) {
					m_game.on_game_pause();
				}*/
			}
		}

	private:
		// Data
		T m_game;
	};
}