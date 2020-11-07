#pragma once
#include <string>
using namespace std;

namespace Tetris
{
	enum class Shape { I, J, L, O, S, Z, T };

#pragma region Tetromino wstrings
	const wstring Ipiece{
		L"...."
		L"...."
		L"XXXX"
		L"...."
	};

	const wstring Jpiece{
		L"...."
		L"X..."
		L"XXX."
		L"...."
	};

	const wstring Lpiece{
		L"...."
		L"..X."
		L"XXX."
		L"...."
	};

	const wstring Opiece{
		L"...."
		L".XX."
		L".XX."
		L"...."
	};

	const wstring Spiece{
		L"...."
		L".XX."
		L"XX.."
		L"...."
	};

	const wstring Zpiece{
		L"...."
		L"XX.."
		L".XX."
		L"...."
	};

	const wstring Tpiece{
		L"...."
		L".X.."
		L"XXX."
		L"...."
	};
#pragma endregion

	class Tetromino
	{
	public:
		Tetromino() = delete;
		Tetromino(Shape shape, wchar_t symbol, const wstring& piece) :
			m_shape{ shape }, m_symbol{ symbol }, m_piece{ piece } {}

		// Copy constructor
		Tetromino(const Tetromino& other) : 
			m_shape{other.m_shape}, m_symbol{other.m_symbol}, m_piece{other.m_piece} {}
	private:
		Shape m_shape;
		wchar_t m_symbol;
		wstring m_piece;
	};
}