#pragma once
#include <iostream>
using namespace std;

#define H 20
#define W 15

class Piece {
protected:
    char matrix[4][4];
    char type;

public:
    int x;             // Tọa độ x hiện tại trên bảng
    int y;             // Tọa độ y hiện tại trên bảng

    Piece()
    virtual ~Piece() 
    virtual void rotate() 
    char getCell(int , int ) const
    char getType() const 
};
