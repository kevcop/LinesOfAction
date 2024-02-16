// Rules.cpp
#include "Rules.h"
#include <cstdlib>
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
    if (!isPathClear(board, startRow, startCol, endRow, endCol, player.getPieceType())) {
        return false;
    }

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

    // Ensure the ending position is valid for the move
    return isValidEndingPosition(board, endRow, endCol, player.getPieceType());
}



//bool Rules::isValidMove(const Board& board, const Player& player, int startRow, int startCol, int endRow, int endCol) {
//
//    // checking for valid positions
//    if (!board.isPositionValid(startRow, startCol) || !board.isPositionValid(endRow, endCol)) {
//        return false;
//    }
//
//    //check if the move is in a straight line (horizontally, vertically, or diagonally)
//    bool isStraightLine = (startRow == endRow) || (startCol == endCol) || (abs(startRow - endRow) == abs(startCol - endCol));
//    if (!isStraightLine) {
//        return false;
//    }
//
//    // Check if the path is clear
//    if (!isPathClear(board, startRow, startCol, endRow, endCol, player.getPieceType())) {
//        return false;
//    }
//
//    int piecesInLine = 0;
//    if (startRow == endRow) {
//        // Horizontal move
//        piecesInLine = countPiecesInLine(board, startRow, startCol, 'H');
//    }
//    else if (startCol == endCol) {
//        // Vertical move
//        piecesInLine = countPiecesInLine(board, startRow, startCol, 'V');
//    }
//    else if (abs(startRow - endRow) == abs(startCol - endCol)) {
//        // Diagonal move
//        piecesInLine = countDiagonalPieces(board, startRow, startCol);
//    }
//
//    int moveDistance = max(abs(startRow - endRow), abs(startCol - endCol));
//    if (moveDistance != piecesInLine) {
//        return false;
//    }
//
//    return isValidEndingPosition(board, endRow, endCol, player.getPieceType());
//}
//determining max amount of move 

// The new countPiecesInLine function with the updated parameters


// 
// 
// 
//int Rules::countPiecesInLine(const Board& board, int row, int col, char direction) {
//    int count = 0;
//    const int SIZE = 8;
//
//    if (direction == 'H') {
//        // Count horizontally
//        for (int i = 0; i < SIZE; ++i) {
//            if (board.getPieceAt(row, i) != '.') {
//                ++count;
//            }
//        }
//    }
//    else if (direction == 'V') {
//        // Count vertically
//        for (int i = 0; i < SIZE; ++i) {
//            if (board.getPieceAt(i, col) != '.') {
//                ++count;
//            }
//        }
//    }
//    else if (direction == 'D') { // Add diagonal counting logic
//       
//        int rowDirection = (endRow - startRow >= 0) ? 1 : -1;
//        int colDirection = (endCol - startCol >= 0) ? 1 : -1;
//        int currentRow = startRow + rowDirection;
//        int currentCol = startCol + colDirection;
//
//        while (currentRow != endRow || currentCol != endCol) {            DOES NOT WORK!
//            if (board.getPieceAt(currentRow, currentCol) != '.') {
//                count++;
//            }
//            currentRow += rowDirection;
//            currentCol += colDirection;
//        }
//    }
        
        
        
        
        // Add diagonal counting logic
        // Determine the direction of the diagonal
        //int endRow = row; // You need to calculate endRow based on the specific move
        //int endCol = col; // You need to calculate endCol based on the specific move
        //int rowDirection = (endRow - row >= 0) ? 1 : -1;
        //int colDirection = (endCol - col >= 0) ? 1 : -1;

        //// Loop to count pieces on the diagonal path from the starting position
        //// towards the ending position
        //int i = row + rowDirection, j = col + colDirection;
        //while ((i >= 0 && i < SIZE) && (j >= 0 && j < SIZE)) {
        //    if (board.getPieceAt(i, j) != '.') ++count;
        //    i += rowDirection;
        //    j += colDirection;
        //}
        // Adjust for the starting position being counted multiple times
        // The adjustment will depend on the specifics of how you implement the diagonal counting
        

        //// Count positive slope diagonal
        //for (int i = row, j = col; i < SIZE && j < SIZE; i++, j++) {
        //    if (board.getPieceAt(i, j) != '.') count++;
        //}
        //for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        //    if (board.getPieceAt(i, j) != '.') count++;
        //}
        //// Count negative slope diagonal
        //for (int i = row, j = col; i < SIZE && j >= 0; i++, j--) {
        //    if (board.getPieceAt(i, j) != '.') count++;
        //}
        //for (int i = row - 1, j = col + 1; i >= 0 && j < SIZE; i--, j++) {
        //    if (board.getPieceAt(i, j) != '.') count++;
        //}
        //count -= 2; // Adjust for the starting position being counted multiple times

