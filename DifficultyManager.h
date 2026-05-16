#pragma once

class DifficultyManager
{
private:
    int difficulty;

public:
    DifficultyManager();

    void chooseDifficulty();

    int getSpeed() const;

    int getDifficulty() const;
};