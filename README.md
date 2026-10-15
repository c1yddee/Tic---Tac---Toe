# Tic Tac Toe

A command-line Tic Tac Toe game where you play against a computer opponent.

## Features

- **Human vs Computer gameplay** – Challenge an AI opponent
- **Input validation** – Prevents invalid moves and handles user errors gracefully
- **Win detection** – Automatically detects wins via rows, columns, and diagonals
- **Replay functionality** – Play multiple games in succession without restarting
- **Randomized computer moves** – Computer plays random valid moves

## Requirements

- C++ compiler (g++, clang, or equivalent)
- C++11 or later

## Compilation

Compile using any standard C++ compiler:

```bash
g++ -o tictactoe tictactoe.cpp
```

Or with a custom seed for reproducible random moves:

```bash
g++ -o tictactoe tictactoe.cpp
```

## How to Run

Run the compiled program:

```bash
./tictactoe
```

Or provide a seed for reproducible random computer moves:

```bash
./tictactoe 12345
```

## How to Play

1. The game displays an empty 3×3 board
2. When prompted, enter your move as two integers (x, y) where:
   - `x` is the column (0-2, left to right)
   - `y` is the row (0-2, top to bottom)
3. You play as **X**, the computer plays as **O**
4. First to get three in a row (horizontally, vertically, or diagonally) wins
5. If all spaces fill with no winner, it's a tie (Cat's Game)
6. After each game, choose whether to play again

### Example Move
```
Please enter a position to play (x, y)
1 1
```
This places your X at the center of the board.

## Board Layout

```
 | | 
---------
 | | 
---------
 | | 
```

Position reference (x, y):
```
(0,0) | (1,0) | (2,0)
------|-------|------
(0,1) | (1,1) | (2,1)
------|-------|------
(0,2) | (1,2) | (2,2)
```

## Project Structure

- `tictactoe.cpp` – Main game implementation
  - Board initialization and drawing
  - Move validation and placement
  - Win condition checking (rows, columns, diagonals)
  - Game loop and replay logic
  - Computer move generation

## Functions

| Function | Purpose |
|----------|---------|
| `main()` | Game loop and flow control |
| `drawBoard()` | Display the current board state |
| `clearBoard()` | Reset the board for a new game |
| `getHumanMove()` | Get and validate player input |
| `getComputerMove()` | Generate a random computer move |
| `checkWin()` | Check for win conditions |
| `checkRow/Column/Diagonal()` | Check specific win patterns |
| `placeSymbol()` | Place X or O on the board |
| `isOccupied()` | Verify a position is empty |
| `initializeSeed()` | Initialize random number generator |

## Author

**Clyde Vincent Gadia**  
Student ID: 2002635336  
Course: CS 135 1007 (Spring 2025)  
Assignment: Assignment 7

## Future Improvements

- Implement AI strategy (block opponent wins, seek winning moves)
- Add difficulty levels (random, medium, hard)
- GUI interface using a graphics library
- Game statistics tracking (wins/losses/ties)
- Undo move functionality

## Notes

- The computer makes random moves; it does not use strategic AI
- Provide a seed via command line for reproducible games
- Default seed is 10145 if none is provided
