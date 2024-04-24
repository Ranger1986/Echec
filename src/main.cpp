#include "Piece.hpp"
#include "Board.hpp"
#include <iostream>

typedef Position p;

int main(int argc, char* argv[])
{
    Board board = Board();
    board.ShowBoard();

    board.move(p(0,1), p(2,2));
    board.ShowBoard();

    board.move(p(7,1), p(5,0));
    board.ShowBoard();

    board.move(p(2,2), p(4,3));
    board.ShowBoard();

    board.move(p(5,0), p(7,1));
    board.ShowBoard();

    board.move(p(4,3), p(6,2));
    board.ShowBoard();

    board.move(p(7,1), p(5,0));
    board.ShowBoard();

    board.move(p(6,2), p(7,4));
    board.ShowBoard();

    board.move(p(5,0), p(7,1));
    board.ShowBoard();

    if (board.checkWin()!=0)
    {
        std::cout << board.checkWin() << std::endl;
    }
    
}