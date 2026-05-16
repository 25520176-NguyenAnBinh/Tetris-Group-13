#pragma once
#include "Piece.h"
#include <windows.h>
#include "GameEngine.h"

class Board {
private:
    char grid[20][15];
    int speed = 500;
public:
    Board() {
        for (int i = 0; i < 20; i++)
            for (int j = 0; j < 15; j++)
                if (i == 19 || j == 0 || j == 14) grid[i][j] = '#';
                else grid[i][j] = ' ';
    }
    int getSpeed() const { return speed; }

    bool checkCollision(const Shape& s, int nx, int ny) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (s.getCell(i, j) != ' ') {
                    int tx = nx + j;
                    int ty = ny + i;
                    if (tx <= 0 || tx >= 14 || ty >= 19 || grid[ty][tx] != ' ') return true;
                }
            }
        }
        return false;
    }

    void lockShape(const Shape& s, int x, int y) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (s.getCell(i, j) != ' ') grid[y + i][x + j] = s.getCell(i, j);
    }

void removeLine() {
        int j;
        bool removed = false;
        for (int i = 18; i > 0; i--) {
            // W - 1 tương đương 15 - 1 = 14 (cột sát tường phải)
            for (j = 1; j < 14; j++)
                if (grid[i][j] == ' ') break;
            if (j == 14) { 
                removed = true;
                for (int ii = i; ii > 0; ii--)
                    for (int j = 1; j < 14; j++)
                        grid[ii][j] = grid[ii - 1][j];
                i++; 
                draw();
                Sleep(200);
            }
        }
        if (removed) {
            speed -= 10;
            if (speed < 50)
                speed = 50;
        }
    }

    char getCell(int r, int c) const { return grid[r][c]; }
};

