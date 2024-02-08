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
bool Board::placePiece(int row, int col, char pieceType) {
    // Validate the position and piece type
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && (pieceType == 'B' || pieceType == 'W')) {
        // Check if the position is empty
        if (board[row][col] == '.') {
            board[row][col] = pieceType; // Place the piece
            return true; // Placement successful
        }
    }
    return false; // Invalid position or not empty
}

bool Board::movePiece(int startRow, int startCol, int endRow, int endCol,char player) {
    // Validate positions and ensure the move is by the correct player
    if (startRow >= 0 && startRow < ROWS && startCol >= 0 && startCol < COLS &&
        endRow >= 0 && endRow < ROWS && endCol >= 0 && endCol < COLS &&
        board[startRow][startCol] == player && board[endRow][endCol] == '.') {

        // Make the move
        board[endRow][endCol] = player;
        board[startRow][startCol] = '.'; // Clear the starting position
        return true; // Move successful
    }
    return false; // Move failed
}
