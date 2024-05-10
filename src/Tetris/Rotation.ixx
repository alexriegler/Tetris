export module Rotation;

import std;

namespace ar
{
export enum class Rotation
{
    None,
    Rotate90CW,
    Rotate180CW,
    Rotate270CW
};

inline constexpr auto rotationOptions = 4;

export Rotation operator+(Rotation rotation, int value)
{
    const auto nextRotation = (std::to_underlying(rotation) + value) % rotationOptions;
    return static_cast<Rotation>(nextRotation);
}

export Rotation operator+(int value, Rotation rotation)
{
    return rotation + value;
}

export void operator++(Rotation& rotation)
{
    rotation = rotation + 1;
}

/// <summary>
/// Returns a new index for a tetromino piece given its coordinates and a rotation.
/// </summary>
/// <param name="px">The x position of the piece.</param>
/// <param name="py">The y position of the piece.</param>
/// <param name="rotation">The amount of rotation.</param>
/// <returns>Rotated index.</returns>
export int Rotate(int px, int py, Rotation rotation)
{
    switch (rotation)
    {
        using enum Rotation;
        case None:
            return py * 4 + px;
        case Rotate90CW:
            return 12 + py - (px * 4);
        case Rotate180CW:
            return 15 - (py * 4) - px;
        case Rotate270CW:
            return 3 - py + (px * 4);
        default:
            return py * 4 + px;
    }
}
}  // namespace ar