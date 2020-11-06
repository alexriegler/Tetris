#include <iostream>

#include <Windows.h>
#include <array>

// Global variables
// Tetrominoes
// TODO: Use std::array for tetromino
std::wstring tetromino[7];

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

	// Game loop
	bool bGameOver = false;

	while (!bGameOver)
	{
		// GAME TIMING ===========================================

		// INPUT =================================================

		// GAME LOGIC ============================================

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

		// Display frame
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0, 0 }, &dwBytesWritten);
	}

	// Clean up
	delete[] screen;
	delete[] pField;

	return 0;
}