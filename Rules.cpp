// Rules.cpp
#include "Rules.h"
#include <cstdlib>
#include <vector>
#include <utility>
using namespace std;
//looking for a valid path
// 
// 
bool Rules::isPathClear(const Board& board, int startRow, int startCol, int endRow, int endCol, char playerPieceType, vector<pair<int, int>>& capturePositions) {
    int dRow = (endRow - startRow != 0) ? (endRow - startRow) / abs(endRow - startRow) : 0;
    int dCol = (endCol - startCol != 0) ? (endCol - startCol) / abs(endCol - startCol) : 0;

    int currentRow = startRow + dRow;
    int currentCol = startCol + dCol;

    while (currentRow != endRow || currentCol != endCol) {
        char pieceAtCurrent = board.getPieceAt(currentRow, currentCol);
        if (pieceAtCurrent != '.' && pieceAtCurrent != playerPieceType) {
            // Potential capture detected, add to capturePositions
            capturePositions.push_back(std::make_pair(currentRow, currentCol));
            // Continue checking the path in case of multiple captures
        }
        else if (pieceAtCurrent == playerPieceType) {
            // Path blocked by player's own piece
            return false;
        }
        currentRow += dRow;
        currentCol += dCol;
    }

    // Final position check for capturing
    char pieceAtDestination = board.getPieceAt(endRow, endCol);
    if (pieceAtDestination != '.' && pieceAtDestination != playerPieceType) {
        // Potential capture at the destination
        capturePositions.push_back(std::make_pair(endRow, endCol));
    }
    else if (pieceAtDestination == playerPieceType) {
        // Destination blocked by player's own piece
        return false;
    }

    return true; // Path is clear, captures are recorded
}

//  bool Rules::isPathClear(const Board& board, int startRow, int startCol, int endRow, int endCol, char playerPieceType) {
//    // Calculate direction of movement
//    int dRow = (endRow - startRow != 0) ? (endRow - startRow) / abs(endRow - startRow) : 0;
//    int dCol = (endCol - startCol != 0) ? (endCol - startCol) / abs(endCol - startCol) : 0;
//
//    int currentRow = startRow + dRow;
//    int currentCol = startCol + dCol;                     THIS WORKS WITHOUT THE CAPTURING!!!!!
//
//    // traversing path
//    while (currentRow != endRow || currentCol != endCol) {
//        if (board.getPieceAt(currentRow, currentCol) != '.' && board.getPieceAt(currentRow, currentCol) != playerPieceType) {
//            return false; // unclear path
//        }
//        currentRow += dRow;
//        currentCol += dCol;
//    }
//
//    return true; // path is clear
//}

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

