#include "Game.hpp"
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>

namespace tetris
{

    // Intiailizes a new Tetris game, setting up the board and spawing the first tetromino.
    // Seeds the random number generator for piece selection during the game loop.
    Game::Game()
        : board_(), current_(Cell::I), gameOver_(false)
    {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        spawnNewPiece();
    }

    // Returns a const reference to the game board for external access.
    // Allows inspection of the board sate without modification.
    const Board &Game::getBoard() const
    {
        return board_;
    }

    // Returns the absolute (x,y) coordinates of the four blocks of the current falling tetromino.
    // Uses Tetromino::getBlocks() to compute positions based on the piece's origin and rotation.
    std::array<std::pair<int, int>, 4> Game::getCurrentBlocks() const
    {
        return current_.getBlocks();
    }

    // Returns the type (say I, O, T) of the current falling tetromino.
    Cell Game::getCurrentType() const
    {
        return current_.getType();
    }

    // Assesses whether the present game session has concluded (ie: due to a collision at spawn).
    // Returns true if the game is over, false otherwise.
    bool Game::isGameOver() const
    {
        return gameOver_;
    }

    // Spawns a new random tetromino at the board's default spawn point (x=3, y=0).
    // Sets the gameOver_ boolean property to true if the new piece collides immediately, indicating a full board.
    void Game::spawnNewPiece()
    {
        int r = 1 + (std::rand() % 7); // RNG between 1 and 7
        Cell type = static_cast<Cell>(r);
        current_ = Tetromino(type);
        if (board_.testCollision(current_.getBlocks()))
            gameOver_ = true;
    }

    // Locks the current tetromino onto the board, clears completed lines, and spawns a new piece.
    // Updates the board with the piece's blocks and type before clearing lines.
    void Game::lockCurrentPiece()
    {
        board_.lockPiece(current_.getBlocks(), current_.getType());
        board_.sweepLines();
        spawnNewPiece();
    }

    // Advances the game by one tick, simulating gravity by moving the tetromino down one unit.
    // If a collision occurs, undoes the move and locks the piece in place.
    void Game::update()
    {
        if (gameOver_)
            return;
        current_.move(0, 1);
        if (board_.testCollision(current_.getBlocks()))
        {
            current_.move(0, -1); // undo move if collision detected
            lockCurrentPiece();   // locks falling tetromino piece and spawns new one
        }
    }

    // Moves the current tetromino one unit to the left.
    // Undoes the move and logs a non-fatal error if a collision occurs.
    void Game::moveLeft()
    {
        current_.move(-1, 0);
        // Suppose a collision is detected when attempting this action.
        if (board_.testCollision(current_.getBlocks()))
        {
            current_.move(1, 0); // undo move if collision detected
            std::cout << "NON-FATAL ERROR: collision detected whilst attempting to move left." << std::endl;
        }
    }

    // Moves the current tetromino one unit to the right.
    // Undoes the move and logs a non-fatal error if a collision occurs.
    void Game::moveRight()
    {
        current_.move(1, 0);
        if (board_.testCollision(current_.getBlocks()))
        {
            current_.move(-1, 0); // undo move if collision detected
            std::cout << "NON-FATAL ERROR: collision detected whilst attempting to move right." << std::endl;
        }
    }

    // Moves the current tetromino one unit downward (soft drop).
    // Undoes the move and logs a non-fatal error if a collision occurs.
    void Game::softDrop()
    {
        current_.move(0, 1);
        if (board_.testCollision(current_.getBlocks()))
        {
            current_.move(0, -1); // undo move if collision detected
            std::cout << "NON-FATAL ERROR: collision detected whilst attempting to move down." << std::endl;
        }
    }

    // Moves the current tetromino downward until it collides, then locks it in place.
    // Logs a non-fatal error for each collision attempt and locks the piece when stopped.
    void Game::hardDrop()
    {
        while (true)
        {
            current_.move(0, 1);
            if (board_.testCollision(current_.getBlocks()))
            {
                current_.move(0, -1); // undo move if collision detected
                std::cout << "NON-FATAL ERROR: collision detected whilst attempting to move down." << std::endl;
                break;
            }
        }
        lockCurrentPiece();
    }

    // Rotates the current tetromino clockwise.
    // Undoes the rotation and logs a non-fatal error if a collision occurs.
    void Game::rotateCW()
    {
        current_.rotateCW();
        if (board_.testCollision(current_.getBlocks()))
        {
            current_.rotateCCW(); // undo rotation if collision detected
            std::cout << "NON-FATAL ERROR: collision detected whilst attempting to rotate clockwise." << std::endl;
        }
    }

    // Rotates the current tetromino counter-clockwise.
    // Undoes the rotation and logs a non-fatal error if a collision occurs.
    void Game::rotateCCW()
    {
        current_.rotateCCW();
        if (board_.testCollision(current_.getBlocks()))
        {
            current_.rotateCW(); // undo rotation if collision detected
            std::cout << "NON-FATAL ERROR: collision detected whilst attempting to rotate counter-clockwise." << std::endl;
        }
    }
}