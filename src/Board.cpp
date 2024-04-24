#include "Board.hpp"
#include <iostream>

Board::Board()
{
    board = new Piece **[8];
    for (int i = 0; i < 8; ++i)
    {
        board[i] = new Piece *[8];
        if (i == 0)
        {
            board[i][0] = new Tour(CAMP::BLANC, Position(i, 0), *this);
            board[i][1] = new Cavalier(CAMP::BLANC, Position(i, 1), *this);
            board[i][2] = new Fou(CAMP::BLANC, Position(i, 2), *this);
            board[i][3] = new Reine(CAMP::BLANC, Position(i, 3), *this);
            board[i][4] = new Roi(CAMP::BLANC, Position(i, 4), *this);
            board[i][5] = new Fou(CAMP::BLANC, Position(i, 5), *this);
            board[i][6] = new Cavalier(CAMP::BLANC, Position(i, 6), *this);
            board[i][7] = new Tour(CAMP::BLANC, Position(i, 7), *this);
        }
        else if (i == 1)
        {
            for (int j = 0; j < 8; ++j)
            {
                board[i][j] = new Pion(CAMP::BLANC, Position(i, j), *this);
            }
        }
        else if (i == 6)
        {
            for (int j = 0; j < 8; ++j)
            {
                board[i][j] = new Pion(CAMP::NOIR, Position(i, j), *this);
            }
        }
        else if (i == 7)
        {
            board[i][0] = new Tour(CAMP::NOIR, Position(i, 0), *this);
            board[i][1] = new Cavalier(CAMP::NOIR, Position(i, 1), *this);
            board[i][2] = new Fou(CAMP::NOIR, Position(i, 2), *this);
            board[i][3] = new Reine(CAMP::NOIR, Position(i, 3), *this);
            board[i][4] = new Roi(CAMP::NOIR, Position(i, 4), *this);
            board[i][5] = new Fou(CAMP::NOIR, Position(i, 5), *this);
            board[i][6] = new Cavalier(CAMP::NOIR, Position(i, 6), *this);
            board[i][7] = new Tour(CAMP::NOIR, Position(i, 7), *this);
        }
        else
        {
            for (int j = 0; j < 8; ++j)
            {
                board[i][j] = nullptr;
            }
        }
    }
    turn = CAMP::BLANC;
}
Piece *Board::getPieceAt(Position pos)
{
    return board[pos.x][pos.y];
}
void Board::ShowBoard()
{
    std::cout << "________________________" << std::endl;
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            Piece *piece = getPieceAt(Position(i, j));
            if (board[i][j] != nullptr)
            {
                char couleur;
                if (piece->getCamp() == CAMP::BLANC)
                {
                    couleur = 'b';
                }
                else
                {
                    couleur = 'n';
                }

                std::cout << piece->getRepresentation() << couleur << " ";
            }
            else
            {
                std::cout << "-- ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "________________________" << std::endl;
}
bool Board::move(Position initpos, Position newpos)
{
    Piece *piece = getPieceAt(initpos);
    Piece *pieceTo = getPieceAt(newpos);
    if (piece != nullptr &&
        static_cast<int>(piece->getCamp()) == turn &&
        piece->canMoveTo(newpos) &&
        (pieceTo == nullptr || (pieceTo->getCamp() != piece->getCamp())))
    {
        turn = -turn;
        board[newpos.x][newpos.y] = piece;
        piece->setPos(newpos);
        board[initpos.x][initpos.y] = nullptr;
        return true;
    }
    return false;
}
int Board::checkWin()
{
    bool blancEnVie = false;
    bool noirEnVie = false;
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (board[i][j] != nullptr)
            {
                blancEnVie = blancEnVie || (board[i][j]->getCamp() == CAMP::BLANC && board[i][j]->getRepresentation() == 'R');
                noirEnVie = noirEnVie || (board[i][j]->getCamp() == CAMP::NOIR && board[i][j]->getRepresentation() == 'R');
            }
        }
    }
    if (blancEnVie && !noirEnVie)
    {
        return CAMP::BLANC;
    }
    if (noirEnVie && !blancEnVie)
    {
        return CAMP::NOIR;
    }
    return 0;
}