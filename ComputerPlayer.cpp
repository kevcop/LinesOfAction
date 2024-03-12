#include "ComputerPlayer.h"
#include <iostream>
#include "Rules.h"
#include <string>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <map>
using namespace std; 

// Global vafiable to map indexes
map<int, char> indexToCol = {
    {0, 'A'}, {1, 'B'}, {2, 'C'}, {3, 'D'},
    {4, 'E'}, {5, 'F'}, {6, 'G'}, {7, 'H'}
};
/**
 * Function Name: ComputerPlayer
 * Purpose: Constructor to create a ComputerPlayer object
 * Parameters:
 *     name, a string. The name of the computer player.
 * Return Value: None
 * Algorithm: Sets the playerName member variable to the given name.
 * Reference: None
 */

ComputerPlayer::ComputerPlayer(const string& name) : Player(name) {}
/**
 * Function Name: askPlayer
 * Purpose: Requests input from the computer player. Placeholder function for overriding.
 * Parameters: None
 * Return Value: None
 * Algorithm: Assigns a modified name with prefix "AI" to the computer player.
 * Reference: None
 */
    void ComputerPlayer::askPlayer() {
    //getting computer name but it is not needed DELETE MAYBE
    playerName = "AI" + playerName; 
}
/**
 * Function Name: selectPiece
 * Purpose: Selects a piece on the board.
 * Parameters:
 *     row, a char. The row of the piece to select.
 *     col, an int. The column of the piece to select.
 * Return Value: None
 * Algorithm: Assigns the selected piece's row and column to the piece member variable.
 * Reference: None
 */
    void ComputerPlayer::selectPiece(char row, int col) {
    //setting position
    piece = make_pair(row, col); 
}
/**
 * Function Name: setDestination
 * Purpose: Sets the destination for the selected piece.
 * Parameters:
 *     row, a char. The row of the destination.
 *     col, an int. The column of the destination.
 * Return Value: None
 * Algorithm: Assigns the destination's row and column to the 'destination' member variable.
 * Reference: None
 */
    void ComputerPlayer::setDestination(char row, int col) {
        //setting destination
    destination =   make_pair(row, col); 
}
/**
 * Function Name: getSelectedPiece
 * Purpose: Retrieves the selected piece.
 * Parameters: None
 * Return Value: The selected piece's position as a pair of row (char) and column (int).
 * Algorithm: Returns the 'piece' member variable.
 * Reference: None
 */
    pair<char, int> ComputerPlayer::getSelectedPiece() const {
        //returning selected piece
    return piece;
}
/**
 * Function Name: getDestination
 * Purpose: Retrieves the chosen destination for the selected piece.
 * Parameters: None
 * Return Value: The destination's position as a pair of row (char) and column (int).
 * Algorithm: Returns the 'destination' member variable.
 * Reference: None
 */
    pair<char, int> ComputerPlayer::getDestination() const {
        //return desired destination
    return destination;
}

    /**
 * Function Name: properNotation
 * Purpose: Converts a board position to chess-like notation.
 * Parameters:
 *     position, a pair<int, int>. The board position to convert.
 * Return Value: The position in chess notation as a string.
 * Algorithm: Uses the 'indexToCol' map to convert the column index to a letter and adjusts the row number for 1-based indexing.
 * Reference: None
 */
  string ComputerPlayer::properNotation(pair<int, int> position) const {
      // converting column index to letter and adjusting row for 1-based index
      char columnLetter = indexToCol[position.second]; 
      int rowNumber = position.first + 1; 
      //return results in string format
      return string(1, columnLetter) + to_string(rowNumber);
  }
  /**
   * Function Name: selectAndExecuteMove
   * Purpose: Selects and executes a move for the computer player.
   * Parameters:
   *     board, a Board object reference. The game board.
   *     playerPieceType, a char. The piece type ('B' or 'W') of the player.
   * Return Value: A pair of strings representing the start and end positions of the move in chess notation.
   * Algorithm: Randomly selects a move from the 'possibleMoves' vector, converts the start and end positions to chess notation, and attempts to execute the move on the board.
   * Reference: None
   */

pair<string, string> ComputerPlayer::selectAndExecuteMove(Board& board, char playerPieceType) {
    //conditional check for empty moves
    if (possibleMoves.empty()) {
        cout << "No possible moves to select from." << endl;
        return {};
    }

    // randomly select a move from the list of possible moves
    //generating random seed
    srand(time(0)); 
    //generate a random index based on size of vector
    int moveIndex = rand() % possibleMoves.size();
    //access random move
    const auto& selectedMove = possibleMoves[moveIndex]; 

    //extract the start and end positions from the selected move
    int startRow = selectedMove.start.first;
    int startCol = selectedMove.start.second;
    int endRow = selectedMove.end.first;
    int endCol = selectedMove.end.second;

    //convert start and end positions to chess notation for output
    string startNotation = properNotation({ startRow, startCol });
    string endNotation = properNotation({ endRow, endCol });

    // Attempt to execute the move
    if (board.movePiece(startRow, startCol, endRow, endCol, playerPieceType)) {
        cout << "Move executed: " << startNotation << " to " << endNotation << endl;

        // process potential captures
        if (!selectedMove.captures.empty()) {
            //attempt to log capture
            for (const auto& capture : selectedMove.captures) {
                cout << "Captured piece at " << properNotation(capture) << endl;
            }
        }
        //return move details 
        return { startNotation, endNotation }; // Return the move details for logging or further use
    }
    else {
        //indicate move failed
        cout << "Failed to execute move: " << startNotation << " to " << endNotation << endl;
        return {}; 
    }
}
/**
 * Function Name: displayPossibleMoves
 * Purpose: Displays all possible moves the computer player can make.
 * Parameters: None
 * Return Value: None
 * Algorithm: Iterates through the 'possibleMoves' vector, converting each move to chess notation and displaying it.
 * Reference: None
 */
