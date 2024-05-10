import Tetris;
import Console;

namespace ar
{
using TetrisApp = Application<Tetris, Console>;
}

int main()
{
    ar::TetrisApp app;
    app.run();
}

// TODO: Add ghost piece (where the piece will fall).
// TODO: Add hold piece.
// TODO: Add future piece preview.
// TODO: Add current speed level.
// TODO: Fix speedup (doesn't seem like it speeds up much if at all).
// TODO: Add opposite direction rotation (you can only rotate in one direction at the moment).
// TODO: Add color to pieces.
// TODO: (Optional) Change pieces from letters to block-like character.
// TODO: Add wall-kick (when piece is next to a wall, move piece then rotate).
