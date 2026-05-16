#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include "Board.h"
#include "DerivedPiece.h" 

using namespace std;

class GameEngine {
private:
    Board gameBoard;
    Piece* currentPiece;
    int speed;
    bool gameOver;
    int score;

    // Hàm di chuyển con trỏ console (Giữ nguyên từ code gốc)
    void gotoxy(int x, int y) {
        COORD c = { (SHORT)x, (SHORT)y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    }

    // Tương đương hàm khởi tạo khối gạch + copyBlocks() cũ
    void spawnPiece() {
        int r = rand() % 7;
        switch (r) {
        case 0: currentPiece = new IPiece(); break;
        case 1: currentPiece = new OPiece(); break;
        case 2: currentPiece = new TPiece(); break;
        case 3: currentPiece = new SPiece(); break;
        case 4: currentPiece = new ZPiece(); break;
        case 5: currentPiece = new JPiece(); break;
        case 6: currentPiece = new LPiece(); break;
        }
        // Đặt vị trí xuất phát giống code cũ của em
        currentPiece->x = 4;
        currentPiece->y = 0;
        if (gameBoard.checkCollision(*currentPiece, currentPiece->x, currentPiece->y)) {
    gameOver = true;
}
    }

    // Tương đương khối lệnh if(_kbhit()) trong code gốc
    void handleInput() {
        if (_kbhit()) {
            char c = _getch();
            if (c == 'a' && !gameBoard.checkCollision(*currentPiece, currentPiece->x - 1, currentPiece->y))
                currentPiece->x--;

            if (c == 'd' && !gameBoard.checkCollision(*currentPiece, currentPiece->x + 1, currentPiece->y))
                currentPiece->x++;

            if (c == 'x' && !gameBoard.checkCollision(*currentPiece, currentPiece->x, currentPiece->y + 1))
                currentPiece->y++;

            if (c == 'w') {
                currentPiece->rotate();
                // Nếu xoay mà bị đè vào tường -> xoay ngược lại 3 lần (về như cũ)
                if (gameBoard.checkCollision(*currentPiece, currentPiece->x, currentPiece->y)) {
                    currentPiece->rotate();
                    currentPiece->rotate();
                    currentPiece->rotate();
                }
            }
            if (c == 'q') exit(0); // Thoát game ngay lập tức như code gốc
        }
    }

    // Tương đương hàm draw() cũ, nhưng lấy dữ liệu thông qua OOP
    void draw() {
        gotoxy(0, 0);
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                bool isPieceDrawn = false;

                // 1. Kiểm tra xem tọa độ (i, j) có nằm trong vùng của viên gạch đang lơ lửng không
                if (currentPiece != nullptr &&
                    i >= currentPiece->y && i < currentPiece->y + 4 &&
                    j >= currentPiece->x && j < currentPiece->x + 4)
                {
                    char pieceChar = currentPiece->getCell(i - currentPiece->y, j - currentPiece->x);
                    if (pieceChar != ' ') {
                        cout << pieceChar << pieceChar; // In gạch lơ lửng
                        isPieceDrawn = true;
                    }
                }

                // 2. Nếu không có gạch lơ lửng ở ô này, in nền của Board
                if (!isPieceDrawn) {
                    char boardChar = gameBoard.getCell(i, j);
                    if (boardChar == '#') cout << "##";
                    else if (boardChar == ' ') cout << "  ";
                    else cout << boardChar << boardChar; // In gạch đã khóa
                }
            }
            cout << "\n";
        }
        cout << "\nScore: " << score << endl;
    }

public:
    GameEngine() {
        speed = 200; // Giữ nguyên tốc độ gốc
        currentPiece = nullptr;
        gameOver = false;
        score=0;

        // Ẩn con trỏ chuột
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(out, &cursorInfo);
    }

    ~GameEngine() {
        if (currentPiece != nullptr) delete currentPiece;
    }

    // Hàm thay thế cho int main() cũ
    void run() {
        srand((unsigned int)time(0));
        system("cls");
        spawnPiece();

        // Vòng lặp vô tận y hệt code gốc
        while (!gameOver) {
            handleInput();

            // Logic rơi y hệt code cũ: canMove(0,1) thì y++, else khóa và đẻ mới
            if (!gameBoard.checkCollision(*currentPiece, currentPiece->x, currentPiece->y + 1)) {
                currentPiece->y++;
            }
            else {
                gameBoard.lockPiece(*currentPiece, currentPiece->x, currentPiece->y);
                int linesCleared = gameBoard.removeLine();
                // Xóa 1 dòng tăng 5ms, dòng thứ 2 tăng 10ms,... maxspeed là 50ms
                speed = max(50, speed - linesCleared * 5);

                // Giải phóng RAM của viên gạch cũ trước khi tạo viên mới
                delete currentPiece;
                spawnPiece();
            }

            draw();
            Sleep(speed);
        }
        gotoxy(10, 10);
cout << "===== GAME OVER =====";

gotoxy(10, 12);
system("pause");
    }
};
