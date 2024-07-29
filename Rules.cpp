// Rules.cpp
#include "Rules.h"
#include <cstdlib>
#include <vector>
#include <utility>
using namespace std;
/**
 * Function Name: isPathClear
 * Purpose: Checks if the path between the start and end positions is clear of other pieces.
 * Parameters:
 *     board, a constant reference to a Board object representing the game board.
 *     startRow, startCol, endRow, endCol, integers representing the start and end positions.
 *     playerPieceType, a char representing the player's piece type.
 *     capturePositions, a reference to a vector of pair<int, int> for capturing opponent pieces.
 * Return Value: A boolean value indicating if the path is clear.
 * Algorithm:
 *     1. Calculate the direction of movement in rows and columns.
 *     2. Iterate from the start position towards the end position.
 *     3. Check if any piece other than the player's own blocks the path.
 *     4. Record valid capture positions if encountered.
 * Reference: Chatgpt
 */

bool Rules::isPathClear(const Board& board, int startRow, int startCol, int endRow, int endCol, char playerPieceType, vector<pair<int, int>>& capturePositions) {
    //determine movement direction
    // Determine the vertical direction of movement between the start and end positions.
// dRow is calculated as the difference between endRow and startRow, normalized to -1, 0, or 1.
// -1 indicates an upward movement on the board (towards lower row indices),
// 1 indicates a downward movement (towards higher row indices),
// and 0 indicates that the movement is purely horizontal (no change in row).
// The normalization is done by dividing the difference by its absolute value,
// ensuring that dRow captures only the direction, not the magnitude of the movement.
// The conditional check (endRow - startRow != 0) ensures division by zero is avoided,
// defaulting dRow to 0 when there's no vertical movement.
    int dRow = (endRow - startRow != 0) ? (endRow - startRow) / abs(endRow - startRow) : 0;
    // Determine the horizontal direction of movement between the start and end positions.
// dCol works similarly to dRow but for the horizontal axis.
// -1 indicates a leftward movement on the board (towards lower column indices),
// 1 indicates a rightward movement (towards higher column indices),
// and 0 indicates that the movement is purely vertical (no change in column).
// This calculation follows the same logic as dRow, standardizing the direction
// to -1, 0, or 1 based on whether the movement is to the left, none, or to the right,
// respectively, and avoids division by zero by checking if the difference is non-zero first.
    int dCol = (endCol - startCol != 0) ? (endCol - startCol) / abs(endCol - startCol) : 0;
    // `currentRow` is derived by adding `dRow` to `startRow`. `dRow` indicates the vertical
// direction of the movement (upward as -1, downward as 1, or stationary as 0).
// Therefore, `currentRow` is the next row position in the direction of the movement.
// This variable is crucial for stepwise traversal or checks along the path from the
// starting position to the destination, enabling iterative or recursive logic
// to move or check each step in the specified direction.
    int currentRow = startRow + dRow;
    // Similarly, `currentCol` is calculated by adding `dCol` to `startCol`, where `dCol`
// indicates the horizontal direction of the movement (leftward as -1, rightward as 1,
// or stationary as 0). Thus, `currentCol` identifies the next column position to
// consider in the movement's direction.
// Like `currentRow`, this variable allows for a systematic approach to navigate or
// evaluate each column step in the movement from the starting point towards the end.
    int currentCol = startCol + dCol;
    char pieceAtDestination = board.getPieceAt(endRow, endCol);

    //check each position along on the path
    while (currentRow != endRow || currentCol != endCol) {
        char pieceAtCurrent = board.getPieceAt(currentRow, currentCol);
        if (pieceAtCurrent != '.' && pieceAtCurrent != playerPieceType) {
            // Path is blocked
            return false;
        }
        currentRow += dRow;
        currentCol += dCol;
    }

    // Handle capturing at the destination
    if (pieceAtDestination != '.' && pieceAtDestination != playerPieceType) {
        // Valid capture at the destination
        capturePositions.push_back({ endRow, endCol });
        return true;
    }
    else if (pieceAtDestination == playerPieceType) {
        // Destination blocked by player's own piece
        return false;
    }
    //path is clear
    return true; 
}
/**
 * Function Name: checkWinCondition
 * Purpose: Determines if a win condition has been met.
 * Parameters:
 *     board, a constant reference to a Board object representing the game board.
 *     player, a constant reference to a Player object representing the player.
 * Return Value: A boolean value indicating if the player has won.
 * Algorithm:
 *     1. Placeholder function for win condition checking.
 * Reference: None
 */
bool Rules::checkWinCondition(const Board& board, const Player& player) {
    return false; 
}
/**
 * Function Name: isValidEndingPosition
 * Purpose: Checks if the ending position of a move is valid.
 * Parameters:
 *     board, a constant reference to a Board object representing the game board.
 *     endRow, endCol, integers representing the end position.
 *     pieceType, a char representing the player's piece type.
 * Return Value: A boolean value indicating if the ending position is valid.
 * Algorithm:
 *     1. Check if the ending position is empty or can be captured.
 * Reference: None
 */
