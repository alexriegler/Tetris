module;

#include <vector>

#include <Windows.h>

export module Tetris;

export import Application;

import RandomBag;
import Tetromino;

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
		bool m_is_running;
		bool m_is_paused;
		float m_fixed_delta_time; // float?
		float m_delta_time; // float?

		// Original data
		// Tetrominoes
		RandomBag randomBag;

		// Playing field
		int nFieldWidth;
		int nFieldHeight;
		unsigned char* pField;

		// Console screen
		int nScreenWidth;		// Console screen size x (columns)
		int nScreenHeight;		// Console screen size y (rows)
		wchar_t* screen;		// Console screen to be used as screen buffer
		HANDLE hConsole;
		DWORD dwBytesWritten;

		// Game state
		Tetromino cur_piece;
		int nCurrentRotation;
		int nCurrentX;
		int nCurrentY;

		// Input
		bool bKey[4];
		bool bRotateHold;

		// Game difficulty
		int nSpeed;
		int nSpeedCounter;
		bool bForceDown;
		int nPieceCount;

		// Score
		int nScore;
		std::vector<int> vLines;	// Number of lines cleared
	};
}