//
//int Rules::countPiecesInLine(const Board& board, int row, int col, char direction) {
//    int count = 0;
//    const int SIZE = 8;
//
//    if (direction == 'H') {
//        // Count horizontally
//        for (int i = 0; i < SIZE; ++i) {
//            if (board.getPieceAt(row, i) != '.') {
//                ++count;
//            }
//        }
//    }
//    else if (direction == 'V') {
//        // Count vertically
//        for (int i = 0; i < SIZE; ++i) {
//            if (board.getPieceAt(i, col) != '.') {
//                ++count;
//            }
//        }
//    }
//    return count;
//}
//method for diagonal moves
// 
//int Rules::countDiagonalPieces(const Board& board, int row, int col) {
//    int count = 0; // Start counting from 0
//
//    // Loop to count pieces going up-right
//    for (int i = row + 1, j = col + 1; i < 8 && j < 8; ++i, ++j) {
//        if (board.getPieceAt(i, j) != '.') ++count;               **LATEST 
//    }
//
//    // Loop to count pieces going up-left
//    for (int i = row + 1, j = col - 1; i < 8 && j >= 0; ++i, --j) {
//        if (board.getPieceAt(i, j) != '.') ++count;
//    }
//
//    // Loop to count pieces going down-right
//    for (int i = row - 1, j = col + 1; i >= 0 && j < 8; --i, ++j) {
//        if (board.getPieceAt(i, j) != '.') ++count;
//    }
//
//    // Loop to count pieces going down-left
//    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j) {
//        if (board.getPieceAt(i, j) != '.') ++count;
//    }
//
//    // Ensure not to double-count the starting piece itself, adjust based on how you count
//    return count;
//}

//int Rules::countDiagonalPieces(const Board& board, int row, int col) {
    //int count = 0;
    //const int SIZE = 8; // Assuming an 8x8 board

    //// Count positive slope diagonal pieces
    //for (int i = row, j = col; i < SIZE && j < SIZE; ++i, ++j) {
    //    if (board.getPieceAt(i, j) != '.') ++count;
    //}
    //for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j) {
    //    if (board.getPieceAt(i, j) != '.') ++count;
    //}

    //// Count negative slope diagonal pieces
    //for (int i = row, j = col; i >= 0 && j < SIZE; --i, ++j) {
    //    if (board.getPieceAt(i, j) != '.') ++count;
    //}
    //for (int i = row + 1, j = col - 1; i < SIZE && j >= 0; ++i, --j) {
    //    if (board.getPieceAt(i, j) != '.') ++count;
    //}
    //int count = 0; // Start counting from 0
    //// Loop to count pieces going up-right. Starts from the current position and goes up to the top-right corner of the board.
    //for (int i = row, j = col; i < 8 && j < 8; ++i, ++j) {
    //    if (board.getPieceAt(i, j) != '.') {
    //        ++count;
    //    }
    //}
    //// Subtract one to not double-count the starting piece itself
    //return count;
    //return count - 1;//-3 for starting position, ** FUNCTION NOT WORKING AS EXPECTED

//int Rules::countDiagonalPieces(const Board& board, int startRow, int startCol, int endRow, int endCol) {
//    int count = 0; // Start counting from 0
//
//    // Determine the direction of the diagonal
//    int rowDirection = (endRow - startRow >= 0) ? 1 : -1;
//    int colDirection = (endCol - startCol >= 0) ? 1 : -1;
//
//    // Loop to count pieces on the diagonal path from the starting position
//    // towards the ending position
//    int i = startRow + rowDirection, j = startCol + colDirection;
//    while (i != endRow || j != endCol) {
//        if (board.getPieceAt(i, j) != '.') {
//            count++;
//        }
//        i += rowDirection;
//        j += colDirection;
//    }
//
//    // No need to subtract 1 since we are not counting the starting square
//    return count;
//}

//LAST ATTEMPT

