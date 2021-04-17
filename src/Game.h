#pragma once

#include "Tetromino.h"
#include "RandomBag.h"

#include <iostream>
#include <thread>
#include <vector>

#include <Windows.h>

namespace ar {
	class Game {
	public:
		// Constructor
		Game();
		
		// Deconstructor
		~Game();

		// Functions
		// Event functions
		// fixed time interval update
		// check collision?
		void fixed_update();
		
		/*void update();
		void late_update();
		void on_render();
		void on_game_pause();*/

		void on_game_over();

		// Accessor functions
		bool is_running() const noexcept;
		bool is_paused() const noexcept;

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