bool Rules::isValidMove(Board& board, const Player& player, int startRow, int startCol, int endRow, int endCol) { //REMOVED CONST
    vector<pair<int, int>> tempCaptures;
    // Ensure start and end positions are within the board
    if (!board.isPositionValid(startRow, startCol) || !board.isPositionValid(endRow, endCol)) {
        return false;
    }

    // Ensure the move is in a straight line: horizontally, vertically, or diagonally
    bool isStraightLine = (startRow == endRow) || (startCol == endCol) || (abs(startRow - endRow) == abs(startCol - endCol));
    if (!isStraightLine) {
        return false;
    }

    // Ensure the path between start and end positions is clear
    if (!isPathClear(board, startRow, startCol, endRow, endCol, player.getPieceType(),tempCaptures)) {
        return false;
    }

    //processCaptures(board, tempCaptures);

    // Determine the number of pieces in line with the move
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
        char direction = determineDiagonalDirection(startRow, startCol, endRow, endCol);
        // Diagonal move
        // Adjust this to call the correct diagonal counting function, considering the move direction
        //piecesInLine = countPiecesInLine(board, startRow, startCol,'D');
         //piecesInLine = countPiecesInLine(board, startRow, startCol, endRow, endCol, 'D');
       // piecesInLine = countDiagonalPieces(board, startRow, startCol);
        piecesInLine = countDiagonalPieces(board,startRow,startCol,direction);

         //piecesInLine = countPiecesInLine(board, startRow,startCol, 'D');
        //piecesInLine++;
    }

    // Calculate the move distance
    int moveDistance = max(abs(startRow - endRow), abs(startCol - endCol));
    // Validate the move distance against the number of pieces in line
    if (moveDistance != piecesInLine) {
        return false;
    }
    if (!isValidEndingPosition(board, endRow, endCol, player.getPieceType())) {
        return false;
    }

    // Since all checks have passed, now we can process captures
    processCaptures(board, tempCaptures);

    return true;
    // Ensure the ending position is valid for the move
    //return isValidEndingPosition(board, endRow, endCol, player.getPieceType());
}
char Rules::determineDiagonalDirection(int startRow, int startCol, int endRow, int endCol) {
    int rowDiff = endRow - startRow;
    int colDiff = endCol - startCol;

    if (rowDiff > 0 && colDiff > 0) {
        std::cout << "Moving Northeast\n";
        return 'N'; // Northeast
    }
    else if (rowDiff > 0 && colDiff < 0) {
        std::cout << "Moving Northwest\n";
        return 'W'; // Northwest
    }
    else if (rowDiff < 0 && colDiff > 0) {
        std::cout << "Moving Southeast\n";
        return 'E'; // Southeast
    }
    else if (rowDiff < 0 && colDiff < 0) {
        std::cout << "Moving Southwest\n";
        return 'S'; // Southwest
    }
    else {
        std::cout << "Not a diagonal move\n";
        return '0'; // Invalid or not diagonal
    }
}


 int Rules::countDiagonalPieces(const Board& board, int startRow, int startCol, char direction) {

      int count = 1; // Include the starting piece
    const int SIZE = 8;

    // Depending on the direction, adjust the row and column changes
    int dRow = 0, dCol = 0;

    switch (direction) {
        case 'N': // Northeast
            dRow = 1;
            dCol = 1;
            break;
        case 'W': // Northwest
            dRow = 1;
            dCol = -1;
            break;
        case 'E': // Southeast
            dRow = -1;
            dCol = 1;
            break;
        case 'S': // Southwest
            dRow = -1;
            dCol = -1;
            break;
        default:
            // Invalid direction, you might want to handle this case.
            return 0;
    }

    // Start checking from the next cell in the specified direction
    int currentRow = startRow + dRow;
    int currentCol = startCol + dCol;

    // Loop through the diagonal path in the specified direction
    while (currentRow >= 0 && currentRow < SIZE && currentCol >= 0 && currentCol < SIZE) {
        if (board.getPieceAt(currentRow, currentCol) != '.') {
            count++;
        }
        currentRow += dRow;
        currentCol += dCol;
    }

    return count;
 }

 int Rules::countPiecesInLine(const Board& board, int startRow, int startCol, char direction) {
    int count = 1; // Start counting from the initial piece.
    const int SIZE = 8; // Assuming an 8x8 board.

    int dRow = 0, dCol = 0;
    switch (direction) {
    case 'H': // Horizontal
        dCol = (startCol < 7) ? 1 : -1; // Assuming moving right unless at the rightmost column
        break;
    case 'V': // Vertical
        dRow = (startRow < 7) ? 1 : -1; // Assuming moving down unless at the bottom row
        break;
        // Diagonal case is handled separately.
    }

    int currentRow = startRow + dRow;
    int currentCol = startCol + dCol;

    while (currentRow >= 0 && currentRow < SIZE && currentCol >= 0 && currentCol < SIZE) {
        char piece = board.getPieceAt(currentRow, currentCol);
        if (piece != '.') count++;
        currentRow += dRow;
        currentCol += dCol;
    }

    return count;
}
 void Rules::processCaptures(Board& board, const vector<pair<int, int>>& captures) {
     for (const auto& pos : captures) {
         board.removePiece(pos.first, pos.second);
     }
 }