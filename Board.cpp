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
        assert(isInside(x, y) && "ERROR: Board::at, coordinates out of range");
        return grid_[y][x];
    }

    // Sets the cell at position (x,y) to a new value (say Cell::I).
    // Asserts that the coordinates are valid, that is within grid bounds.
    // Used to manually place or remove a block.
    void Board::set(int x, int y, Cell c)
    {
        assert(isInside(x, y) && "ERROR: Board::at, coordinates out of range");
        grid_[y][x] = c;
    }

    // Assesses whether placing a tetromino at the given 4 positions causes a collision.
    // Returns true if any of the blocks are out of bounds or overlap existing blocks.
    // Used before moving or rotating a piece to ensure legality.
    bool Board::testCollision(const std::array<std::pair<int, int>, 4> &blocks) const
    {
        for (const auto &[x, y] : blocks)
        {
            if (!isInside(x, y))
                return true;
            if (at(x, y) != Cell::Empty)
                return true;
        }
        return false;
    }

    // Effectively pins a tetrimino permanently onto the board once it can no longer be moved.
    // Assumes testCollision() has been executed previously.
    void Board::lockPiece(const std::array<std::pair<int, int>, 4> &blocks, Cell type)
    {
        for (const auto &[x, y] : blocks)
        {
            assert(isInside(x, y) && "ERROR: Board::lockPiece, coordnates out of bounds");
            grid_[y][x] = type;
        }
    }

    // Iterates throuh each row from bottom to top, checking for fully filled rows.
    // When a filled row is identified, it is removed, and all rows above it are shifted downwards accordingly.
    // Returns the number of lines cleared, important for scoring.
    std::size_t Board::sweepLines()
    {
        std::size_t linesCleared = 0;
        // Note: algorithm "all_of" assesses if a given predicate returns true for all elements in the specified range.
        for (int row = static_cast<int>(height) - 1; row >= 0; --row)
        {
            bool full = std::all_of(grid_[row].begin(), grid_[row].end(), [](Cell c) { return c != Cell::Empty; });
            // Proceed on condition that the row is filled with tetrimino blocks.
            if (full)
            {
                // Shifts all rows above the present "row" downward by one.
                for (int r = row; r > 0; --r) grid_[r] = grid_[r - 1];
                // Topmost row should be cleared per standard Tetris mechanics.
                grid_[0].fill(Cell::Empty);
                ++linesCleared;
                ++row;
            }
        }
        return linesCleared;
    }

}