bool Rules::isValidEndingPosition(const Board& board, int endRow, int endCol, char pieceType) {
    //get the piece at the end position
    char endPosPiece = board.getPieceAt(endRow, endCol);
    if (endPosPiece == '.') {
        //The ending position is empty
        return true;
    }
    // if the position holds opponent piece, capture is possible
    else if (endPosPiece != pieceType) {
        return true; 
    }
    //indicates move is not valid
    return false;
}

/**
 * Function Name: isValidMove
 * Purpose: Determines if a move is valid according to the game rules.
 * Parameters:
 *     board, a reference to a Board object representing the game board.
 *     player, a constant reference to a Player object representing the player making the move.
 *     startRow, startCol, endRow, endCol, integers representing the start and end positions of the move.
 * Return Value: A boolean value indicating if the move is valid.
 * Algorithm:
 *     1. Check if the starting piece belongs to the player and the move is within board bounds.
 *     2. Verify the move is in a straight line and the path is clear.
 *     3. Count pieces in line and compare to the move distance.
 * Reference: None
 */
bool Rules::isValidMove(Board& board, const Player& player, int startRow, int startCol, int endRow, int endCol) {
    //get the piece that is at the starting position
    char pieceAtStart = board.getPieceAt(startRow, startCol);

    //cout << "Debug: Piece at start [" << startRow << "," << startCol << "] is '" << pieceAtStart << "'." << endl;
    //cout << "Debug: Player's piece type is '" << player.getPieceType() << "'." << endl;
    //verify piece belongs to player and move is within bounds
    if (pieceAtStart == '.' || toupper(pieceAtStart) != toupper(player.getPieceType())) {
        cout << "Debug: No piece to move or piece does not belong to player." << endl;
        return false; 
    }

    // Check if the move is within board bounds and in a straight line
    if (!board.isPositionValid(startRow, startCol) || !board.isPositionValid(endRow, endCol)) {
        //cout << "Debug: Move is out of board bounds." << endl;
        return false;
    }
    //ensuring move is in a straight line
    bool isStraightLine = (startRow == endRow) || (startCol == endCol) || (abs(startRow - endRow) == abs(startCol - endCol));
    if (!isStraightLine) {
        //cout << "Debug: Move is not in a straight line." << endl;
        //invalid path
        return false;
    }

    // Ensure the path between start and end positions is clear
    vector<pair<int, int>> tempCaptures;
    if (!isPathClear(board, startRow, startCol, endRow, endCol, player.getPieceType(), tempCaptures)) {
        //cout << "Debug: Path is not clear for the move." << endl;
        return false;
    }
    //calculating the amount of pieces along the path
    int piecesInLine;
    //horizontal move checking
    if (startRow == endRow) {
        // Horizontal move
        piecesInLine = countPiecesInLine(board, startRow, startCol, 'H');
    }
    //vertical move checking
    else if (startCol == endCol) {
        // Vertical move
        piecesInLine = countPiecesInLine(board, startRow, startCol, 'V');
    }
    else {
        //diagonal move pieces in line determination
        char direction = determineDiagonalDirection(startRow, startCol, endRow, endCol);
        piecesInLine = countDiagonalPieces(board, startRow, startCol, direction);
    }
    //attempted distance of move
    int moveDistance = max(abs(startRow - endRow), abs(startCol - endCol));
    //cout << "Debug: Move Distance: " << moveDistance << ", Pieces in Line: " << piecesInLine << endl;
    //checking if desired move distance is equal to the amount of pieces along the line
    if (moveDistance != piecesInLine) {
        //cout << "Debug: Invalid move: Move distance does not match the total pieces in line." << endl;
        return false;
    }

    //checking for potential capturing 
    char pieceAtDestination = board.getPieceAt(endRow, endCol);
    if ((pieceAtDestination != '.' && pieceAtDestination != player.getPieceType() && moveDistance > piecesInLine) ||
        (pieceAtDestination == '.' && moveDistance != piecesInLine)) {
        //cout << "Debug: Conditions for capturing or non-capturing moves not met." << endl;
        return false;
    }

    return isValidEndingPosition(board, endRow, endCol, player.getPieceType());
}


/**
 * Function Name: determineDiagonalDirection
 * Purpose: Determines the direction of a diagonal move.
 * Parameters:
 *     startRow, startCol, endRow, endCol, integers representing the start and end positions of the move.
 * Return Value: A char representing the direction of the diagonal move.
 * Algorithm:
 *     1. Calculate the difference between start and end positions.
 *     2. Return a character representing the diagonal direction.
 * Reference: None
 */
