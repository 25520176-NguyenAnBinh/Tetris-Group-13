#include "Piece.h"

Piece::Piece() {
    x = 4; // Vị trí xuất phát mặc định ở giữa trên cùng
    y = 0;
}

Piece::~Piece() {}

void Piece::rotate() {
    char temp[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[j][3 - i] = matrix[i][j];
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = temp[i][j];
        }
    }
}

char Piece::getCell(int i, int j) const {
    return matrix[i][j];
}

char Piece::getType() const {
    return type;
}
