#include "Board.h"
#include <iostream>

// Constructor initializes the board
Board::Board() {
    resetBoard();
}

// Reset or initialize the board
void Board::resetBoard() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            // Initialize edges with pieces, rest with empty spaces
            if ((i == 0 || i == ROWS - 1) && (j >= 1 && j <= 6)) {
                board[i][j] = 'B'; // Black pieces
            } else if ((j == 0 || j == COLS - 1) && (i >= 1 && i <= 6)) {
                board[i][j] = 'W'; // White pieces
            } else {
                board[i][j] = '.'; // Empty spaces
            }
        }
    }
}

// Display the board
void Board::showBoard() const {
    std::cout << "    ";
    for (char c = 'A'; c < 'A' + COLS; ++c) {
        std::cout << "  " << c;
    }
    std::cout << std::endl;

    for (int i = ROWS - 1; i >= 0; --i) {
        std::cout << "    +------------------------+" << std::endl;
        std::cout << "  " << i + 1 << " |";
        for (int j = 0; j < COLS; ++j) {
            std::cout << " " << board[i][j] << " ";
        }
        std::cout << "| " << i + 1 << std::endl;
    }
    std::cout << "    +------------------------+" << std::endl;
    std::cout << "    ";
    for (char c = 'A'; c < 'A' + COLS; ++c) {
        std::cout << "  " << c;
    }
    std::cout << std::endl;
}

//places piece is position is empty and valid
bool Board::placePiece(int row, int col, char pieceType) {
    //validate the position and piece type
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && (pieceType == 'B' || pieceType == 'W')) {
        //check if the position is empty
        if (board[row][col] == '.') {
            board[row][col] = pieceType; //place the piece
            return true; // successful
        }
    }
    return false;
}
//moves piece on the board if move is deemed valid 
bool Board::movePiece(int startRow, int startCol, int endRow, int endCol,char player) {
    // validation
    if (startRow >= 0 && startRow < ROWS && startCol >= 0 && startCol < COLS &&
        endRow >= 0 && endRow < ROWS && endCol >= 0 && endCol < COLS &&
        board[startRow][startCol] == player && board[endRow][endCol] == '.') {

        //actual movement
        board[endRow][endCol] = player;
        board[startRow][startCol] = '.'; // clear the starting position
        return true; // Move successful
    }
    return false; //invalid move
}
//retrieves piece from a location
char Board::getPieceAt(int row, int col) const {
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
        return board[row][col];
    }
    return ' '; //out of bounds
}

//validate if within board boundaries 
bool Board::isPositionValid(int row, int col) const {
    return row >= 0 and row < ROWS && col >= 0 && col < COLS;
}
