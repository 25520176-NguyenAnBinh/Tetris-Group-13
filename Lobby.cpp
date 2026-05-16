#include "Lobby.h"
#include <iostream>
#include <conio.h>

using namespace std;

Lobby::Lobby()
{
    selected = 0;
}

void Lobby::draw()
{
    system("cls");

    cout << "====== TETRIS ======\n\n";

    if (selected == 0)
        cout << "> Start Game\n";
    else
        cout << "  Start Game\n";

    if (selected == 1)
        cout << "> Difficulty\n";
    else
        cout << "  Difficulty\n";

    if (selected == 2)
        cout << "> Exit\n";
    else
        cout << "  Exit\n";
}

int Lobby::update()
{
    while (true)
    {
        draw();

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
            return selected;
        }
    }
}