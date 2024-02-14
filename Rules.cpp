// Rules.cpp
#include "Rules.h"
//looking for a valid path
  bool Rules::isPathClear(const Board& board, int startRow, int startCol, int endRow, int endCol, char playerPieceType) {
    // Calculate direction of movement
    int dRow = (endRow - startRow != 0) ? (endRow - startRow) / abs(endRow - startRow) : 0;
    int dCol = (endCol - startCol != 0) ? (endCol - startCol) / abs(endCol - startCol) : 0;

    int currentRow = startRow + dRow;
    int currentCol = startCol + dCol;

    // traversing path
    while (currentRow != endRow || currentCol != endCol) {
        if (board.getPieceAt(currentRow, currentCol) != '.' && board.getPieceAt(currentRow, currentCol) != playerPieceType) {
            return false; // unclear path
        }
        currentRow += dRow;
        currentCol += dCol;
    }

    return true; // path is clear
}

bool Rules::checkWinCondition(const Board& board, const Player& player) {
    return false; 
}


//check for valid ending spot
bool Rules::isValidEndingPosition(const Board& board, int endRow, int endCol, char pieceType) {
    char endPosPiece = board.getPieceAt(endRow, endCol); // Assuming Board has a method getPieceAt to get the piece at a given position

    if (endPosPiece == '.') {
        //The ending position is empty
        return true;
    }
    else if (endPosPiece != pieceType) {
        return true; // capturing???
    }
    return false;
}
//determine if move is valid based off rules
bool Rules::isValidMove(const Board& board, const Player& player, int startRow, int startCol, int endRow, int endCol) {

    // checking for valid positions
    if (!board.isPositionValid(startRow, startCol) || !board.isPositionValid(endRow, endCol)) {
        return false;
    }

    //check if the move is in a straight line (horizontally, vertically, or diagonally)
    bool isStraightLine = (startRow == endRow) || (startCol == endCol) || (abs(startRow - endRow) == abs(startCol - endCol));
    if (!isStraightLine) {
        return false;
    }

    // Check if the path is clear
    if (!isPathClear(board, startRow, startCol, endRow, endCol, player.getPieceType())) {
        return false;
    }

    int piecesInLine = 0;
    if (startRow == endRow) {
        // Horizontal move
        piecesInLine = countPiecesInLine(board, startRow, startCol, 'H');
    }
    else if (startCol == endCol) {
        // Vertical move
        piecesInLine = countPiecesInLine(board, startRow, startCol, 'V');
    }
    else if (abs(startRow - endRow) == abs(startCol - endCol)) {
        // Diagonal move
        piecesInLine = countDiagonalPieces(board, startRow, startCol);
    }

    int moveDistance = max(abs(startRow - endRow), abs(startCol - endCol));
    if (moveDistance != piecesInLine) {
        return false;
    }

    return isValidEndingPosition(board, endRow, endCol, player.getPieceType());
}
//determining max amount of move 
int Rules::countPiecesInLine(const Board& board, int row, int col, char direction) {
    int count = 0;
    const int SIZE = 8;

    if (direction == 'H') {
        // Count horizontally
        for (int i = 0; i < SIZE; ++i) {
            if (board.getPieceAt(row, i) != '.') {
                ++count;
            }
        }
    }
    else if (direction == 'V') {
        // Count vertically
        for (int i = 0; i < SIZE; ++i) {
            if (board.getPieceAt(i, col) != '.') {
                ++count;
            }
        }
    }
    return count;
}
//method for diagonal moves
int Rules::countDiagonalPieces(const Board& board, int row, int col) {
    int count = 0;
    const int SIZE = 8; // Assuming an 8x8 board

    // Count positive slope diagonal pieces
    for (int i = row, j = col; i < SIZE && j < SIZE; ++i, ++j) {
        if (board.getPieceAt(i, j) != '.') ++count;
    }
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j) {
        if (board.getPieceAt(i, j) != '.') ++count;
    }

    // Count negative slope diagonal pieces
    for (int i = row, j = col; i >= 0 && j < SIZE; --i, ++j) {
        if (board.getPieceAt(i, j) != '.') ++count;
    }
    for (int i = row + 1, j = col - 1; i < SIZE && j >= 0; ++i, --j) {
        if (board.getPieceAt(i, j) != '.') ++count;
    }

    return count - 3;//-3 for starting position, ** FUNCTION NOT WORKING AS EXPECTED
}
