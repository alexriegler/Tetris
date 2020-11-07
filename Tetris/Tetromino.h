#pragma once
#include <string>
using namespace std;

namespace Tetris
{
	enum class Shape { I, J, L, O, S, Z, T };

	const wstring Ipiece;
	const wstring Jpiece;
	const wstring Lpiece;
	const wstring Opiece;
	const wstring Spiece;
	const wstring Zpiece;
	const wstring Tpiece;

	class Tetromino
	{
	public:
		Tetromino() = delete;
		Tetromino(Shape shape, wchar_t symbol, const wstring& piece) :
			m_shape{ shape }, m_symbol{ symbol }, m_piece{ piece } {}
	private:
		const Shape m_shape;
		const wchar_t m_symbol;
		const wstring m_piece;
	};
}