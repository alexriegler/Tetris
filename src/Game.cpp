#include "Game.h"

namespace ar {
	// Public functions
	// Constructor
	Game::Game() : m_is_running{ true }, m_is_paused{ false }, m_fixed_delta_time{}, m_delta_time{}, randomBag{} {
		// Initialize playing field
		// Playing field
		nFieldWidth = 10;
		nFieldHeight = 20;
		
		// Create playing field buffer
		pField = new unsigned char[nFieldWidth * nFieldHeight];

		// Create playing field boundary
		for (int x = 0; x < nFieldWidth; x++)
		{
			for (int y = 0; y < nFieldHeight; y++)
			{
				// TODO: Fix space representation
				// 9 represents a border
				// 0 represents a empty space
				pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;
			}
		}

		nScreenWidth = 120;
		nScreenHeight = 30;

		// Setup console to be used as screen buffer
		screen = new wchar_t[nScreenWidth * nScreenHeight];
		for (int i = 0; i < nScreenWidth * nScreenHeight; i++)
		{
			screen[i] = L' ';
		}
		hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleActiveScreenBuffer(hConsole);
		dwBytesWritten = 0;

		// Game logic
		// TODO: Change instances of "bGameOver" to "m_is_running"
		// bool bGameOver = false;

		// Game state
		cur_piece = randomBag.next();
		nCurrentRotation = 0;
		nCurrentX = nFieldWidth / 2 - 2;
		nCurrentY = 0;

		// Input
		// TODO: Add up arrow for hard drop
		bRotateHold = true;

		// Game difficulty
		nSpeed = 20;
		nSpeedCounter = 0;
		bForceDown = false;
		nPieceCount = 0;

		// Score
		nScore = 0;
	}

	// Deconstructor
	Game::~Game() {
		// Game over message
		// Need to close console handle before writing to std::cout
		CloseHandle(hConsole);
		std::cout << "Game Over! Score: " << nScore << '\n';
		// TODO: Windows specific; change to cross platform "Press any key to continue"
		system("pause");

		delete[] screen;
		delete[] pField;
	}

	// Functions
	void Game::fixed_update() {
		// For ms suffix
		using namespace std::chrono_literals;

		// GAME TIMING ===========================================
		// TODO: Fix hack for fixed update
		std::this_thread::sleep_for(50ms);
		nSpeedCounter++;
		bForceDown = (nSpeedCounter == nSpeed);

		// INPUT =================================================
		for (int k = 0; k < 4; k++)
		{
			// \x27		= Right arrow	VK_RIGHT
			// \x25		= Left arrow	VK_LEFT
			// \x28		= Down arrow	VK_DOWN
			// Z		= Z (rotate)	0x5A
			bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;
		}

		// GAME LOGIC ============================================
		// Player movement
		// Right key pressed
		if (bKey[0] && DoesPieceFit(cur_piece, nCurrentRotation, nCurrentX + 1, nCurrentY))
		{
			nCurrentX++;
		}
		// Left key pressed
		if (bKey[1] && DoesPieceFit(cur_piece, nCurrentRotation, nCurrentX - 1, nCurrentY))
		{
			nCurrentX--;
		}
		// Down key pressed
		if (bKey[2] && DoesPieceFit(cur_piece, nCurrentRotation, nCurrentX, nCurrentY + 1))
		{
			nCurrentY++;
		}
		// Z key pressed (rotate)
		// Latches the rotation so that it does spin repetitively
		if (bKey[3])
		{
			if (!bRotateHold && DoesPieceFit(cur_piece, nCurrentRotation + 1, nCurrentX, nCurrentY))
			{
				nCurrentRotation++;
			}
			bRotateHold = true;
		}
		else
		{
			bRotateHold = false;
		}

		// Game movement
		// If it's time to force the tetromino down
		if (bForceDown)
		{
			// Move piece down if it fits
			if (DoesPieceFit(cur_piece, nCurrentRotation, nCurrentX, nCurrentY + 1))
			{
				nCurrentY++;
			}
			else
			{
				// Lock the current piece in the field
				for (int px = 0; px < 4; px++)
				{
					for (int py = 0; py < 4; py++)
					{
						if (cur_piece[Rotate(px, py, nCurrentRotation)] == L'X')
						{
							// Place peice in the field
							pField[(nCurrentY + py) * nFieldWidth + (nCurrentX + px)] = cur_piece.id;
						}
					}
				}

				// Increment piece count and decrease ticks required to move piece (i.e., move faster)
				nPieceCount++;
				if (nPieceCount % 10 == 0)
				{
					if (nSpeed >= 10)
					{
						nSpeed--;
					}
				}

				// Check for horizontal lines
				// Check 4 rows of tetromino for lines
				for (int py = 0; py < 4; py++)
				{
					// Boundary check
					if (nCurrentY + py < nFieldHeight - 1)
					{
						bool bLine = true;
						// Exlcude first and last column in check (since they are empty)
						for (int px = 1; px < nFieldWidth - 1; px++)
						{
							bLine &= (pField[(nCurrentY + py) * nFieldWidth + px]) != 0;
						}

						if (bLine)
						{
							// Remove line (set to '=')
							for (int px = 1; px < nFieldWidth - 1; px++)
							{
								// TODO: Change constant 8 to enum or something
								pField[(nCurrentY + py) * nFieldWidth + px] = 8;
							}

							vLines.push_back(nCurrentY + py);
						}
					}
				}

				// Score
				nScore += 25;
				if (!vLines.empty())
				{
					// Lines are worth: lines^2 * 100
					nScore += (1 << vLines.size()) * 100;
				}

				// Choose the next piece and reset the piece position and rotation
				cur_piece = randomBag.next();
				nCurrentX = nFieldWidth / 2 - 2;
				nCurrentY = 0;
				nCurrentRotation = 0;

				// Game continues if the pieces fits
				m_is_running = DoesPieceFit(cur_piece, nCurrentRotation, nCurrentX, nCurrentY);
			}

			nSpeedCounter = 0;
		}		
	}

