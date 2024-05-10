module;

#include <Windows.h>

export module Tetris;

export import Application;

import RandomBag;
import Tetromino;

import std;

namespace ar {
	export
	class Tetris : public Game {
	public:
		// Constructor
		Tetris();

		// Deconstructor
		~Tetris();

		// Functions
		// Event functions
		void fixed_update() override;
		void update() override;
		void late_update() override;
		void on_render() override;
		void on_game_pause() override;

		// Accessor functions
		bool is_running() const noexcept override;
		bool is_paused() const noexcept override;

	private:
		// Functions
		int Rotate(int, int, int);
		bool DoesPieceFit(const Tetromino&, int, int, int);

		// Data
		// Game state
		// TODO: Add console/window class
		bool m_is_running{ true };
		bool m_is_paused{ false };
		float m_fixed_delta_time{ 0.0f };
		float m_delta_time{ 0.0f };

		// Original data
		// Tetrominoes
		RandomBag randomBag{};

		// Playing field
		const int nFieldWidth{ 10 };
		const int nFieldHeight{ 20 };
		unsigned char pField[10 * 20];	// TODO: Add Field abstraction

		// Console screen
		int nScreenWidth{ 120 };		// Console screen size x (columns)
		int nScreenHeight{ 30 };		// Console screen size y (rows)
		wchar_t screen[120 * 30];		// Console screen to be used as screen buffer

		HANDLE hConsole{ nullptr };
		DWORD dwBytesWritten{ 0 };

		// Game state
		Tetromino cur_piece;
		int nCurrentRotation{ 0 };
		int nCurrentX{ nFieldWidth / 2 - 2 };
		int nCurrentY{ 0 };

		// Input
		bool bKey[4];
		bool bRotateHold{ true };

		// Game difficulty
		int nSpeed{ 20 };
		int nSpeedCounter{ 0 };
		bool bForceDown{ false };
		int nPieceCount{ 0 };

		// Score
		int nScore{ 0 };
		std::vector<int> vLines{};	// Number of lines cleared
	};
}