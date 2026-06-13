#include <iostream>
#include <fstream>
#include "globals.h"
#include "fileio.h"

using namespace std;

int saveFileExists()
{
    ifstream fin("savegame.dat", ios::binary);

    if (!fin)
    {
        return 0;
    }

    if (fin.peek() == EOF)
    {
        return 0;
    }

    return 1;
}

void saveGame()
{
    ofstream fout("savegame.dat", ios::binary);

    if (!fout)
    {
        cout << "Save file could not be opened." << endl;
        return;
    }

    fout.write((char*)playerName, sizeof(playerName));
    fout.write((char*)tokenPos, sizeof(tokenPos));
    fout.write((char*)&currentPlayer, sizeof(currentPlayer));
    fout.write((char*)score, sizeof(score));

    fout.close();

    cout << "Game saved in savegame.dat" << endl;
}

int loadGame()
{
    ifstream fin("savegame.dat", ios::binary);

    if (!fin)
    {
        return 0;
    }

    fin.read((char*)playerName, sizeof(playerName));
    fin.read((char*)tokenPos, sizeof(tokenPos));
    fin.read((char*)&currentPlayer, sizeof(currentPlayer));
    fin.read((char*)score, sizeof(score));

    if (!fin)
    {
        return 0;
    }

    fin.close();

    return 1;
}

void clearSave()
{
    ofstream fout("savegame.dat", ios::binary);
    fout.close();
}