void ComputerPlayer::displayPossibleMoves() const {
    //mainly used for debugging
    cout << "Possible Moves:" << endl;
    //iterate through possibleMoves vector to display moves
    for (const auto& moveDetails : possibleMoves) {
        auto start = moveDetails.start;
        auto end = moveDetails.end;
        string startNotation = properNotation(start);
        string endNotation = properNotation(end);
        cout << startNotation << " to " << endNotation;
        if (!moveDetails.captures.empty()) {
            cout << " with captures at: ";
            for (const auto& capture : moveDetails.captures) {
                cout << properNotation(capture) << " ";
            }
        }
        cout << endl;
    }
}
/**
 * Function Name: generateAllPossibleMoves
 * Purpose: Generates all valid moves for the computer player based on the current board state.
 * Parameters:
 *     board, a Board object reference. The game board to analyze.
 * Return Value: None
 * Algorithm:
 *     1. Clear the list of possible moves to start fresh.
 *     2. Iterate through each square of the board.
 *     3. If a square contains a piece belonging to the computer player, determine possible moves from that square:
 *        a. Calculate the number of horizontal moves required by counting pieces in the horizontal line.
 *        b. For each possible offset in the horizontal direction (both right and left), check if the move is valid and add it to possible moves.
 *        c. Calculate the number of vertical moves required by counting pieces in the vertical line.
 *        d. For each possible offset in the vertical direction (both up and down), check if the move is valid and add it to possible moves.
 * Reference: None
 */
  void ComputerPlayer::generateAllPossibleMoves( Board& board) {
      //clear vector each time
      possibleMoves.clear();
      //cout << "Generating moves for piece type: " << this->getPieceType() << "\n";
      //iterate through each position on the board to find possible moves
      for (int fromRow = 0; fromRow < 8; ++fromRow) {
          for (int fromCol = 0; fromCol < 8; ++fromCol) {
              //check if position has computer piece
              if (board.getPieceAt(fromRow, fromCol) == this->getPieceType()) {
                  //generating valid horizontal moves
                  int horizontalMovesRequired = rules.countPiecesInLine(board, fromRow, fromCol, 'H');
                  for (int offset = 1; offset <= horizontalMovesRequired; ++offset) {
                      //adding moves when moving right
                      addMoveIfValid(board, fromRow, fromCol, fromRow, fromCol + offset);
                      //adding moves when moving left
                      addMoveIfValid(board, fromRow, fromCol, fromRow, fromCol - offset);
                  }
                  //cout << "BOARD AT THE END OF THE horizontal generate FUNCTION!\n";

                 // board.showBoard();


                  // generating vertical moves
                  int verticalMovesRequired = rules.countPiecesInLine(board, fromRow, fromCol, 'V');
                  for (int offset = 1; offset <= verticalMovesRequired; ++offset) {
                      //add moves when moving down
                      addMoveIfValid(board, fromRow, fromCol, fromRow + offset, fromCol);
                      //add moves when moving up
                      addMoveIfValid(board, fromRow, fromCol, fromRow - offset, fromCol);
                  }
                  //board.showBoard();
                 // cout << "BOARD AT THE END OF THE vertical generate FUNCTION!\n";


              }
          }

          displayPossibleMoves();
      }
  }
  /**
  * Function Name: addMoveIfValid
  * Purpose: Adds a move to the 'possibleMoves' vector if it is valid according to the game rules.
  * Parameters:
  *     board, a Board object reference. The game board.
  *     startRow, startCol, endRow, endCol, integers. The starting and ending positions of the move.
  * Return Value: None
  * Algorithm:
  *     1. Initialize a vector to store any potential capture positions for this move.
  *     2. Validate the move based on several criteria:
  *        a. The end position must be within the board's valid range.
  *        b. The move must be valid according to the game's rules (e.g., the move follows the correct path and is not blocked).
  *        c. The path between the start and end positions must be clear of obstructions.
  *        d. The ending position must be a valid spot for the move to conclude.
  *     3. If the move passes all validations, create a MoveDetails object with the start and end positions, along with any capture positions.
  *     4. Add the MoveDetails object to the 'possibleMoves' vector for later execution.
  * Reference: None
  */
  void ComputerPlayer::addMoveIfValid(Board& board, int startRow, int startCol, int endRow, int endCol) {
      //creating vector to hold captures 
      vector<pair<int, int>> capturePositions; 
      //check if move is valid based on the rules class validations
      if (board.isPositionValid(endRow, endCol) &&
          rules.isValidMove(board, *this, startRow, startCol, endRow, endCol) &&
          rules.isPathClear(board, startRow, startCol, endRow, endCol, this->getPieceType(), capturePositions) &&
          rules.isValidEndingPosition(board, endRow, endCol, this->getPieceType())) {
          // Creates a MoveDetails object with starting position, ending position, and any capture positions
          MoveDetails move{ {startRow, startCol}, {endRow, endCol}, capturePositions };
          //add valid move to selection
          possibleMoves.push_back(move);
      }
  }

 