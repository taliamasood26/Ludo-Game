#include <iostream>
#include <windows.h>
#include "globals.h"
#include "utils.h"
#include "board.h"

using namespace std;

int sameCell(int r, int c, int p, int t)
{
    int pos = tokenPos[p][t];

    if (pos == -1)
    {
        if (baseR[p][t] == r && baseC[p][t] == c)
        {
            return 1;
        }
    }
    else if (pos >= 0 && pos <= 51)
    {
        int g = (startIndex[p] + pos) % 52;
        if (trackR[g] == r && trackC[g] == c)
        {
            return 1;
        }
    }
    else if (pos >= 52 && pos <= 56)
    {
        int k = pos - 52;
        if (pathR[p][k] == r && pathC[p][k] == c)
        {
            return 1;
        }
    }

    return 0;
}

char cellToken(int r, int c)
{
    int found = 0;
    int oldp = -1;
    char ch = ' ';

    for (int p = 0; p < 2; p++)
    {
        for (int t = 0; t < 4; t++)
        {
            if (sameCell(r, c, p, t) == 1)
            {
                if (found == 0)
                {
                    if (p == 0)
                    {
                        ch = 'R';
                    }
                    else
                    {
                        ch = 'Y';
                    }

                    oldp = p;
                    found = 1;
                }
                else
                {
                    if (oldp != p)
                    {
                        ch = 'X';
                    }
                }
            }
        }
    }

    if (found == 1)
    {
        return ch;
    }

    return board[r][c];
}

void cellColor(int r, int c, char ch)
{
    if (ch == 'R' || ch == 'r')
    {
        color(12);
    }
    else if (ch == 'Y' || ch == 'y')
    {
        color(14);
    }
    else if (ch == 'X')
    {
        color(12);
    }
    else if (ch == '*')
    {
        color(10);
    }
    else if (ch == 'F')
    {
        color(11);
    }
    else if (ch == '+')
    {
        if (c < 7)
        {
            color(12);
        }
        else
        {
            color(14);
        }
    }
    else
    {
        color(7);
    }
}

void initBoard()
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            board[i][j] = ' ';
        }
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            board[i][j] = 'r';
            board[i + 10][j + 10] = 'y';
        }
    }

    for (int i = 0; i < 52; i++)
    {
        board[trackR[i]][trackC[i]] = '.';
    }

    for (int p = 0; p < 2; p++)
    {
        for (int i = 0; i < 5; i++)
        {
            board[pathR[p][i]][pathC[p][i]] = '+';
        }
    }

    int safe[8] = { 0,8,13,21,26,34,39,47 };

    for (int i = 0; i < 8; i++)
    {
        board[trackR[safe[i]]][trackC[safe[i]]] = '*';
    }

    board[7][7] = 'F';
}

void drawBoard()
{
    gotoxy(0, 0);
    color(15);

    cout << "2 PLAYER CONSOLE LUDO GAME                                      " << endl;
    cout << "R = Red, Y = Yellow, * = Safe, + = Home Path, F = Finish          " << endl;

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            char ch = cellToken(i, j);
            cellColor(i, j, ch);
            cout << " " << ch;
        }

        color(15);
        cout << "        " << endl;
    }

    for (int i = 18; i < 30; i++)
    {
        gotoxy(0, i);
        cout << "                                                                                ";
    }

    resetColor();
}

void showWinner(int p)
{
    drawBoard();
    gotoxy(0, 18);

    if (p == 0)
    {
        color(12);
    }
    else
    {
        color(14);
    }

    cout << "Winner: " << playerName[p] << "!" << endl;

    color(15);
    cout << "All 4 tokens reached the finish area." << endl;

    winSound();
    resetColor();
}