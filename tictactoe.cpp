/*
Name: CLYDE VINCENT GADIA, 2002635336, CS 135 1007, SP 25 - Assignment 7
Description: Tic tac toe program which makes user play against computer
Input: User definded functions, loops, 2d dimensional arrays, passing
functions
Output: Display of tic tac toe game
*/

#include <iostream>
#include <iomanip>
#include <cstdlib> //For rand()
#include <time.h> //For seeding randomness
#include <unistd.h>

using namespace std;

//Constants
const int BOARD_DIM = 3; /// Width of the board.
const int TOTAL_SPACES = BOARD_DIM * BOARD_DIM; //Number of spaces on board 
const int DEFAULT_SEED = 10145; //Default seed for random number generation

//String constants
const string POSITION_MSG = "Please enter a position to play (x, y)";
const string HUMAN_WIN_MSG = "Human player wins!";
const string COM_WIN_MSG = "Computer wins!";
const string TIE_MSG = "Cat's Game!";
const string PLAY_AGAIN_MSG = "Play again?";
const string POS_ERR_MSG = "ERROR! Move enter an integer between 0 and " + to_string(BOARD_DIM - 1) + " inclusive";
const string NOT_EMPTY_MSG = "ERROR! That position is already filled. Please enter again.";
const string YN_ERR_MSG = "ERROR! Please enter (y)es or (n)o";

//Function prototypes

void initializeSeed(const int& arg_count, char** arg_vector);
void drawBoard(char board[BOARD_DIM][BOARD_DIM]);
void clearBoard(char board[BOARD_DIM][BOARD_DIM]);
char getYesOrNo();
int getInteger(int min, int max);
void getHumanMove(char board[BOARD_DIM][BOARD_DIM], int& x, int& y);
void getComputerMove(int&x, int& y, char board[BOARD_DIM][BOARD_DIM]);
bool isOccupied(char board[BOARD_DIM][BOARD_DIM], const int& x, const int& y);
bool checkDiagonalUpRight(char board[BOARD_DIM][BOARD_DIM]);
bool checkDiagonalDownLeft(char board[BOARD_DIM][BOARD_DIM]);
bool checkWin(char board[BOARD_DIM][BOARD_DIM]);
bool checkRow(char board[BOARD_DIM][BOARD_DIM]);
void placeSymbol(char board[BOARD_DIM][BOARD_DIM], int x, int y, char symbol);
bool checkColumn(char board[BOARD_DIM][BOARD_DIM]);

//TODO: For practice, please write prototypes for checkRow, checkColumn, and placeSymbol here

int main (int argc, char** argv) {
    char board[BOARD_DIM][BOARD_DIM]; //Create the board

    initializeSeed(argc, argv); //Seed for RNG

	//Variables 
    int xPos, yPos; //x and y positions
    int turnNumber; //Current turn number

    char playAgain;

    initializeSeed(argc, argv); //Seed for RNG

    do {
        clearBoard(board);        // Reset the board
        drawBoard(board);         // Show empty board
        turnNumber = 0;

        //Loop of the game
        while (turnNumber < TOTAL_SPACES) {
            //User turn
            cout << POSITION_MSG << endl; //User prompt for position
            getHumanMove(board, xPos, yPos); 
            placeSymbol(board, xPos, yPos, 'x'); //Places user position
            drawBoard(board); //Puts board after the user turns
            turnNumber++; //Increases count for turns

            //Checks if player wins game
            if (checkWin(board)) {
                cout << HUMAN_WIN_MSG << endl;
                break;
            }
            if (turnNumber == TOTAL_SPACES) break;

            //The computers turn
            cout << "\nComputer turn" << endl;
            getComputerMove(xPos, yPos, board);
            placeSymbol(board, xPos, yPos, 'o');
            drawBoard(board);
            turnNumber++;

            //Checks if cpu won game and displays win message
            if (checkWin(board)) {
                cout << COM_WIN_MSG << endl;
                break;
            }
        }

        //Checks if tie and displays tie message
        if (turnNumber == TOTAL_SPACES && !checkWin(board)) {
            cout << TIE_MSG << endl;
        }

        //Displays play again message and prompt
        cout << PLAY_AGAIN_MSG << " ";
        playAgain = getYesOrNo();

    //If user says no, game ends
    } while (playAgain == 'y');

    cout << endl << "See you later!" << endl;
    return 0;
}


//"Clears" the board by filling all elements with the space character
void clearBoard(char board[BOARD_DIM][BOARD_DIM])
{
    for (int i = 0; i < BOARD_DIM; ++i)
    for (int j = 0; j < BOARD_DIM; ++j)
        board[i][j] = ' ';   
}

//Prompt if player wants to play again and error checks the response
char getYesOrNo() {
    char response;
    cin >> response;
    while (response != 'y' && response != 'n') { //Loops until y or n
        cout << YN_ERR_MSG << endl;
        cin >> response;
    }
    return response;
}

//Gets a move from the user and checks if the space isn't occupied
void getHumanMove(char board[BOARD_DIM][BOARD_DIM], int& x, int& y) {
    do {
        x = getInteger(0, BOARD_DIM);
        y = getInteger(0, BOARD_DIM);
        if (isOccupied(board, x, y))
            cout << NOT_EMPTY_MSG << endl;
    } while (isOccupied(board, x, y));
}

