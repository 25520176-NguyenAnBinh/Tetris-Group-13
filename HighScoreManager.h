#pragma once
#include <fstream>

class HighScoreManager {
private:
    const char* filename = "highscore.txt";

public:
    // Đọc điểm kỷ lục từ file
    int loadHighScore() {
        std::ifstream file(filename);
        int highScore = 0;
        if (file >> highScore) {
            return highScore;
        }
        return 0; // Trả về 0 nếu file chưa có dữ liệu hoặc chưa tồn tại
    }

    // Kiểm tra và cập nhật kỷ lục mới
    bool updateHighScore(int currentScore) {
        int currentHigh = loadHighScore();
        if (currentScore > currentHigh) {
            std::ofstream file(filename);
            if (file << currentScore) {
                return true; // Đã cập nhật kỷ lục mới thành công
            }
        }
        return false; // Không phá được kỷ lục
    }
};
