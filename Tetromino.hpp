#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include <array>
#include <utility> //resolved error with 'std::pair'
#include <cstdint>
#include "Board.hpp"

namespace tetris
{
    class Tetromino
    {
    public:
        // Constructor
        explicit Tetromino(Cell type);

        // Accessors
        Cell getType() const;
        int getRotation() const;
        std::pair<int, int> getPosition() const;
        std::array<std::pair<int, int>, 4> getBlocks() const;

        // Mutators
        void reset();
        void rotateCW();
        void rotateCCW();
        void move(int dx, int dy);

    private:
        Cell type_;    // piece identity (I, O, T, ...)
        int x_, y_;    // top-left anchor position on board
        int rotation_; // 0=spawn, 1=90°, 2=180°, 3=270°

        // Each tetrimino has up to 4 distinct orientations: default, 90°, 180°, 270°
        // shapes_ constitutes a static table encompassing all 7 x 4 = 28 rotation layouts.
        // Each rotation is thought of as a 4-block pattern centered around a pivot point with offsets.
        static const std::array<std::array<std::array<std::pair<int, int>, 4>, 4>, 7> shapes_;
    };
}
#endif