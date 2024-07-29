/************************************************************
 * Name:  Kevin Chicas                                      *
 * Project:  Lines of Action - P1                           *
 * Class:  CMPS 369 - OPL                                   *
 * Date:  03/12/2024                                        *
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
    //loop through each row
    for (int i = 0; i < ROWS; ++i) {
        //loop through each column
        for (int j = 0; j < COLS; ++j) {
            // Initialize edges with black pieces, sides with white pieces, rest with empty spaces
            if ((i == 0 || i == ROWS - 1) && (j >= 1 && j <= 6)) {
                //black pieces
                board[i][j] = 'B'; 
            }
            else if ((j == 0 || j == COLS - 1) && (i >= 1 && i <= 6)) {
                //white pieces
                board[i][j] = 'W'; 
            }
            else {
                //empty spaces
                board[i][j] = '.'; 
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
    //primt column letters
    cout << "    ";
    for (char c = 'A'; c < 'A' + COLS; ++c) {
        cout << "  " << c;
    }
    cout << endl;
    //print board rows with boundaries and row numbers
    for (int i = ROWS - 1; i >= 0; --i) {
        //row boundary
        cout << "    +------------------------+" << endl;
        //row number
        cout << "  " << i + 1 << " |";
        for (int j = 0; j < COLS; ++j) {
            cout << " " << board[i][j] << " ";
        }
        //closing row boundary
        cout << "| " << i + 1 << endl;
    }
    //bottom boundary 
    cout << "    +------------------------+" << endl;
    cout << "    ";
    //print letter again 
    for (char c = 'A'; c < 'A' + COLS; ++c) {
        cout << "  " << c;
    }
    cout << endl;
}

/* *********************************************************************
Function Name: placePiece
Purpose: Determine if piece is being set to a location within the bounds of board
Parameters: row and col integers to specify location to check, char pieceType to verify that specific piece
Return Value: True or false boolean value
Algorithm:1) Validate row and column are within the bounds of the board 2) Check if the position listed is empty
3) If the position is valid and empty, return true indicating the piece can be placed there
4) Otherwise return false
Reference: none
********************************************************************* */
bool Board::placePiece(int row, int col, char pieceType) {
    // Validate the position and piece type
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && (pieceType == 'B' || pieceType == 'W')) {
        // Check if the position is empty
        if (board[row][col] == '.') {
            // Place the piece
            board[row][col] = pieceType; 
            // Successful placement
            return true; 
        }
    }
    // Invalid placement or position not empty
    return false; 
}

/* *********************************************************************
Function Name: movePiece
Purpose: To inidcate whether or not a piece can be moved
Parameters:
    startRow, an integer for the starting row.
    startCol, an integer for the starting column.
    endRow, an integer for the destination row.
    endCol, an integer for the destination column.
    player, a char representing the player's piece type ('B' or 'W').
Return Value: A boolean value, true if the move was executed successfully, false otherwise.
Algorithm:
    1. Validate the start and end positions are within board bounds and that the start position has the player's piece.
    2. Ensure the end position is either empty or contains an opponent's piece for capture.
    3. If valid, move the piece and return true.
    4. If invalid, return false.
Reference: none
********************************************************************* */
bool Board::movePiece(int startRow, int startCol, int endRow, int endCol, char player) {
    //determine the opponents piece 
    char opponent = (player == 'B') ? 'W' : 'B'; 
    // Validate the move
    if (startRow >= 0 && startRow < ROWS && startCol >= 0 && startCol < COLS &&
        endRow >= 0 && endRow < ROWS && endCol >= 0 && endCol < COLS &&
        board[startRow][startCol] == player && (board[endRow][endCol] == '.' || board[endRow][endCol] == opponent)) {
        // Execute the move
        //place piece at destination
        board[endRow][endCol] = player; // Place player's piece at destination (capturing if opponent's piece was there)
        //clear starting position
        board[startRow][startCol] = '.'; 
        //indicates move is successful
        return true; 
    }
    //indicates failure
    return false; 
}

/* *********************************************************************
Function Name: getPieceAt
Purpose: To retrieve the piece at a specified board position.
Parameters:
    row, an integer for the row.
    col, an integer for the column.
Return Value: A char representing the piece at the specified location or ' ' if the position is out of bounds.
Algorithm:
    1. Validate the specified position is within the bounds of the board.
    2. Return the piece at the position or ' ' if out of bounds.
Reference: none
********************************************************************* */
char Board::getPieceAt(int row, int col) const {
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
        return board[row][col];
    }
    //return empty space if out of bounds
    return ' '; 
}

/* *********************************************************************
Function Name: isPositionValid
Purpose: To check if a specified position is within the bounds of the board.
Parameters:
    row, an integer for the row.
    col, an integer for the column.
Return Value: A boolean value, true if the position is within bounds, false otherwise.
Algorithm:
    1. Return true if both row and column are within the 0 to ROWS-1 and 0 to COLS-1 range, respectively.
    2. Return false otherwise.
Reference: none
********************************************************************* */
bool Board::isPositionValid(int row, int col) const {
    //checks for correct board bounds
    return row >= 0 and row < ROWS && col >= 0 && col < COLS;
}

/* *********************************************************************
Function Name: removePiece
Purpose: To remove a piece from the board at a specified position.
Parameters:
    row, an integer for the row.
    col, an integer for the column.
Return Value: None
Algorithm:
    1. Set the board position specified by row and col to '.' (empty).
Reference: none
********************************************************************* */
void Board::removePiece(int row, int col) {
    //remove piece by setting it to '.' indicating an open space
    board[row][col] = '.';
}

/* *********************************************************************
Function Name: countPiecesByColor
Purpose: To count the number of black and white pieces currently on the board.
Parameters: None
Return Value: A pair of integers, the first for the count of black pieces, the second for the count of white pieces.
Algorithm:
    1. Initialize two counters for black and white pieces.
    2. Iterate over the entire board, incrementing the appropriate counter when a piece is encountered.
    3. Return the counts as a pair.
Reference: none
********************************************************************* */
pair<int, int> Board::countPiecesByColor() const {
    //variables to track count of pieces by color
    int blackCount = 0;
    int whiteCount = 0;
    //iterate through entire board
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (board[row][col] == 'B') {
                //increase count if black piece is encountered
                ++blackCount;
            }
            else if (board[row][col] == 'W') {
                //increase count if white piece is encountered
                ++whiteCount;
            }
        }
    }
    //return counts as a pair 
    return make_pair(blackCount, whiteCount);
}

/* *********************************************************************
Function Name: setPieceAt
Purpose: To set a piece of a specific type at a specified location on the board.
Parameters:
    row, an integer for the row.
    col, an integer for the column.
    pieceType, a char for the type of piece ('B', 'W', or '.').
Return Value: None
Algorithm:
    1. If the specified position is valid, set the board at that position to the specified pieceType.
Reference: none
********************************************************************* */
void Board::setPieceAt(int row, int col, char pieceType) {
    //validation check
    if (isPositionValid(row, col)) {
        //set piece at the location
        board[row][col] = pieceType;
    }
}

/* *********************************************************************
Function Name: clearBoard
Purpose: Clear the entire board by setting all positions to empty.
Parameters: None
Return Value: None
Algorithm:
    1. Loop through each row of the board from 0 to ROWS - 1.
    2. Inside each row, loop through each column from 0 to COLS - 1.
    3. Set the board position at [row][col] to '.', indicating an empty space.
Reference: None
********************************************************************* */
void Board::clearBoard() {
    //iterate through board
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            //set all positions to empty
            board[i][j] = '.'; 
        }
    }
}
