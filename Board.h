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

    bool checkCollision(const Piece& s, int nx, int ny) {
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

    void lockPiece(const Piece& s, int x, int y) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (s.getCell(i, j) != ' ') grid[y + i][x + j] = s.getCell(i, j);
    }

int removeLine() {
    int linesClearedThisTurn = 0; 
    for (int i = 0; i < H - 1; i++) {
        bool full = true;
        for (int j = 1; j < W - 1; j++) {
            if (grid[i][j] == ' ') { full = false; break; }
        }
        if (full) {
            linesClearedThisTurn++; // Tăng số lượng dòng xóa được
            for (int k = i; k > 0; k--) {
                for (int j = 1; j < W - 1; j++) {
                    grid[k][j] = grid[k - 1][j];
                }
            }
            for (int j = 1; j < W - 1; j++) grid[0][j] = ' ';
            i--; 
        }
    }
    return linesClearedThisTurn;
    }

    char getCell(int r, int c) const { return grid[r][c]; }
};

