#include"Piece.h"
class IPiece : public Piece {
public:
    IPiece() {
        type = 'I';
        char block[4][4] = { {' ','I',' ',' '}, {' ','I',' ',' '}, {' ','I',' ',' '}, {' ','I',' ',' '} };
        for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) matrix[i][j] = block[i][j];
    }
};
class OPiece : public Piece {
public:
    OPiece() {
        type = 'O';
        char block[4][4] = { {' ',' ',' ',' '}, {' ','O','O',' '}, {' ','O','O',' '}, {' ',' ',' ',' '} };
        for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) matrix[i][j] = block[i][j];
    }
    // Ghi đè đa hình: Khối vuông không xoay
    void rotate() override { /* Do nothing */ }
};
class TPiece : public Piece {
public:
    TPiece() {
        type = 'T';
        char block[4][4] = { {' ',' ',' ',' '}, {' ','T',' ',' '}, {'T','T','T',' '}, {' ',' ',' ',' '} };
        for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) matrix[i][j] = block[i][j];
    }
};
class SPiece : public Piece {
public:
    SPiece() {
        type = 'S';
        char block[4][4] = {
            {' ', ' ', ' ', ' '},
            {' ', 'S', 'S', ' '},
            {'S', 'S', ' ', ' '},
            {' ', ' ', ' ', ' '}
        };
        for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) matrix[i][j] = block[i][j];
    }
};
class ZPiece : public Piece {
public:
    ZPiece() {
        type = 'Z';
        char block[4][4] = {
            {' ', ' ', ' ', ' '},
            {'Z', 'Z', ' ', ' '},
            {' ', 'Z', 'Z', ' '},
            {' ', ' ', ' ', ' '}
        };
        for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) matrix[i][j] = block[i][j];
    }
};
class LPiece : public Piece {
public:
    LPiece() {
        type = 'L';
        char block[4][4] = {
            {' ', 'L', ' ', ' '},
            {' ', 'L', ' ', ' '},
            {' ', 'L', 'L', ' '},
            {' ', ' ', ' ', ' '}
        };
        for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) matrix[i][j] = block[i][j];
    }
};
class JPiece : public Piece {
public:
    JPiece() {
        type = 'J';
        char block[4][4] = {
            {' ', ' ', 'J', ' '},
            {' ', ' ', 'J', ' '},
            {' ', 'J', 'J', ' '},
            {' ', ' ', ' ', ' '}
        };
        for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) matrix[i][j] = block[i][j];
    }
};
