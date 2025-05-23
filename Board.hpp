// Belongs to the Model Layer
// A 10 x 20 grid

#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <cstdint>  //resolved error with 'std::uint8_t'
#include <cstddef>  //defines std::size_t
#include <optional> 

namespace tetris
{

    // Defn: scoped enumeration with underlying type 8-bit integer compact storage
    enum class Cell : std::uint8_t
    {
        Empty = 0,
        I,
        O,
        T,
        S,
        Z,
        J,
        L
    };

    class Board
    {
    public:
        // Grid Dimensions
        static constexpr std::size_t width = 10;
        static constexpr std::size_t height = 28;

        // Accessors
        Board();                           // default constructor
        void clear();                      // clears the grid by setting all cells to 'Empty'
        bool isInside(int x, int y) const; // assesses whether the coordinates are within grid bounds
        Cell at(int x, int y) const;       // returns the Cell type at position (x,y)

        // Mutators
        void set(int x, int y, Cell c);                                              // updates the Cell type at postion (x,y) to type 'c'
        bool testCollision(const std::array<std::pair<int, int>, 4> &blocks) const;  // assesses whether the tetrimino collides with bounds, other tetriminos
        void lockPiece(const std::array<std::pair<int, int>, 4> &blocks, Cell type); // pins the tetrimino onto the board when there is no more space to move
        std::size_t sweepLines(); // scans the grid, deletes full rows, compacts accordingly, returns count

    private:
        using Row = std::array<Cell, width>; // alias: one horizontal row
        std::array<Row, height> grid_;       // the whole 20×10 board
    };
}

#endif