char Rules::determineDiagonalDirection(int startRow, int startCol, int endRow, int endCol) {
    //calculating the difference between start and end positions for row and col
    int rowDiff = endRow - startRow;
    int colDiff = endCol - startCol;
    //identify diagonal direction based on the row and col
    if (rowDiff > 0 && colDiff > 0) {
        cout << "Moving Northeast\n";
        return 'N'; 
    }
    else if (rowDiff > 0 && colDiff < 0) {
        cout << "Moving Northwest\n";
        return 'W'; 
    }
    else if (rowDiff < 0 && colDiff > 0) {
        cout << "Moving Southeast\n";
        return 'E'; 
    }
    else if (rowDiff < 0 && colDiff < 0) {
        cout << "Moving Southwest\n";
        return 'S'; 
    }
    else {
        cout << "Not a diagonal move\n";
        return '0'; 
    }
}
/**
 * Function Name: countDiagonalPieces
 * Purpose: Counts the pieces on a diagonal line from a given position.
 * Parameters:
 *     board, a constant reference to a Board object representing the game board.
 *     startRow, startCol, integers representing the start position.
 *     direction, a char representing the direction of the diagonal.
 * Return Value: An integer representing the total count of pieces on the diagonal.
 * Algorithm:
 *     1. Count pieces in both positive and negative directions along the diagonal.
 * Reference: Chatgpt
 */
int Rules::countDiagonalPieces(const Board& board, int startRow, int startCol, char direction) {
    //wil be used to count amount of pieces
    int totalDiagonalCount = 0; 
    const int SIZE = 8;

    // Determine the direction increments for row and column based on the specified direction
    int dRow = (direction == 'N' || direction == 'E') ? 1 : -1;
    int dCol = (direction == 'E' || direction == 'W') ? 1 : -1;

    if (direction == 'W' || direction == 'E') { // Adjust for west and east directions
        dCol *= -1;
    }

    // Count pieces in the positive direction
    for (int i = 1; i < SIZE; i++) {
        int newRow = startRow + i * dRow;
        int newCol = startCol + i * dCol;
        if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE) {
            if (board.getPieceAt(newRow, newCol) != '.') {
                totalDiagonalCount++;
            }
        }
        else {
            //stop count if out of bounds
            break; 
        }
    }

    // Count pieces in the negative direction, excluding the starting piece itself
    for (int i = 1; i < SIZE; i++) {
        int newRow = startRow - i * dRow;
        int newCol = startCol - i * dCol;
        if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE) {
            if (board.getPieceAt(newRow, newCol) != '.') {
                totalDiagonalCount++;
            }
        }
        else {
            //stop count if out of bounds
            break; 
        }
    }

    //Include the starting piece in the total count
    return totalDiagonalCount + 1;
}

/**
 * Function Name: countPiecesInLine
 * Purpose: Counts the pieces in a straight line from a given position.
 * Parameters:
 *     board, a constant reference to a Board object representing the game board.
 *     startRow, startCol, integers representing the start position.
 *     direction, a char indicating the direction to count ('H' for horizontal, 'V' for vertical).
 * Return Value: An integer representing the total count of pieces in line.
 * Algorithm:
 *     1. Count pieces to the left/up and right/down from the start position.
 * Reference: None
 */
 int Rules::countPiecesInLine(const Board& board, int startRow, int startCol, char direction) {
     //used to keep track of count
     int count = 0; 
     //size of board
     const int SIZE = 8; 

     // Count left side of a horizontal move and up for a vertical move
     for (int d = -1; d >= -SIZE; --d) {
         int currentRow = startRow, currentCol = startCol;
         if (direction == 'H') currentCol += d;
         else if (direction == 'V') currentRow += d;

         if (currentRow < 0 || currentRow >= SIZE || currentCol < 0 || currentCol >= SIZE) break;
         if (board.getPieceAt(currentRow, currentCol) != '.') count++;
     }

     // Count right side of a horizontal move and down for a vertical move
     for (int d = 0; d < SIZE; ++d) {
         int currentRow = startRow, currentCol = startCol;
         if (direction == 'H') currentCol += d;
         else if (direction == 'V') currentRow += d;
         //break out of loop if current position is out of bounds
         if (currentRow < 0 || currentRow >= SIZE || currentCol < 0 || currentCol >= SIZE) break;
         //increment count if a piece is found
         if (board.getPieceAt(currentRow, currentCol) != '.') count++;
     }
     //cout << "Total pieces counted in line: " << count << endl;
     //return num of pieces counted
     return count;
 }
 /**
 * Function Name: processCaptures
 * Purpose: Processes the captures of opponent pieces on the board.
 * Parameters:
 *     board, a reference to a Board object where the captures will be processed.
 *     captures, a constant reference to a vector of pair<int, int> representing the positions of captured pieces.
 * Return Value: None
 * Algorithm:
 *     1. Remove each captured piece from the board.
 * Reference: None
 */
 void Rules::processCaptures(Board& board, const vector<pair<int, int>>& captures) {
     //iterate through captures and remove piece
     for (const auto& pos : captures) {
         board.removePiece(pos.first, pos.second);
     }
 }

