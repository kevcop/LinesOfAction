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
 * Reference: ChatGPT
 */

bool Rules::isPathClear(const Board& board, int startRow, int startCol, int endRow, int endCol, char playerPieceType, vector<pair<int, int>>& capturePositions) {
    // Calculate the direction increments for rows and columns
    int dRow = (endRow - startRow) != 0 ? (endRow - startRow) / abs(endRow - startRow) : 0;
    int dCol = (endCol - startCol) != 0 ? (endCol - startCol) / abs(endCol - startCol) : 0;

    // Initialize current position to the next step from the start
    int currentRow = startRow + dRow;
    int currentCol = startCol + dCol;
    char pieceAtDestination = board.getPieceAt(endRow, endCol);

    // Traverse the path from start to end position
    while (currentRow != endRow || currentCol != endCol) {
        char pieceAtCurrent = board.getPieceAt(currentRow, currentCol);
        if (pieceAtCurrent != '.' && pieceAtCurrent != playerPieceType) {
            return false; // Path is blocked by an opponent's piece
        }
        currentRow += dRow;
        currentCol += dCol;
    }

    // Check the piece at the destination
    if (pieceAtDestination != '.' && pieceAtDestination != playerPieceType) {
        capturePositions.push_back({ endRow, endCol });
        return true; // Path is clear, and an opponent's piece can be captured
    }
    else if (pieceAtDestination == playerPieceType) {
        return false; // Path is blocked by player's own piece
    }
    return true; // Path is clear
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
    char endPosPiece = board.getPieceAt(endRow, endCol);
    return endPosPiece == '.' || endPosPiece != pieceType;
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
    // Get the piece that is at the starting position
    char pieceAtStart = board.getPieceAt(startRow, startCol);

    // Verify piece belongs to player and move is within bounds
    if (pieceAtStart == '.' || toupper(pieceAtStart) != toupper(player.getPieceType())) {
        cout << "Debug: No piece to move or piece does not belong to player." << endl;
        return false;
    }

    // Check if the move is within board bounds and in a straight line
    if (!board.isPositionValid(startRow, startCol) || !board.isPositionValid(endRow, endCol)) {
        return false;
    }

    // Ensure the path between start and end positions is clear
    vector<pair<int, int>> tempCaptures;
    if (!isPathClear(board, startRow, startCol, endRow, endCol, player.getPieceType(), tempCaptures)) {
        return false;
    }

    // Calculate the number of pieces along the path
    int piecesInLine;
    if (startRow == endRow) {
        // Horizontal move
        piecesInLine = countPiecesInLine(board, startRow, startCol, 'H');
    }
    else if (startCol == endCol) {
        // Vertical move
        piecesInLine = countPiecesInLine(board, startRow, startCol, 'V');
    }
    else {
        // Diagonal move
        piecesInLine = countDiagonalPieces(board, startRow, startCol, endRow, endCol);
    }

    int moveDistance = max(abs(startRow - endRow), abs(startCol - endCol));
    if (moveDistance != piecesInLine) {
        cout << "Debug: Invalid move: Move distance does not match the total pieces in line." << endl;
        return false;
    }

    // Check for potential capturing 
    char pieceAtDestination = board.getPieceAt(endRow, endCol);
    if ((pieceAtDestination != '.' && pieceAtDestination != player.getPieceType() && moveDistance > piecesInLine) ||
        (pieceAtDestination == '.' && moveDistance != piecesInLine)) {
        cout << "Debug: Conditions for capturing or non-capturing moves not met." << endl;
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
    int rowDiff = endRow - startRow;
    int colDiff = endCol - startCol;

    // Identify diagonal direction based on the row and column differences
    if (rowDiff < 0 && colDiff > 0) {
        return 'N'; // Northeast
    }
    else if (rowDiff < 0 && colDiff < 0) {
        return 'W'; // Northwest
    }
    else if (rowDiff > 0 && colDiff > 0) {
        return 'E'; // Southeast
    }
    else if (rowDiff > 0 && colDiff < 0) {
        return 'S'; // Southwest
    }
    else {
        return '0'; // Not a diagonal move
    }
}

/**
 * Function Name: countDiagonalPieces
 * Purpose: Counts the pieces on a diagonal line from a given position.
 * Parameters:
 *     board, a constant reference to a Board object representing the game board.
 *     startRow, startCol, endRow, endCol, integers representing the start and end positions.
 * Return Value: An integer representing the total count of pieces on the diagonal.
 * Algorithm:
 *     1. Count pieces in both positive and negative directions along the diagonal.
 * Reference: ChatGPT
 */
int Rules::countDiagonalPieces(const Board& board, int startRow, int startCol, int endRow, int endCol) {
    int totalDiagonalCount = 0;
    const int SIZE = 8;

    // Determine the direction increments
    int dRow = (endRow > startRow) - (endRow < startRow);
    int dCol = (endCol > startCol) - (endCol < startCol);

    // Find the starting point of the diagonal
    int startRowDiagonal = startRow;
    int startColDiagonal = startCol;
    while (startRowDiagonal > 0 && startColDiagonal > 0) {
        startRowDiagonal--;
        startColDiagonal--;
    }
    while (startRowDiagonal < SIZE - 1 && startColDiagonal < SIZE - 1) {
        startRowDiagonal++;
        startColDiagonal++;
    }

    // Find the ending point of the diagonal
    int endRowDiagonal = startRow;
    int endColDiagonal = startCol;
    while (endRowDiagonal < SIZE - 1 && endColDiagonal < SIZE - 1) {
        endRowDiagonal++;
        endColDiagonal++;
    }
    while (endRowDiagonal > 0 && endColDiagonal > 0) {
        endRowDiagonal--;
        endColDiagonal--;
    }

    // Adjust based on the move direction
    if (dRow > 0 && dCol > 0) { // Bottom-left to top-right
        startRowDiagonal = startRow;
        startColDiagonal = startCol;
        while (startRowDiagonal > 0 && startColDiagonal > 0) {
            startRowDiagonal--;
            startColDiagonal--;
        }
        endRowDiagonal = startRow;
        endColDiagonal = startCol;
        while (endRowDiagonal < SIZE - 1 && endColDiagonal < SIZE - 1) {
            endRowDiagonal++;
            endColDiagonal++;
        }
    }
    else if (dRow > 0 && dCol < 0) { // Bottom-right to top-left
        startRowDiagonal = startRow;
        startColDiagonal = startCol;
        while (startRowDiagonal > 0 && startColDiagonal < SIZE - 1) {
            startRowDiagonal--;
            startColDiagonal++;
        }
        endRowDiagonal = startRow;
        endColDiagonal = startCol;
        while (endRowDiagonal < SIZE - 1 && endColDiagonal > 0) {
            endRowDiagonal++;
            endColDiagonal--;
        }
    }
    else if (dRow < 0 && dCol > 0) { // Top-left to bottom-right
        startRowDiagonal = startRow;
        startColDiagonal = startCol;
        while (startRowDiagonal < SIZE - 1 && startColDiagonal > 0) {
            startRowDiagonal++;
            startColDiagonal--;
        }
        endRowDiagonal = startRow;
        endColDiagonal = startCol;
        while (endRowDiagonal > 0 && endColDiagonal < SIZE - 1) {
            endRowDiagonal--;
            endColDiagonal++;
        }
    }
    else if (dRow < 0 && dCol < 0) { // Top-right to bottom-left
        startRowDiagonal = startRow;
        startColDiagonal = startCol;
        while (startRowDiagonal < SIZE - 1 && startColDiagonal < SIZE - 1) {
            startRowDiagonal++;
            startColDiagonal++;
        }
        endRowDiagonal = startRow;
        endColDiagonal = startCol;
        while (endRowDiagonal > 0 && endColDiagonal > 0) {
            endRowDiagonal--;
            endColDiagonal--;
        }
    }

    // Count pieces along the diagonal from start to end
    int currentRow = startRowDiagonal;
    int currentCol = startColDiagonal;

    while ((dRow > 0 && currentRow <= endRowDiagonal) || (dRow < 0 && currentRow >= endRowDiagonal) ||
        (dCol > 0 && currentCol <= endColDiagonal) || (dCol < 0 && currentCol >= endColDiagonal)) {
        if (board.getPieceAt(currentRow, currentCol) != '.') {
            totalDiagonalCount++;
        }
        currentRow += dRow;
        currentCol += dCol;
    }

    return totalDiagonalCount;
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
    int count = 0;
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

        if (currentRow < 0 || currentRow >= SIZE || currentCol < 0 || currentCol >= SIZE) break;
        if (board.getPieceAt(currentRow, currentCol) != '.') count++;
    }

    return count; // Include the starting piece
}

/**
 * Function Name: processCaptures
 * Purpose: Processes the captures of opponent pieces on the board.
 * Parameters:
 *     board, a reference to a Board object where the captures will be processed.
 *     captures, a constant reference to a vector of pair<int, int>> representing the positions of captured pieces.
 * Return Value: None
 * Algorithm:
 *     1. Remove each captured piece from the board.
 * Reference: None
 */
void Rules::processCaptures(Board& board, const vector<pair<int, int>>& captures) {
    // Iterate through captures and remove piece
    for (const auto& pos : captures) {
        board.removePiece(pos.first, pos.second);
    }
}
