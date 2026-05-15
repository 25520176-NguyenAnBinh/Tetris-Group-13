#pragma once
#include <iostream>

using namespace std;

#define H 20
#define W 15

class Piece
{
protected:
    char matrix[4][4];
    char type;

public:
    int x;
    int y;

public:
    Piece();

    virtual ~Piece();
    virtual void rotateBlocks();
    void copyBlocks(const char block[4][4]);
    void boardDelBlock(char board[][W]);
    void block2Board(char board[][W]);
    bool canMove(char board[][W], int dx, int dy);
    bool canRotate(char board[][W]);
    char getCell(int i, int j) const;
    char getType() const;
};