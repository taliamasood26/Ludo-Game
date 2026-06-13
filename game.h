#pragma once

int showMenu();
void getPlayerNames();
void newGame();
void gameLoop();
int selectToken(int p, int dice);
int canMove(int p, int t, int dice);
void moveToken(int p, int t, int dice);
void checkCapture(int p, int t);
int checkWin(int p);
