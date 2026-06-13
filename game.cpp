#include <iostream>
#include <windows.h>
#include "globals.h"
#include "utils.h"
#include "board.h"
#include "fileio.h"
#include "game.h"

using namespace std;

int isSafeGlobal(int g)
{
    int safe[8] = { 0,8,13,21,26,34,39,47 };

    for (int i = 0; i < 8; i++)
    {
        if (g == safe[i])
        {
            return 1;
        }
    }

    if (g == startIndex[0] || g == startIndex[1])
    {
        return 1;
    }

    return 0;
}

void printTokenStatus()
{
    gotoxy(0, 18);
    color(15);

    cout << "Current turn: ";

    if (currentPlayer == 0)
    {
        color(12);
    }
    else
    {
        color(14);
    }

    cout << playerName[currentPlayer] << "                                      " << endl;

    color(15);
    cout << "Score: " << playerName[0] << " = " << score[0] << " | " << playerName[1] << " = " << score[1] << "                  " << endl;

    for (int p = 0; p < 2; p++)
    {
        if (p == 0)
        {
            color(12);
            cout << "Red tokens:    ";
        }
        else
        {
            color(14);
            cout << "Yellow tokens: ";
        }

        for (int t = 0; t < 4; t++)
        {
            int pos = tokenPos[p][t];

            cout << "T" << t + 1 << ":";

            if (pos == -1)
            {
                cout << "Home";
            }
            else if (pos == 57)
            {
                cout << "Finish";
            }
            else if (pos >= 52)
            {
                cout << "Path" << pos - 51;
            }
            else
            {
                cout << "Track" << pos;
            }

            cout << "  ";
        }

        cout << "          " << endl;
    }

    resetColor();
}

int anyMove(int p, int dice)
{
    for (int t = 0; t < 4; t++)
    {
        if (canMove(p, t, dice) == 1)
        {
            return 1;
        }
    }

    return 0;
}

int showMenu()
{
    char ch[10];
    int choice = 0;

    gotoxy(0, 0);
    color(15);

    cout << "==============================" << endl;
    cout << "        LUDO GAME MENU        " << endl;
    cout << "==============================" << endl;
    cout << "1. New Game" << endl;

    if (saveFileExists() == 1)
    {
        cout << "2. Resume Game" << endl;
    }
    else
    {
        cout << "2. Resume Game (no saved game)" << endl;
    }

    cout << "3. Quit" << endl;
    cout << "Enter choice: ";

    cin.getline(ch, 10);

    if (ch[0] >= '1' && ch[0] <= '3')
    {
        choice = ch[0] - '0';
    }

    return choice;
}

void getPlayerNames()
{
    cout << "Enter Player 1 name (Red): ";
    cin.getline(playerName[0], 30);

    if (playerName[0][0] == '\0')
    {
        playerName[0][0] = 'P';
        playerName[0][1] = '1';
        playerName[0][2] = '\0';
    }

    cout << "Enter Player 2 name (Yellow): ";
    cin.getline(playerName[1], 30);

    if (playerName[1][0] == '\0')
    {
        playerName[1][0] = 'P';
        playerName[1][1] = '2';
        playerName[1][2] = '\0';
    }
}

void newGame()
{
    for (int p = 0; p < 2; p++)
    {
        score[p] = 0;

        for (int t = 0; t < 4; t++)
        {
            tokenPos[p][t] = -1;
        }
    }

    currentPlayer = 0;
    diceValue = 0;
    gameOver = 0;
    extraTurn = 0;
}

int canMove(int p, int t, int dice)
{
    int pos = tokenPos[p][t];

    if (pos == 57)
    {
        return 0;
    }

    if (pos == -1)
    {
        if (dice == 6)
        {
            return 1;
        }

        return 0;
    }

    if (pos + dice <= 57)
    {
        return 1;
    }

    return 0;
}

