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
    Piece* nextPiece;
    int speed;
    Piece* holdPiece;      
    bool isHoldEmpty;      
    bool canHold;
    int level;
    bool gameOver;
    int score;

    // Hàm di chuyển con trỏ console (Giữ nguyên từ code gốc)
    void gotoxy(int x, int y) {
        COORD c = { (SHORT)x, (SHORT)y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    }

    // Hàm phụ trợ dùng chung để sinh ngẫu nhiên một con trỏ khối gạch
    Piece* createRandomPiece() {
        int r = rand() % 7;
        switch (r) {
            case 0: return new IPiece();
            case 1: return new OPiece();
            case 2: return new TPiece();
            case 3: return new SPiece();
            case 4: return new ZPiece();
            case 5: return new JPiece();
            case 6: return new LPiece();
        }
        return new IPiece();
    }

    void spawnPiece() {
        // Nếu là lượt đầu tiên chạy game, chưa có khối tiếp theo -> tạo mới
        if (nextPiece == nullptr) {
            nextPiece = createRandomPiece();
        }
        
        // Lấy khối "tiếp theo" chuyển sang làm khối "hiện tại"
        currentPiece = nextPiece;
        
        // Tiếp tục chuẩn bị khối gạch mới cho lượt sau nữa
        nextPiece = createRandomPiece();

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
            if (c == 'c' && canHold) {
                if (isHoldEmpty) {
                    // Lần đầu bấm: Cất gạch hiện tại đi, đẻ ra gạch mới
                    holdPiece = currentPiece;
                    isHoldEmpty = false;
                    spawnPiece();
                }
                else {
                    // Đã có gạch: Hoán đổi 2 con trỏ cho nhau
                    Piece* temp = currentPiece;
                    currentPiece = holdPiece;
                    holdPiece = temp;

                    // Đặt lại tọa độ cho gạch vừa lấy ra từ Hold
                    currentPiece->x = 4;
                    currentPiece->y = 0;
                }

                // Khóa lại, không cho đổi liên tục trong lúc đang rơi nữa
                canHold = false;
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
        cout << "Level: " << level << endl;
        cout << "\nScore: " << score << endl;
        // Xác định tọa độ X bên phải bàn cờ (Độ rộng bàn cờ kí tự kép W*2 + 5 ô khoảng cách)
        int offsetX = W * 2 + 5; 
        
        gotoxy(offsetX, 2);  cout << "==================";
        gotoxy(offsetX, 3);  cout << "   NEXT PIECE     ";
        gotoxy(offsetX, 4);  cout << "==================";
        
        // Vòng lặp quét ma trận 4x4 của khối gạch tiếp theo
        for (int i = 0; i < 4; i++) {
            gotoxy(offsetX, 5 + i);
            cout << "    "; // Tạo lề trống bên trái khung gạch
            for (int j = 0; j < 4; j++) {
                char nextChar = nextPiece->getCell(i, j);
                if (nextChar != ' ') cout << nextChar << nextChar;
                else cout << "  ";
            }
            cout << "    ";
        }
        gotoxy(offsetX, 9);  cout << "==================";
    } // Đây là dấu đóng ngoặc nhọn kết thúc hàm draw() của bạn

public:
    GameEngine() {
        speed = 200; // Giữ nguyên tốc độ gốc
        currentPiece = nullptr;
        nextPiece = nullptr;
        holdPiece = nullptr;
        isHoldEmpty = true;
        canHold = true;
        level = 0;
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
        if (nextPiece != nullptr) delete nextPiece;
        if (holdPiece != nullptr) delete holdPiece;
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
                if (linesCleared == 1) score += 100;
                else if (linesCleared == 2) score += 300;
                else if (linesCleared == 3) score += 500;
                else if (linesCleared == 4) score += 800;
                level = score / 500;
                
                speed = max(50, 200 - level * 20);

                // Giải phóng RAM của viên gạch cũ trước khi tạo viên mới
                delete currentPiece;
                spawnPiece();
                canHold = true;
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
