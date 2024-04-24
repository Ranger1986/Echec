#ifndef PIECE_HPP
#define PIECE_HPP
enum CAMP
{
    BLANC = 1,
    NOIR = -1
};

class Position
{
public:
    int x;
    int y;

    Position(int x, int y);

    bool isOnBoard();
};
class Board;
class Piece
{
protected:
    CAMP camp;
    Position pos;
    char rep;
    Board& board; 

public:
    Piece(CAMP camp, Position position, char representation,  Board& gameBoard);
    virtual bool canMoveTo(Position pos) = 0;
    char getRepresentation() const;
    CAMP getCamp() const;
    Board& getBoard() const;
    void setPos(Position position);
};

class Tour : public Piece
{
public:
    Tour(CAMP camp, Position position,  Board& gameBoard);
    bool canMoveTo(Position pos) override;
};

class Cavalier : public Piece
{
public:
    Cavalier(CAMP camp, Position position,  Board& gameBoard);
    bool canMoveTo(Position pos) override;
};

class Fou : public Piece
{
public:
    Fou(CAMP camp, Position position,  Board& gameBoard);
    bool canMoveTo(Position pos) override;
};

class Roi : public Piece
{
public:
    Roi(CAMP camp, Position position,  Board& gameBoard);
    bool canMoveTo(Position pos) override;
};

class Reine : public Piece
{
public:
    Reine(CAMP camp, Position position,  Board& gameBoard);
    bool canMoveTo(Position pos) override;
};

class Pion : public Piece
{
private:
    bool hasMoved;

public:
    Pion(CAMP camp, Position position,  Board& gameBoard);
    bool canMoveTo(Position pos) override;
};

#endif