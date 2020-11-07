#pragma once
#include <string>
using namespace std;

namespace Tetris
{
	enum class Shape { I, J, L, O, S, Z, T };

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

		static const wstring Ipiece;
		static const wstring Jpiece;
		static const wstring Lpiece;
		static const wstring Opiece;
		static const wstring Spiece;
		static const wstring Zpiece;
		static const wstring Tpiece;
	};
}