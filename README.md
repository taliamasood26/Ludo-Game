# Ludo-Game
A console-based Ludo game in C++ featuring dice rolling, player turns, token movement, and complete game logic implementation.
# Ludo Game (C++ Console-Based)

A console-based Ludo game developed in C++ that simulates the classic board game experience. The game allows two players to compete by rolling dice, moving tokens across the board, capturing opponents' pieces, and racing to reach the home area first. It also supports saving and loading game progress.

## Features

* Two-player gameplay
* Random dice rolling
* Console-based board display
* Token movement according to Ludo rules
* Safe zones for token protection
* Token capturing system
* Home path and winning mechanism
* Save and load game progress
* Score tracking
* Menu-driven interface

## Technologies Used

* C++
* Standard Libraries: iostream, fstream, cstdlib, ctime
* Windows Console API

## Project Structure

```text
Ludo-Game/
│
├── Board.cpp
├── Board.h
├── Game.cpp
├── Game.h
├── FileIO.cpp
├── FileIO.h
├── Globals.cpp
├── Globals.h
├── Utils.cpp
├── Utils.h
│
└── main.cpp
```

## How to Run

Compile the project:

```bash
g++ *.cpp -o ludo
```

Run the executable:

```bash
./ludo
```

## Gameplay

* Roll the dice to move tokens.
* A token enters the board when the required roll is obtained.
* Players take turns moving their tokens.
* Landing on an opponent's token captures it and sends it back to the starting area.
* Safe cells protect tokens from capture.
* The first player to bring all tokens home wins the game.

## Learning Outcomes

* Object-Oriented Programming in C++
* File handling and data persistence
* Modular programming
* Game logic implementation
* Random number generation
* Use of arrays, structures, classes, and functions
* Console-based UI development
