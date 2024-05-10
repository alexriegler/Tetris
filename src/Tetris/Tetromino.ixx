export module Tetromino;

import std;

namespace ar {
	enum class Shape { I, J, L, O, S, Z, T };

	export
	struct Tetromino {
		// Constructors
		Tetromino() : shape{}, symbol{}, id{}, piece{} {}

		Tetromino(Shape shape, wchar_t symbol, int id, const std::wstring& piece) :
			shape{ shape }, symbol{ symbol }, id{ id }, piece{ piece } {}

		// Functions
		const wchar_t operator[](int idx) const {
			return piece[idx];
		}

		// Data
		Shape shape;
		wchar_t symbol;
		int id;
		std::wstring piece;
	};

	// TODO: Shoud this be const/constexpr?
#pragma region Tetromino wstrings
	const std::wstring Ipiece{
		L"...."
		L"...."
		L"XXXX"
		L"...."
	};

	const std::wstring Jpiece{
		L"...."
		L"X..."
		L"XXX."
		L"...."
	};

	const std::wstring Lpiece{
		L"...."
		L"..X."
		L"XXX."
		L"...."
	};

	const std::wstring Opiece{
		L"...."
		L".XX."
		L".XX."
		L"...."
	};

	const std::wstring Spiece{
		L"...."
		L".XX."
		L"XX.."
		L"...."
	};

	const std::wstring Zpiece{
		L"...."
		L"XX.."
		L".XX."
		L"...."
	};

	const std::wstring Tpiece{
		L"...."
		L".X.."
		L"XXX."
		L"...."
	};
#pragma endregion

	// TODO: Shoud this be const/constexpr?
	const Tetromino I_tetro{ Shape::I, L'A', 1, Ipiece };
	const Tetromino J_tetro{ Shape::J, L'B', 2, Jpiece };
	const Tetromino L_tetro{ Shape::L, L'C', 3, Lpiece };
	const Tetromino O_tetro{ Shape::O, L'D', 4, Opiece };
	const Tetromino S_tetro{ Shape::S, L'E', 5, Spiece };
	const Tetromino Z_tetro{ Shape::Z, L'F', 6, Zpiece };
	const Tetromino T_tetro{ Shape::T, L'G', 7, Tpiece };

	// TODO: Replace 7 constant
	// TODO: Shoud this be const/constexpr?
	export
	std::array<Tetromino, 7> default_tetromino_set
		= { I_tetro, J_tetro, L_tetro, O_tetro, S_tetro, Z_tetro, T_tetro };
}