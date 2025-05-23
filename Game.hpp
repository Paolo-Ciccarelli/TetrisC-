#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include "Tetromino.hpp"
#include <optional>

namespace tetris
{
    class Game
    {
    public:
        Game();
        void update();
        void rotateCW();
        void rotateCCW();
        void moveLeft();
        void moveRight();
        void softDrop();
        void hardDrop();
        bool isGameOver() const;
        const Board &getBoard() const;
        std::array<std::pair<int, int>, 4> getCurrentBlocks() const;
        Cell getCurrentType() const;

    private:
        Board board_;
        Tetromino current_;
        bool gameOver_;
        void spawnNewPiece();
        void lockCurrentPiece();
    };
}

#endif