//int Rules::countDiagonalPieces(const Board& board, int startRow, int startCol) {
//    int count = 0;
//    const int SIZE = 8;
//
//    // Directions for diagonal movement
//    int directions[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
//
//    // Check all four diagonal directions from start position
//    for (int dir = 0; dir < 4; ++dir) {
//        int dRow = directions[dir][0];
//        int dCol = directions[dir][1];
//        int currentRow = startRow + dRow;
//        int currentCol = startCol + dCol;
//
//        while (currentRow >= 0 && currentRow < SIZE && currentCol >= 0 && currentCol < SIZE) {
//            if (board.getPieceAt(currentRow, currentCol) != '.') count++;
//            currentRow += dRow;
//            currentCol += dCol;
//        }
//    }
//
//    // Check if the start position itself should be counted
//    if (board.getPieceAt(startRow, startCol) != '.') count++;
//
//    return count;
//}

//Rules::DiagonalDirection Rules::determineDiagonalDirection(int startRow, int startCol, int endRow, int endCol) {
//    int rowDiff = endRow - startRow;
//    int colDiff = endCol - startCol;
//
//    if (rowDiff > 0 && colDiff > 0) {
//        std::cout << "Moving Northeast\n";
//        return DiagonalDirection::Northeast;
//    }
//    else if (rowDiff > 0 && colDiff < 0) {
//        std::cout << "Moving Northwest\n";
//        return DiagonalDirection::Northwest;
//    }
//    else if (rowDiff < 0 && colDiff > 0) {
//        std::cout << "Moving Southeast\n";
//        return DiagonalDirection::Southeast;
//    }
//    else if (rowDiff < 0 && colDiff < 0) {
//        std::cout << "Moving Southwest\n";
//        return DiagonalDirection::Southwest;
//    }
//    else {
//        std::cout << "Not a diagonal move\n";
//        return DiagonalDirection::None;
//    }
//}
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
    //int count = 1;
    //const int SIZE = 8;

    //if (direction == 'N') { // Handling only Northeast direction for now
    //    int currentRow = startRow + 1;
    //    int currentCol = startCol + 1;

    //    // Loop through the diagonal path in the northeast direction
    //    while (currentRow < SIZE && currentCol < SIZE) {
    //        if (board.getPieceAt(currentRow, currentCol) != '.') {
    //            count++;
    //        }
    //        currentRow++;
    //        currentCol++;
    //    }
    //}

    //return count;
}

//int Rules::countDiagonalPieces(const Board& board, int startRow, int startCol, char Direction) {
//    int count = 0;
//    const int SIZE = 8;
//
//    // Directions for diagonal movement
//    int directions[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
//
//    // Check all four diagonal directions from start position
//    for (int dir = 0; dir < 4; ++dir) {
//        int dRow = directions[dir][0];
//        int dCol = directions[dir][1];
//        int currentRow = startRow + dRow;
//        int currentCol = startCol + dCol;
//
//        while (currentRow >= 0 && currentRow < SIZE && currentCol >= 0 && currentCol < SIZE) {
//            if (board.getPieceAt(currentRow, currentCol) != '.') count++;
//            currentRow += dRow;
//            currentCol += dCol;
//        }
//    }
//
//    // Check if the start position itself should be counted
//    if (board.getPieceAt(startRow, startCol) != '.') count++;
//
//    return count;
//}


/*  Rules rulesInstance;
        Rules::DiagonalDirection dir = rulesInstance.determineDiagonalDirection(startRow, startCol, endRow, endCol);
        switch (dir) {
        case Rules::DiagonalDirection::Northeast:
            std::cout << "Direction: Northeast\n";
            // Additional logic for Northeast direction
            break;
        case Rules::DiagonalDirection::Northwest:
            std::cout << "Direction: Northwest\n";
            // Additional logic for Northwest direction
            break;
        case Rules::DiagonalDirection::Southeast:
            std::cout << "Direction: Southeast\n";
            // Additional logic for Southeast direction
            break;
        case Rules::DiagonalDirection::Southwest:
            std::cout << "Direction: Southwest\n";
            // Additional logic for Southwest direction
            break;
        case Rules::DiagonalDirection::None:
        default:
            std::cout << "Not a diagonal move or invalid direction\n";
            // Handle the case where it's not a diagonal move or invalid
            break;*/

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
