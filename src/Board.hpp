#ifndef BOARD_HPP
#define BOARD_HPP

#include "Piece.hpp"

class Board
{
private:
    Piece *** board;
    int turn;
public:
    Board();
    void ShowBoard();
    Piece* getPieceAt(Position pos);
    bool move(Position initpos, Position newpos);
    int checkWin();
};

#endif