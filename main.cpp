#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "globals.h"
#include "board.h"
#include "game.h"
#include "fileio.h"

using namespace std;

int main()
{
    srand(time(0));

    initBoard();

    int choice = 0;

    while (choice != 3)
    {
        choice = showMenu();

        if (choice == 1)
        {
            getPlayerNames();
            newGame();
            gameLoop();
            choice = 3;
        }
        else if (choice == 2)
        {
            if (loadGame() == 1)
            {
                gameOver = 0;
                gameLoop();
                choice = 3;
            }
            else
            {
                cout << "No saved game found." << endl;
                Sleep(1000);
            }
        }
        else if (choice == 3)
        {
            cout << "Goodbye!" << endl;
        }
        else
        {
            cout << "Invalid menu choice." << endl;
            Sleep(1000);
        }
    }

    system("pause");
    return 0;
}