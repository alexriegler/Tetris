#pragma once

#include "Game.h"

namespace ar {
	class Application {
	public:
		// Constructor
		Application() : m_game{} {}

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
		Game m_game;
	};
}