#include <iostream>
#include <cstdlib>
#include <windows.h>
#include "utils.h"

using namespace std;

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void resetColor()
{
    color(15);
}

int rollDice()
{
    int d = 1;
    for (int i = 0; i < 10; i++)
    {
        d = rand() % 6 + 1;
        gotoxy(42, 4);
        color(14);
        cout << "Dice rolling: " << d << "   ";
        Beep(300 + i * 40, 60);
        Sleep(70);
    }

    gotoxy(42, 4);
    color(14);
    cout << "Dice result : " << d << "   ";
    resetColor();

    if (d == 6)
    {
        sixSound();
    }

    return d;
}

void moveSound()
{
    Beep(800, 100);
}

void captureSound()
{
    Beep(200, 400);
}

void sixSound()
{
    Beep(1000, 150);
    Beep(1200, 150);
}

void winSound()
{
    Beep(523, 300);
    Beep(659, 300);
    Beep(784, 300);
    Beep(1046, 400);
}