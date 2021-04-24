export module Application;

export import Game;

namespace ar {
	export
	template<GameType T>
	class Application {
	public:
		// Constructor
		// TODO: Add constructor for game so that commandline options can be passed to it
		Application() : m_game{} {}

		// Functions
		void run() {
			while (m_game.is_running()) {
				m_game.fixed_update();
				m_game.update();
				m_game.late_update();
				m_game.on_render();

				if (m_game.is_paused()) {
					m_game.on_game_pause();
				}
			}
		}

	private:
		// Data
		T m_game;
	};
}