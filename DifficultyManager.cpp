#include "DifficultyManager.h"
#include <iostream>
#include <conio.h>

using namespace std;

DifficultyManager::DifficultyManager()
{
    difficulty = 1;
}

void DifficultyManager::chooseDifficulty()
{
    int selected = 0;

    while (true)
    {
        system("cls");

        cout << "===== SELECT DIFFICULTY =====\n\n";

        if (selected == 0)
            cout << "> Easy\n";
        else
            cout << "  Easy\n";

        if (selected == 1)
            cout << "> Medium\n";
        else
            cout << "  Medium\n";

        if (selected == 2)
            cout << "> Hard\n";
        else
            cout << "  Hard\n";

        char c = _getch();

        if (c == 'w')
        {
            selected--;

            if (selected < 0)
                selected = 2;
        }

        else if (c == 's')
        {
            selected++;

            if (selected > 2)
                selected = 0;
        }

        else if (c == 13)
        {
            difficulty = selected;
            return;
        }
    }
}

int DifficultyManager::getSpeed() const
{
    switch (difficulty)
    {
    case 0:
        return 300;

    case 1:
        return 200;

    case 2:
        return 100;
    }

    return 200;
}

int DifficultyManager::getDifficulty() const
{
    return difficulty;
}