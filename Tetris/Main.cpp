#include <iostream>

std::wstring tetromino[7];

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

int main()
{
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

	return 0;
}