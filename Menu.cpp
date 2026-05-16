#include "Menu.h"

void Menu::drawMenu()
{
    system("cls");

    cout << "====================\n";
    cout << "       TETRIS       \n";
    cout << "====================\n\n";

    cout << "1. Play\n";
    cout << "2. Difficulty\n";
    cout << "3. Exit\n\n";

    cout << "Choose: ";
}

int Menu::chooseMenu()
{
    drawMenu();

    char c = _getch();

    return c - '0';
}