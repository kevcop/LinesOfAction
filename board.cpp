/************************************************************
 * Name:  Kevin Chicas                                      *
 * Project:  Lines of Action - P1                           *
 * Class:  CMPS 369 - OPL                                   *
 * Date:  03/13/2024                                        *
 ************************************************************/
#include "Board.h"
#include <iostream>

 // Constructor initializes the board to its starting state
Board::Board() {
    resetBoard();
}

/* *********************************************************************
Function Name: resetBoard
Purpose: Set board to its initial state 
Parameters: None
Return Value: None
Algorithm: 1) Nested loop used to iterate through columns within rows 
2) Add checks to see if on bottom or top edge which results in placing black pieces
3) Add checks to see if on left or right outermost column which results in placing white pieces
4) If on neither on desired locations then place a '.' indicating an empty space
Reference: none
********************************************************************* */
void Board::resetBoard() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            // Initialize edges with black pieces, sides with white pieces, rest with empty spaces
            if ((i == 0 || i == ROWS - 1) && (j >= 1 && j <= 6)) {
                board[i][j] = 'B'; // Black pieces
            }
            else if ((j == 0 || j == COLS - 1) && (i >= 1 && i <= 6)) {
                board[i][j] = 'W'; // White pieces
            }
            else {
                board[i][j] = '.'; // Empty spaces
            }
        }
    }
}

/* *********************************************************************
Function Name: showBoard
Purpose: Display board
Parameters: None
Return Value: None
Algorithm: 1) Print columns label (A-H) for the top row 2) For each row, assign label (1-8)
#) Print column labels (A-H) for the bottom row
Reference: none
********************************************************************* */
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

/* *********************************************************************
Function Name: placePiece
Purpose: Determine if piece is being set to a location within the bounds of board
Parameters: row and col integers to specify location to check, char pieceType to verify that specific piece
Return Value: True or false 
Algorithm:
Reference: none
********************************************************************* */
bool Board::placePiece(int row, int col, char pieceType) {
    // Validate the position and piece type
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && (pieceType == 'B' || pieceType == 'W')) {
        // Check if the position is empty
        if (board[row][col] == '.') {
            board[row][col] = pieceType; // Place the piece
            return true; // Successful placement
        }
    }
    return false; // Invalid placement or position not empty
}

/**
 * @brief Moves a piece on the board if the move is valid.
 * @param startRow The starting row of the piece to be moved.
 * @param startCol The starting column of the piece to be moved.
 * @param endRow The destination row for the piece.
 * @param endCol The destination column for the piece.
 * @param player The player ('B' or 'W') making the move.
 * @return True if the move was successful, false otherwise.
 */
bool Board::movePiece(int startRow, int startCol, int endRow, int endCol, char player) {
    char opponent = (player == 'B') ? 'W' : 'B'; // Determine the opponent's symbol
    // Validate the move
    if (startRow >= 0 && startRow < ROWS && startCol >= 0 && startCol < COLS &&
        endRow >= 0 && endRow < ROWS && endCol >= 0 && endCol < COLS &&
        board[startRow][startCol] == player && (board[endRow][endCol] == '.' || board[endRow][endCol] == opponent)) {
        // Execute the move
        board[endRow][endCol] = player; // Place player's piece at destination (capturing if opponent's piece was there)
        board[startRow][startCol] = '.'; // Clear the starting position
        return true; // Move successful
    }
    return false; // Invalid move
}

/**
 * @brief Retrieves the piece at a specified location.
 * @param row The row of the desired location.
 * @param col The column of the desired location.
 * @return The character representing the piece at the specified location or ' ' if out of bounds.
 */
char Board::getPieceAt(int row, int col) const {
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
        return board[row][col];
    }
    return ' '; // Return empty space if out of bounds
}

/**
 * @brief Checks if a given position is within the board boundaries.
 * @param row The row to check.
 * @param col The column to check.
 * @return True if the position is valid, false otherwise.
 */
bool Board::isPositionValid(int row, int col) const {
    return row >= 0 and row < ROWS && col >= 0 && col < COLS;
}

/**
 * @brief Removes a piece from the board at a specified location.
 * @param row The row of the piece to remove.
 * @param col The column of the piece to remove.
 */
void Board::removePiece(int row, int col) {
    board[row][col] = '.';
}

/**
 * @brief Counts the number of black and white pieces on the board.
 * @return A pair containing the count of black pieces first and white pieces second.
 */
std::pair<int, int> Board::countPiecesByColor() const {
    int blackCount = 0;
    int whiteCount = 0;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (board[row][col] == 'B') {
                ++blackCount;
            }
            else if (board[row][col] == 'W') {
                ++whiteCount;
            }
        }
    }

    return std::make_pair(blackCount, whiteCount);
}

/**
 * @brief Sets a piece at a specified location on the board.
 * @param row The row where the piece is to be placed.
 * @param col The column where the piece is to be placed.
 * @param pieceType The type of the piece ('B' for black, 'W' for white, or '.' for empty).
 */
void Board::setPieceAt(int row, int col, char pieceType) {
    if (isPositionValid(row, col)) {
        board[row][col] = pieceType;
    }
}

/**
 * @brief Clears the board, setting all positions to empty.
 */
void Board::clearBoard() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            board[i][j] = '.'; // Set all positions to empty
        }
    }
}
