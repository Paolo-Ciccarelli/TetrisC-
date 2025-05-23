#include "Board.hpp"
#include <algorithm>
#include <cassert>

namespace tetris
{
    // Constructor: initializes an empty board by calling clear()
    Board::Board()
    {
        clear();
    }

    // Clears the entire board, setting all cells to Cell::Empty.
    // Conventionally called when initially starting or restarting a game session.
    void Board::clear()
    {
        for (auto &row : grid_)
            row.fill(Cell::Empty);
    }

    // Returns true if the coordinates (x,y) lie within the board bounds.
    // Prevents accessing invalid memory beyond the grid.
    bool Board::isInside(int x, int y) const
    {
        return 0 <= x && x < static_cast<int>(width) &&
               0 <= y && y < static_cast<int>(height);
    }

    // Returns the cell value at position (x,y).
    // Asserts that the coordinates are valid, that is within grid bounds.
    Cell Board::at(int x, int y) const
    {
        assert(isInside(x,y) && "ERROR: Board::at, coordinates out of range");
        return grid_[y][x];
    }

    // Sets the cell at position (x,y) to a new value (say Cell::I).
    // Asserts that the coordinates are valid, that is within grid bounds.
    // Used to manually place or remove a block.
    void Board::set(int x, int y, Cell c) 
    {
        assert(isInside(x,y) && "ERROR: Board::at, coordinates out of range");
        grid_[y][x] = c;
    }

    // Assesses whether placing a tetromino at the given 4 positions causes a collision.
    // Returns true if any of the blocks are out of pounds or overlap existing blocks.
    // Used before moving or rotating a piece to ensure legality.
    bool Board::testCollision(const std::array<std::pair<int, int>, 4> &blocks) const
    {
        
        return false;
    }


}