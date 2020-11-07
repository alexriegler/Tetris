#include <iostream>
#include <thread>
#include <vector>
using namespace std;

#include <Windows.h>

// Global variables
// Tetrominoes
// TODO: Use std::array for tetromino
wstring tetromino[7];

// Playing field
int nFieldWidth = 12;
int nFieldHeight = 18;
unsigned char* pField = nullptr;

// Console screen
int nScreenWidth = 120;		// Console screen size x (columns)
int nScreenHeight = 30;		// Console screen size y (rows)

/// <summary>
/// Returns a new index for a tetromino piece given its coordinates and a rotation.
/// </summary>
/// <param name="px">The x position of the piece</param>
/// <param name="py">The y position of the piece</param>
/// <param name="r">The degree of rotation: 0 = none, 1 = 90, 2 = 180, 3 = 270</param>
/// <returns>Rotated index</returns>
int Rotate(int px, int py, int r)
{
	// TODO: Use enum for rotation
	switch (r % 4)
	{
	case 0: return py * 4 + px;			//   0 degrees
	case 1: return 12 + py - (px * 4);	//  90 degrees
	case 2: return 15 - (py * 4) - px;	// 180 degrees
	case 3: return 3 - py + (px * 4);	// 270 degrees
	}
}

/// <summary>
/// Checks whether a tetromino piece fits in a given location.
/// </summary>
/// <param name="nTetromino">The index of the tetromino</param>
/// <param name="nRotation">The degree of rotation: 0 = none, 1 = 90, 2 = 180, 3 = 270</param>
/// <param name="nPosX">The x position of the top left corner of the tetromino</param>
/// <param name="nPosY">The y position of the top left corner of the tetromino</param>
/// <returns>True, if the piece fits; false, otherwise</returns>
bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY)
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
					// Collision detection
					if (tetromino[nTetromino][pi] == L'X' && pField[fi] != 0)
					{
						return false; // fail on first hit
					}
				}
			}
		}
	}
	
	return true;
}

int main()
{
	// Create assets
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");

	tetromino[1].append(L"..X.");
	tetromino[1].append(L".XX.");
	tetromino[1].append(L".X..");
	tetromino[1].append(L"....");

	tetromino[2].append(L".X..");
	tetromino[2].append(L".XX.");
	tetromino[2].append(L"..X.");
	tetromino[2].append(L"....");

	tetromino[3].append(L"....");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L"....");

	tetromino[4].append(L"..X.");
	tetromino[4].append(L".XX.");
	tetromino[4].append(L"..X.");
	tetromino[4].append(L"....");

	tetromino[5].append(L"....");
	tetromino[5].append(L".XX.");
	tetromino[5].append(L"..X.");
	tetromino[5].append(L"..X.");

	tetromino[6].append(L"....");
	tetromino[6].append(L".XX.");
	tetromino[6].append(L".X..");
	tetromino[6].append(L".X..");

	// Initialize playing field
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

	// Setup console to be used as screen buffer
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	for (int i = 0; i < nScreenWidth * nScreenHeight; i++)
	{
		screen[i] = L' ';
	}
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	// Game logic
	bool bGameOver = false;

	// Game state
	int nCurrentPiece = 0;
	int nCurrentRotation = 0;
	int nCurrentX = nFieldWidth / 2;
	int nCurrentY = 0;

	// Input
	// TODO: Add up arrow for hard drop
	bool bKey[4];
	bool bRotateHold = true;

	// Game difficulty
	int nSpeed = 20;
	int nSpeedCounter = 0;
	bool bForceDown = false;
	int nPieceCount = 0;

	// Score
	int nScore = 0;

	vector<int> vLines;

	// Game loop
	while (!bGameOver)
	{
		// GAME TIMING ===========================================
		this_thread::sleep_for(50ms);
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
		if (bKey[0] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY))
		{
			nCurrentX++;
		}
		// Left key pressed
		if (bKey[1] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY))
		{
			nCurrentX--;
		}
		// Down key pressed
		if (bKey[2] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
		{
			nCurrentY++;
		}
		// Z key pressed (rotate)
		// Latches the rotation so that it does spin repetitively
		if (bKey[3])
		{
			if (!bRotateHold && DoesPieceFit(nCurrentPiece, nCurrentRotation + 1, nCurrentX, nCurrentY))
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
			if (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
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
						if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] == L'X')
						{
							// Place peice in the field
							pField[(nCurrentY + py) * nFieldWidth + (nCurrentX + px)] = nCurrentPiece + 1;
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

				// Choose the next piece
				nCurrentX = nFieldWidth / 2;
				nCurrentY = 0;
				nCurrentRotation = 0;
				// TODO: Implement better random method
				nCurrentPiece = rand() % 7;

				// If piece does not fit, game over
				bGameOver = !DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY);
			}

			nSpeedCounter = 0;
		}

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
				if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] == L'X')
				{
					// Add 65 to current piece index to get ASCII 'A' - 'G'
					screen[(nCurrentY + py + 2) * nScreenWidth + (nCurrentX + px + 2)] = nCurrentPiece + 65;
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
			this_thread::sleep_for(400ms); // Delay a bit

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

	// Clean up
	CloseHandle(hConsole);
	delete[] screen;
	delete[] pField;

	// Game over
	cout << "Game Over! Score: " << nScore << endl;
	system("pause");

	return 0;
}