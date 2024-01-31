#include "board.h"
#include <iostream>
using namespace std;
/* Constructor to initialize board 
   Calls another function,(can this be done without the need of another function?)*/
Board::Board() {
    createBoard();
}
/* Function to initialize board */
void Board::createBoard() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if ((i == 0 || i == ROWS - 1) && j >= 1 && j <= 6) {
                board[i][j] = 'B'; // Top and bottom rows, positions 1 to 6, black pieces
            }
            else if ((j == 0 || j == COLS - 1) && i >= 1 && i <= 6) {
                board[i][j] = 'W'; // Left and right columns, positions 1 to 6, red pieces
            }
            else {
                board[i][j] = '.'; // Use 'S' to represent empty spaces
            }
        }
    }
    //for (int i = 0; i < ROWS; i++)
    //{
    //    for (int j = 0; j < COLS; j++)
    //    {
    //        if (i==0 && j >=2 && j<=7)
    //        {
    //            board[i][j] = 'B';
    //        }
    //        else if (i == ROWS-1 && j>=2 && j<=7) {
    //            board[i][j] = 'B';
    //        }
    //        else if (j == 0 && i >= 2 && i <= 7) {
    //            board[i][j] = 'R';
    //        }
    //        else if (j == COLS - 1 && i >= 2 && i <= 7) {
    //            board[i][j] = 'R';
    //        }
    //        else {
    //            board[i][j] = 'S';
    //        }
    //        //board[i][j] = '*';
    //    }
    //}
}
/* Function to display board, perhaps include another function to display current board*/
void Board::showBoard() {
    cout << "    ";
    for (char c = 'A'; c <= 'H'; ++c) {
        cout << "  " << c;
    }
    cout << endl;

    for (int i = ROWS - 1; i >= 0; --i) {
        cout << "    +------------------------+" << endl;
        cout << "  " << i + 1 << " |";
        for (int j = 0; j < COLS; ++j) {
            cout << " " << (board[i][j] == 'S' ? '.' : board[i][j]) << " ";
        }
        cout << "| " << i + 1 << endl;
    }
    cout << "    +------------------------+" << endl;
    cout << "    ";
    for (char c = 'A'; c <= 'H'; ++c) {
        cout << "  " << c;
    }
    cout << endl;
    //for (int i = 0; i < ROWS; i++)
    //{
    //    for (int j = 0; j < COLS; j++)
    //    {
    //        //cout << (board[i][j] == ' ' ? "  " : board[i][j] + " ");
    //        cout << board[i][j] << " ";
    //    }
    //    cout << endl;

    //}
    //hello world git works now
    //test2
}