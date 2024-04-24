#include "Board.hpp"
#include "Piece.hpp"
#include <cmath>

Position::Position(int x, int y)
{
    this->x = x;
    this->y = y;
}
bool Position::isOnBoard()
{
    return 0 <= x && x < 8 && 0 <= y && y < 8;
}

Piece::Piece(CAMP camp, Position position, char representation, Board& gameBoard) : camp(camp), pos(position), rep(representation), board(gameBoard){}

char Piece::getRepresentation() const
{
    return rep;
}
CAMP Piece::getCamp() const
{
    return camp;
}
Board& Piece::getBoard() const{
    return this->board;
};
void Piece::setPos(Position position){
    this->pos=position;
};

Tour::Tour(CAMP camp, Position position, Board& gameBoard) : Piece(camp, position, 'T',gameBoard) {}

bool Tour::canMoveTo(Position newPos)
{
    // Vérifier si la nouvelle position est sur la même ligne ou colonne
    if (newPos.x == pos.x || newPos.y == pos.y)
    {
        // Vérifier s'il n'y a pas d'obstacles entre la position actuelle et la nouvelle position
        int dx = newPos.x - pos.x;
        int dy = newPos.y - pos.y;
        int stepX = (dx > 0) ? 1 : ((dx < 0) ? -1 : 0);
        int stepY = (dy > 0) ? 1 : ((dy < 0) ? -1 : 0);
        for (int x = pos.x + stepX, y = pos.y + stepY; x != newPos.x || y != newPos.y; x += stepX, y += stepY)
        {
            if (getBoard().getPieceAt(Position(x, y)) != nullptr)
            {
                return false; // Il y a un obstacle sur le chemin
            }
        }
        return true; // Le mouvement est valide
    }
    return false; // La nouvelle position n'est pas sur la même ligne ou colonne
}

Cavalier::Cavalier(CAMP camp, Position position, Board& gameBoard) : Piece(camp, position, 'C',gameBoard) {}

bool Cavalier::canMoveTo(Position newPos)
{
    int dx = abs(newPos.x - pos.x);
    int dy = abs(newPos.y - pos.y);
    return ((dx == 1 && dy == 2) || (dx == 2 && dy == 1));
}

Fou::Fou(CAMP camp, Position position, Board& gameBoard) : Piece(camp, position, 'F',gameBoard) {}

bool Fou::canMoveTo(Position newPos)
{
    if (pos.x == newPos.x || pos.y == newPos.y)
        return false; // Le fou ne peut pas se déplacer en ligne droite

    int dx = newPos.x - pos.x;
    int dy = newPos.y - pos.y;
    int stepX = (dx > 0) ? 1 : -1;
    int stepY = (dy > 0) ? 1 : -1;

    for (int x = pos.x + stepX, y = pos.y + stepY; x != newPos.x || y != newPos.y; x += stepX, y += stepY)
    {
        if (getBoard().getPieceAt(Position(x, y)) != nullptr)
        {
            return false; // Il y a un obstacle sur le chemin
        }
    }
    return true;
}

Roi::Roi(CAMP camp, Position position, Board& gameBoard) : Piece(camp, position, 'R',gameBoard) {}

bool Roi::canMoveTo(Position newPos)
{
    int dx = abs(newPos.x - pos.x);
    int dy = abs(newPos.y - pos.y);
    return (dx <= 1 && dy <= 1);
}

Reine::Reine(CAMP camp, Position position, Board& gameBoard) : Piece(camp, position, 'Q',gameBoard) {}

bool Reine::canMoveTo(Position newPos)
{
    if (pos.x == newPos.x || pos.y == newPos.y)
    {
        // Vérifier s'il n'y a pas d'obstacles entre la position actuelle et la nouvelle position
        int dx = newPos.x - pos.x;
        int dy = newPos.y - pos.y;
        int stepX = (dx > 0) ? 1 : ((dx < 0) ? -1 : 0);
        int stepY = (dy > 0) ? 1 : ((dy < 0) ? -1 : 0);
        for (int x = pos.x + stepX, y = pos.y + stepY; x != newPos.x || y != newPos.y; x += stepX, y += stepY)
        {
            if (getBoard().getPieceAt(Position(x, y)) != nullptr)
            {
                return false; // Il y a un obstacle sur le chemin
            }
        }
        return true; // Le mouvement est valide
    }
    else if (abs(newPos.x - pos.x) == abs(newPos.y - pos.y))
    {
        // Mouvement diagonal
        int dx = newPos.x - pos.x;
        int dy = newPos.y - pos.y;
        int stepX = (dx > 0) ? 1 : -1;
        int stepY = (dy > 0) ? 1 : -1;

        for (int x = pos.x + stepX, y = pos.y + stepY; x != newPos.x || y != newPos.y; x += stepX, y += stepY)
        {
            if (getBoard().getPieceAt(Position(x, y)) != nullptr)
            {
                return false; // Il y a un obstacle sur le chemin
            }
        }
        return true;
    }
    return false;
}

Pion::Pion(CAMP camp, Position position, Board& gameBoard) : Piece(camp, position, 'P', gameBoard), hasMoved(false) {}

bool Pion::canMoveTo(Position newPos)
{
    
    int dx = newPos.x - pos.x;
    int dy = newPos.y - pos.y;
    if (!hasMoved)
    {
        if ((dx == camp || dx == 2 * camp) && dy == 0)
        {
            // Déplacement initial
            if (dx == 2 * camp)
            {
                // Vérifier si le chemin est libre
                if (getBoard().getPieceAt(Position(pos.x + camp, pos.y)) != nullptr)
                {
                    return false; // Il y a un obstacle sur le chemin
                }
            }
            return true;
        }
    }
    else
    {
        if (dx == camp && dy == 0)
        {
            return true;
        }
    }
    return false;
}