#include "Piece.h"

Piece::Piece()
{
    x = 5;
    y = 0;
    type = ' ';

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix[i][j] = ' ';
        }
    }
}

Piece::~Piece()
{
}

void Piece::copyBlocks(const char block[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix[i][j] = block[i][j];
        }
    }
}

void Piece::boardDelBlock(char board[][W])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (matrix[i][j] != ' ')
            {
                board[y + i][x + j] = ' ';
            }
        }
    }
}

void Piece::block2Board(char board[][W])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (matrix[i][j] != ' ')
            {
                board[y + i][x + j] = matrix[i][j];
            }
        }
    }
}

bool Piece::canMove(char board[][W], int dx, int dy)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (matrix[i][j] != ' ')
            {
                int tx = x + j + dx;
                int ty = y + i + dy;

                if (tx < 1 || tx >= W - 1 || ty >= H - 1)
                {
                    return false;
                }

                if (board[ty][tx] != ' ')
                {
                    return false;
                }
            }
        }
    }

    return true;
}

bool Piece::canRotate(char board[][W])
{
    char temp[4][4];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            temp[j][3 - i] = matrix[i][j];
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (temp[i][j] != ' ')
            {
                int tx = x + j;
                int ty = y + i;

                if (tx < 1 || tx >= W - 1 || ty >= H - 1)
                {
                    return false;
                }

                if (board[ty][tx] != ' ')
                {
                    return false;
                }
            }
        }
    }

    return true;
}

void Piece::rotateBlocks()
{
    char temp[4][4];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            temp[j][3 - i] = matrix[i][j];
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix[i][j] = temp[i][j];
        }
    }
}

char Piece::getCell(int i, int j) const
{
    return matrix[i][j];
}

char Piece::getType() const
{
    return type;
}