//Checks row if they have the same symbols
bool checkRow(char board[BOARD_DIM][BOARD_DIM]) {
    for (int i = 0; i < BOARD_DIM; ++i) { //Go through each row
        char checkChar = board[i][0];
        if (checkChar == ' ') continue; //Skips row
        bool match = true;
        for (int j = 1; j < BOARD_DIM; ++j) {
            if (board[i][j] != checkChar) {
                match = false; //If no symbols in a row match
                break;
            }
        }
        if (match) return true; //If the symbols match, then win 
    }
    return false; //No win if no symbols match
}

//checks for win conditions
bool checkWin(char board[BOARD_DIM][BOARD_DIM]) {
    return checkRow(board) || checkColumn(board) ||
           checkDiagonalDownLeft(board) || checkDiagonalUpRight(board);
}


//Places x or o on the inputted x and y positions
void placeSymbol(char board[BOARD_DIM][BOARD_DIM], int x, int y, char symbol) {
    board[y][x] = symbol;
}

//Gets an integer from the user in the range [min, max) and returns it
int getInteger(int min, int max)
{
    int value;
    cin >> value; //Read int

    //Loop until value was successfully read in valid range
    while(cin.fail() || value < min || value >= max)
    {
        cout << POS_ERR_MSG << endl; //Print error message
        cin.clear(); //Clear fail state
        cin.ignore(1024, '\n'); //Ignore
        cin >> value; //Try to read again
    }

    return value;
}

//Checks if a player has won via the diagonal from bottom left to top right
bool checkDiagonalUpRight(char board[BOARD_DIM][BOARD_DIM])
{
    char checkChar = board[BOARD_DIM - 1][0]; //Get bottom left character
    if(checkChar == ' ') return false; //If not filled, diagonal is not a winner

    //Travel across diagonal. If any character does not match bottom left, diagonal is not a winner
    for(int i = 1; i < BOARD_DIM; i++)
        if(board[BOARD_DIM + i - 1][i] != checkChar) return false;

    return true; //If all matched, someone won via the diagonal!
}

//Checks if a player has won via the diagonal from top left to bottom right
bool checkDiagonalDownLeft(char board[BOARD_DIM][BOARD_DIM])
{
    char checkChar = board[0][0]; //Get top left character
    if(checkChar == ' ') return false; //If not filled, diagonal is not a winner

    //Travel across diagonal. If any character does not match top left, diagonal is not a winner
    for(int i = 1; i < BOARD_DIM; i++)
        if(board[i][i] != checkChar) return false;

    return true; //If all matched, someone won via the diagonal!
}

//Checks if a player has won from a column from top to bottom
bool checkColumn(char board[BOARD_DIM][BOARD_DIM]) {
    for (int j = 0; j < BOARD_DIM; j++) { //Goes through each column
        char checkChar = board[0][j]; //Gets top character
        if (checkChar == ' ') continue; //If not filled, then no win
        bool match = true;
        for (int i = 1; i < BOARD_DIM; i++) {
            if (board[i][j] != checkChar) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

//Indicates whether the given position is occupied with an 'x' or 'o'
bool isOccupied(char board[BOARD_DIM][BOARD_DIM], const int& x, const int& y)
{
    return board[y][x] != ' ';
}

//Gets a random move to play on the board. Sets x and y to be the coordinates of the move.
//Played move is guaranteed to be open for a play to be made.
//Assumes board is not completely full
void getComputerMove(int&x, int& y, char board[BOARD_DIM][BOARD_DIM])
{
    x = rand() % BOARD_DIM; //Get a random x
    y = rand() % BOARD_DIM; //Get a random y

    //Reroll until an empty space is found
    while (isOccupied(board, x, y))
    {
        x = rand() % BOARD_DIM;
        y = rand() % BOARD_DIM;
    }
}

// Prints the board to the screen
void drawBoard(char board[BOARD_DIM][BOARD_DIM]) {
    int h, w;
    for (h = 0; h < BOARD_DIM - 1; h++) {
        for (w = 0; w < BOARD_DIM - 1; w++)
            cout << board[h][w] << "|"; //Print each character and the board lines

        cout << board[h][w] << endl; //Print last character of row
        cout << setw(2*BOARD_DIM - 1) << setfill('-') << "" << endl;
    }

    //Print last row
    for (w = 0; w < BOARD_DIM - 1; w++)
        cout << board[h][w] << "|"; //Print each character and the board lines
    cout << board[h][w] << endl; //Print last character of row
}

//Initializes the seed for rng using the command line arguments.
void initializeSeed(const int& arg_count, char** arg_vector)
{
    //Read the seed from the command line or set default if none given
    switch(arg_count)
    {
        case 1: //If no arguments, use default seed
            srand(DEFAULT_SEED);
            break;
        case 2: //Else use command line argument as seed
            srand(stoi(arg_vector[1]));
            break;
        default: //If more arguments are used
            cout << "Error, program takes either 0 or 1 command line arguments. Usages:\n" <<
            "./a.out\n or ./a.out <seed>" << endl;
            exit(1);
    }
}