int selectToken(int p, int dice)
{
    char ch[10];
    int t = -1;

    while (t == -1)
    {
        gotoxy(0, 24);
        color(15);
        cout << "Choose token 1 to 4:                                      ";

        cin.getline(ch, 10);

        if (ch[0] >= '1' && ch[0] <= '4')
        {
            int k = ch[0] - '1';

            if (canMove(p, k, dice) == 1)
            {
                t = k;
            }
            else
            {
                gotoxy(0, 25);
                color(12);
                cout << "This token cannot move. Choose another token.              ";
                Sleep(900);
            }
        }
        else
        {
            gotoxy(0, 25);
            color(12);
            cout << "Invalid choice. Enter 1, 2, 3 or 4.                        ";
            Sleep(900);
        }

        gotoxy(0, 25);
        cout << "                                                                                ";
    }

    resetColor();

    return t;
}

void moveToken(int p, int t, int dice)
{
    if (tokenPos[p][t] == -1 && dice == 6)
    {
        tokenPos[p][t] = 0;
    }
    else
    {
        tokenPos[p][t] = tokenPos[p][t] + dice;
    }

    if (tokenPos[p][t] == 57)
    {
        score[p]++;
    }

    moveSound();
    checkCapture(p, t);
}

void checkCapture(int p, int t)
{
    if (tokenPos[p][t] < 0 || tokenPos[p][t]>51)
    {
        return;
    }

    int g = (startIndex[p] + tokenPos[p][t]) % 52;

    if (isSafeGlobal(g) == 1)
    {
        return;
    }

    int op = 1 - p;

    for (int i = 0; i < 4; i++)
    {
        if (tokenPos[op][i] >= 0 && tokenPos[op][i] <= 51)
        {
            int og = (startIndex[op] + tokenPos[op][i]) % 52;

            if (og == g)
            {
                tokenPos[op][i] = -1;

                gotoxy(0, 26);
                color(12);
                cout << "Capture! Opponent token sent back home.                    ";

                captureSound();
                Sleep(1200);
            }
        }
    }

    resetColor();
}

int checkWin(int p)
{
    if (score[p] == 4)
    {
        return 1;
    }

    return 0;
}

void gameLoop()
{
    char op[10];

    while (gameOver == 0)
    {
        drawBoard();
        printTokenStatus();

        gotoxy(0, 23);
        color(15);
        cout << "Press ENTER to roll dice, S to save, Q to quit : ";

        cin.getline(op, 10);

        if (op[0] == 'S' || op[0] == 's')
        {
            gotoxy(0, 24);
            saveGame();
            Sleep(1000);
        }
        else if (op[0] == 'Q' || op[0] == 'q')
        {
            gotoxy(0, 24);
            cout << "Game stopped.";
            Sleep(1000);
            gameOver = 1;
        }
        else
        {
            diceValue = rollDice();

            drawBoard();
            printTokenStatus();

            gotoxy(0, 23);
            color(14);
            cout << "Dice value: " << diceValue << "                                      ";

            resetColor();

            if (anyMove(currentPlayer, diceValue) == 0)
            {
                gotoxy(0, 24);
                color(12);
                cout << "No valid move available.                                    ";

                Sleep(1200);

                if (diceValue != 6)
                {
                    currentPlayer = 1 - currentPlayer;
                }
            }
            else
            {
                int t = selectToken(currentPlayer, diceValue);

                moveToken(currentPlayer, t, diceValue);

                if (checkWin(currentPlayer) == 1)
                {
                    gameOver = 1;
                    showWinner(currentPlayer);
                    clearSave();
                }
                else
                {
                    if (diceValue == 6)
                    {
                        gotoxy(0, 27);
                        color(14);
                        cout << "Rolled 6! Extra turn.                                      ";
                        Sleep(1000);
                    }
                    else
                    {
                        currentPlayer = 1 - currentPlayer;
                    }
                }
            }
        }
    }

    resetColor();
}