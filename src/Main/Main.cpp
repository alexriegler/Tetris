import Tetris;

using TetrisApp = ar::Application<ar::Tetris>;

int main() {
	TetrisApp app;
	app.run();
}

// TODO: Split main into modular parts: game, tetris, score, field, etc.
// TODO: Add ghost piece (where the piece will fall).
// TODO: Add hold piece.
// TODO: Add future piece preview.
// TODO: Add current speed level.
// TODO: Fix speedup (doesn't seem like it speeds up much if at all).
// TODO: Add opposite direction rotation (you can only rotate in one direction at the moment).
// TODO: Add color to pieces.
// TODO: (Optional) Change pieces from letters to block-like character.
// TODO: Add wall-kick (when piece is next to a wall, move piece then rotate).