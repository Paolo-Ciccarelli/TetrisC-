#include "Tetromino.hpp"
#include <cassert>

namespace tetris {

// ====== Static shape data for all 7 tetrominoes and 4 rotations each ======
// Each block is stored as an offset from the piece's origin (x_, y_)
const std::array<std::array<std::array<std::pair<int,int>, 4>, 4>, 7> Tetromino::shapes_ = {{
    // ======== I Piece ========
    {{
        {{ {0,1}, {1,1}, {2,1}, {3,1} }}, // Rotation 0° (horizontal)
        {{ {2,0}, {2,1}, {2,2}, {2,3} }}, // Rotation 90°
        {{ {0,2}, {1,2}, {2,2}, {3,2} }}, // Rotation 180°
        {{ {1,0}, {1,1}, {1,2}, {1,3} }}  // Rotation 270°
    }},
    // ======== O Piece ========
    {{
        {{ {1,0}, {2,0}, {1,1}, {2,1} }}, // Rotation 0° (square symmetry)
        {{ {1,0}, {2,0}, {1,1}, {2,1} }}, // Rotation 90°
        {{ {1,0}, {2,0}, {1,1}, {2,1} }}, // Rotation 180°
        {{ {1,0}, {2,0}, {1,1}, {2,1} }}  // Rotation 270°
    }},
    // ======== T Piece ========
    {{
        {{ {1,0}, {0,1}, {1,1}, {2,1} }}, // Rotation 0° (spawn)
        {{ {1,0}, {1,1}, {2,1}, {1,2} }}, // Rotation 90°
        {{ {0,1}, {1,1}, {2,1}, {1,2} }}, // Rotation 180°
        {{ {1,0}, {0,1}, {1,1}, {1,2} }}  // Rotation 270°
    }},
    // ======== S Piece ========
    {{
        {{ {1,0}, {2,0}, {0,1}, {1,1} }}, // Rotation 0° (spawn)
        {{ {1,0}, {1,1}, {2,1}, {2,2} }}, // Rotation 90°
        {{ {1,1}, {2,1}, {0,2}, {1,2} }}, // Rotation 180°
        {{ {0,0}, {0,1}, {1,1}, {1,2} }}  // Rotation 270°
    }},
    // ======== Z Piece ========
    {{
        {{ {0,0}, {1,0}, {1,1}, {2,1} }}, // Rotation 0° (spawn)
        {{ {2,0}, {1,1}, {2,1}, {1,2} }}, // Rotation 90°
        {{ {0,1}, {1,1}, {1,2}, {2,2} }}, // Rotation 180°
        {{ {1,0}, {0,1}, {1,1}, {0,2} }}  // Rotation 270°
    }},
    // ======== J Piece ========
    {{
        {{ {0,0}, {0,1}, {1,1}, {2,1} }}, // Rotation 0° (spawn)
        {{ {1,0}, {2,0}, {1,1}, {1,2} }}, // Rotation 90°
        {{ {0,1}, {1,1}, {2,1}, {2,2} }}, // Rotation 180°
        {{ {1,0}, {1,1}, {0,2}, {1,2} }}  // Rotation 270°
    }},
    // ======== L Piece ========
    {{
        {{ {2,0}, {0,1}, {1,1}, {2,1} }}, // Rotation 0° (spawn)
        {{ {1,0}, {1,1}, {1,2}, {2,2} }}, // Rotation 90°
        {{ {0,1}, {1,1}, {2,1}, {0,2} }}, // Rotation 180°
        {{ {0,0}, {1,0}, {1,1}, {1,2} }}  // Rotation 270°
    }}
}};

// Constructs a Tetromino at default position (3,0) spawn rotation (ie:0) with designated type 
Tetromino::Tetromino(Cell type) : type_(type), x_(3), y_(0), rotation_(0)
{
    assert(type != Cell::Empty);  // Empty is not a valid piece
}

// Resets Tetrimino piece to spawn orientation (ie:0) and default position (3,0)
void Tetromino::reset() {
    x_ = 3;
    y_ = 0;
    rotation_ = 0;
}

// Displaces tetromino piece by relatve offset (dx, dy)
void Tetromino::move(int dx, int dy) {
    x_ += dx;
    y_ += dy;
}

// Rotates the tetromino clockwise by incrementing the rotation index (0 to 3)
void Tetromino::rotateCW() {
    rotation_ = (rotation_ + 1) % 4;
}

// Rotates the tetromino counter-clockwise by decrementing the rotation index (0 to 3)
void Tetromino::rotateCCW() {
    rotation_ = (rotation_ + 3) % 4;  // Equivalent to -1 mod 4
}

// Computes the absolute board positions of the tetromino's four blocks.
// Uses the current type, rotation, and origin (x_, y_) to apply offsets from shapes_.
std::array<std::pair<int, int>, 4> Tetromino::getBlocks() const {
    std::array<std::pair<int, int>, 4> result;
    int index = static_cast<int>(type_) - 1;
    assert(index >= 0 && index < 7);  // Bounds check

    for (int i = 0; i < 4; ++i) {
        int dx = shapes_[index][rotation_][i].first;
        int dy = shapes_[index][rotation_][i].second;
        result[i] = { x_ + dx, y_ + dy };
    }
    return result;
}

// Returns the tetromino's type (eg: I, O, T, etc)
Cell Tetromino::getType() const {
    return type_;
}

// Returns the current rotation index (0, 1, 2, or 3)
int Tetromino::getRotation() const {
    return rotation_;
}

// Returns the tetromino's origin position as an (x,y) coordinate pair
std::pair<int, int> Tetromino::getPosition() const {
    return { x_, y_ };
}

}