	/*void Game::update();
	void Game::late_update();*/

	void Game::on_render() {
		// For ms suffix
		using namespace std::chrono_literals;

		// RENDER OUTPUT =========================================
		// Draw playing field
		for (int x = 0; x < nFieldWidth; x++)
		{
			for (int y = 0; y < nFieldHeight; y++)
			{
				// Symbol key:
				// Index	Char	Represents
				// ______________________________
				//   0	|	( )	  |	empty space 
				//  1-7	|  (A-G)  |	tetrominoes
				//   8	|	(=)	  |	   line 
				//   9	|	(#)	  |	  border
				screen[(y + 2) * nScreenWidth + (x + 2)] = L" ABCDEFG=#"[pField[y * nFieldWidth + x]];
			}
		}

		// Draw current piece
		for (int px = 0; px < 4; px++)
		{
			for (int py = 0; py < 4; py++)
			{
				if (cur_piece[Rotate(px, py, nCurrentRotation)] == L'X')
				{
					screen[(nCurrentY + py + 2) * nScreenWidth + (nCurrentX + px + 2)] = cur_piece.symbol;
				}
			}
		}

		// Draw score
		swprintf_s(&screen[2 * nScreenWidth + nFieldWidth + 6], 16, L"SCORE: %8d", nScore);

		// Draw line animation
		if (!vLines.empty())
		{
			// Display frame (hacky draw lines)
			WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
			std::this_thread::sleep_for(400ms); // Delay a bit

			// Move lines down
			for (auto& v : vLines)
			{
				for (int px = 1; px < nFieldWidth - 1; px++)
				{
					for (int py = v; py > 0; py--)
					{
						pField[py * nFieldWidth + px] = pField[(py - 1) * nFieldWidth + px];
					}
					pField[px] = 0;
				}
			}

			vLines.clear();
		}

		// Display frame
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0, 0 }, &dwBytesWritten);
	}

	//void Game::on_game_pause();

	bool Game::is_running() const noexcept {
		return m_is_running;
	}
	bool Game::is_paused() const noexcept {
		return m_is_paused;
	}

	// Private functions
	/// <summary>
	/// Returns a new index for a tetromino piece given its coordinates and a rotation.
	/// </summary>
	/// <param name="px">The x position of the piece.</param>
	/// <param name="py">The y position of the piece.</param>
	/// <param name="r">The degree of rotation: 0 = none, 1 = 90, 2 = 180, 3 = 270.</param>
	/// <returns>Rotated index.</returns>
	int Game::Rotate(int px, int py, int r)
	{
		// TODO: Use enum for rotation
		switch (r % 4)
		{
		case 0:  return py * 4 + px;		//   0 degrees
		case 1:  return 12 + py - (px * 4);	//  90 degrees
		case 2:  return 15 - (py * 4) - px;	// 180 degrees
		case 3:  return 3 - py + (px * 4);	// 270 degrees
		default: return py * 4 + px;		//   0 degrees
		}
	}

	/// <summary>
	/// Checks whether a tetromino piece fits in a given location.
	/// </summary>
	/// <param name="tetromino">The tetromino piece.</param>
	/// <param name="nRotation">The degree of rotation: 0 = none, 1 = 90, 2 = 180, 3 = 270.</param>
	/// <param name="nPosX">The x position of the top left corner of the tetromino.</param>
	/// <param name="nPosY">The y position of the top left corner of the tetromino.</param>
	/// <returns>True, if the piece fits; false, otherwise.</returns>
	bool Game::DoesPieceFit(const Tetromino& tetromino, int nRotation, int nPosX, int nPosY)
	{
		for (int px = 0; px < 4; px++)
		{
			for (int py = 0; py < 4; py++)
			{
				// Get index into piece
				int pi = Rotate(px, py, nRotation);

				// Get index into field
				int fi = (nPosY + py) * nFieldWidth + (nPosX + px);

				// Check array bounds
				if (nPosX + px >= 0 && nPosX + px < nFieldWidth)
				{
					if (nPosY + py >= 0 && nPosY + py < nFieldHeight)
					{
						// Detect collision (check if piece fits in location
						if (tetromino[pi] == L'X' && pField[fi] != 0)
						{
							return false;
						}
					}
				}
			}
		}
		return true;
	}
}