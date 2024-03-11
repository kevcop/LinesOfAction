#include "ComputerPlayer.h"
#include <iostream>
#include "Rules.h"
#include <string>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <map>
using namespace std; 

// Global or within a namespace to ensure it's accessible where needed
map<int, char> indexToCol = {
    {0, 'A'}, {1, 'B'}, {2, 'C'}, {3, 'D'},
    {4, 'E'}, {5, 'F'}, {6, 'G'}, {7, 'H'}
};

ComputerPlayer::ComputerPlayer(const string& name) : Player(name) {}

void ComputerPlayer::askPlayer() {
    //getting computer name but it is not needed DELETE MAYBE
    playerName = "AI" + playerName; 
}

//choose piece
void ComputerPlayer::selectPiece(char row, int col) {
    piece = make_pair(row, col); 
}
//choose destination
void ComputerPlayer::setDestination(char row, int col) {
    destination =   make_pair(row, col); 
}
// return piece selected
  pair<char, int> ComputerPlayer::getSelectedPiece() const {
    return piece;
}
  // return destination
  pair<char, int> ComputerPlayer::getDestination() const {
    return destination;
}
  // trying to mimic chess notation
//  string ComputerPlayer::properNotation(std::pair<int, int> position) const {
//    return std::string(1, static_cast<char>('A' + position.first)) + std::to_string(position.second + 1);
//}

  std::string ComputerPlayer::properNotation(std::pair<int, int> position) const {
      // Ensure that column conversion uses indexToCol for consistency
      char columnLetter = indexToCol[position.second]; // Converts column index back to letter
      int rowNumber = position.first + 1; // Adjust row number for 1-based indexing

      return std::string(1, columnLetter) + std::to_string(rowNumber);
  }


  //void ComputerPlayer::generateAllPossibleMoves(Board& board) {
  //    possibleMoves.clear();
  //    std::cout << "Generating moves for piece type: " << this->getPieceType() << std::endl;

  //    for (int fromRow = 0; fromRow < 8; ++fromRow) {
  //        for (int fromCol = 0; fromCol < 8; ++fromCol) {
  //            char piece = board.getPieceAt(fromRow, fromCol);
  //            // Verify if the piece at the current position belongs to the computer player
  //            if (piece == this->getPieceType()) {
  //                std::string fromNotation = char('A' + fromCol) + std::to_string(fromRow + 1);
  //                std::cout << "Computer piece found at: " << fromNotation << " with identifier: '" << piece << "'" << std::endl;

  //                // Calculate max moves required in horizontal and vertical directions
  //                int horizontalMovesRequired = rules.countPiecesInLine(board, fromRow, fromCol, 'H');
  //                int verticalMovesRequired = rules.countPiecesInLine(board, fromRow, fromCol, 'V');

  //                std::cout << "Max horizontal moves required: " << horizontalMovesRequired << std::endl;
  //                std::cout << "Max vertical moves required: " << verticalMovesRequired << std::endl;


  //                // Generating horizontal moves (if applicable)
  //                if (horizontalMovesRequired > 0) {
  //                    for (int dCol = -horizontalMovesRequired; dCol <= horizontalMovesRequired; ++dCol) {
  //                        if (dCol == 0) continue; // Skip no move
  //                        int toCol = fromCol + dCol;
  //                        if (!board.isPositionValid(fromRow, toCol)) continue;
  //                        std::string toNotation = char('A' + toCol) + std::to_string(fromRow + 1);

  //                        // Validate the horizontal move
  //                        if (rules.isValidMove(board, *this, fromRow, fromCol, fromRow, toCol)) {
  //                            std::string moveNotation = fromNotation + ":" + toNotation;
  //                            std::cout << "Adding to moves: From Row: " << fromRow << ", From Col: " << fromCol << " To Col: " << toCol << std::endl;
  //                            possibleMoves.push_back({ {fromRow, fromCol}, {fromRow, toCol} });
  //                            std::cout << "Adding valid move: " << moveNotation << std::endl;

  //                            std::cout << "Move added: " << moveNotation << ". Current Possible Moves:" << std::endl;
  //                            for (const auto& move : possibleMoves) {
  //                                auto start = move.first;
  //                                auto end = move.second;
  //                                std::string startNotation = properNotation(start);
  //                                std::string endNotation = properNotation(end);
  //                                cout << "WE are adding here!" << endl;
  //                                std::cout << startNotation << " to " << endNotation << std::endl;
  //                            }
  //                        }

  //                        }
  //                    }
  //                
  //      
  //                

  //                // Generating vertical moves (if applicable)
  //                if (verticalMovesRequired > 0) {
  //                    for (int dRow = -verticalMovesRequired; dRow <= verticalMovesRequired; ++dRow) {
  //                        if (dRow == 0) continue; // Skip no move
  //                        int toRow = fromRow + dRow;
  //                        if (!board.isPositionValid(toRow, fromCol)) continue;
  //                        std::string toNotation = char('A' + fromCol) + std::to_string(toRow + 1);

  //                        // Validate the vertical move
  //                        if (rules.isValidMove(board, *this, fromRow, fromCol, toRow, fromCol)) {
  //                            std::string moveNotation = fromNotation + ":" + toNotation;
  //                            possibleMoves.push_back({ {fromRow, fromCol}, {toRow, fromCol} });
  //                            std::cout << "Adding valid move: " << moveNotation << std::endl;
  //                        }
  //                    }
  //                }
  //            }
  //        }
  //    }
  //}


  //WORKS IN GENERATING MOVES BUT CAPTURES INVALID
  //void ComputerPlayer::generateAllPossibleMoves(Board& board) {
  //    possibleMoves.clear();
  //    std::cout << "Generating moves for piece type: " << this->getPieceType() << "\n";

  //    for (int fromRow = 0; fromRow < 8; ++fromRow) {
  //        for (int fromCol = 0; fromCol < 8; ++fromCol) {
  //            char piece = board.getPieceAt(fromRow, fromCol);
  //            if (piece == this->getPieceType()) {
  //                std::string fromNotation = char('A' + fromCol) + std::to_string(fromRow + 1);
  //                std::cout << "\nComputer piece found at: " << fromNotation << " with identifier: '" << piece << "'\n";

  //                int horizontalMovesRequired = rules.countPiecesInLine(board, fromRow, fromCol, 'H');
  //                int verticalMovesRequired = rules.countPiecesInLine(board, fromRow, fromCol, 'V');
  //                std::cout << "Max horizontal moves required: " << horizontalMovesRequired << "\n";
  //                std::cout << "Max vertical moves required: " << verticalMovesRequired << "\n";

  //                // Generating and validating horizontal moves
  //                if (horizontalMovesRequired > 0) {
  //                    for (int dCol = -horizontalMovesRequired; dCol <= horizontalMovesRequired; ++dCol) {
  //                        if (dCol == 0) continue; // Skip no move
  //                        int toCol = fromCol + dCol;
  //                        if (!board.isPositionValid(fromRow, toCol)) continue;
  //                        std::string toNotation = char('A' + toCol) + std::to_string(fromRow + 1);

  //                        if (rules.isValidMove(board, *this, fromRow, fromCol, fromRow, toCol)) {
  //                            std::cout << "Validating and adding move from " << fromNotation << " to " << toNotation << "\n";
  //                            cout << "from row being added: " << fromRow << "fromCol being added: " << fromCol<<"toCol being added:  "<<toCol;
  //                            displayPossibleMoves();
  //                            possibleMoves.push_back({ {fromRow, fromCol}, {fromRow, toCol} });

  //                        }
  //                    }
  //                }

  //                // Generating and validating vertical moves
  //                if (verticalMovesRequired > 0) {
  //                    for (int dRow = -verticalMovesRequired; dRow <= verticalMovesRequired; ++dRow) {
  //                        if (dRow == 0) continue; // Skip no move
  //                        int toRow = fromRow + dRow;
  //                        if (!board.isPositionValid(toRow, fromCol)) continue;
  //                        std::string toNotation = char('A' + fromCol) + std::to_string(toRow + 1);

  //                        if (rules.isValidMove(board, *this, fromRow, fromCol, toRow, fromCol)) {
  //                            std::cout << "Validating and adding move from " << fromNotation << " to " << toNotation << "\n";
  //                            possibleMoves.push_back({ {fromRow, fromCol}, {toRow, fromCol} });
  //                        }
  //                    }
  //                }
  //            }
  //        }
  //    }
  //    std::cout << "\nFinal Possible Moves:" << std::endl;
  //    for (const auto& move : possibleMoves) {
  //        auto start = move.first;

  //        cout << "Whats being added: ";
  //        cout << start.first;
  //        cout << start.second;
  //        auto end = move.second;
  //        cout << "Whats being added: ";
  //        cout << end.first;
  //        cout << end.second;
  //        std::string startNotation = properNotation({ start.first, start.second });
  //        std::string endNotation = properNotation({ end.first, end.second });
  //        std::cout << startNotation << " to " << endNotation << std::endl;
  //    }
  //}


  //LATEST WORKING
//void ComputerPlayer::generateAllPossibleMoves(Board& board) {
//    possibleMoves.clear();
//    std::cout << "Generating moves for piece type: " << this->getPieceType() << "\n";
//
//    for (int fromRow = 0; fromRow < 8; ++fromRow) {
//        for (int fromCol = 0; fromCol < 8; ++fromCol) {
//            char piece = board.getPieceAt(fromRow, fromCol);
//            if (piece == this->getPieceType()) {
//                std::string fromNotation = char('A' + fromCol) + std::to_string(fromRow + 1);
//                std::cout << "\nComputer piece found at: " << fromNotation << " with identifier: '" << piece << "'\n";
//
//                int horizontalMovesRequired = rules.countPiecesInLine(board, fromRow, fromCol, 'H');
//                int verticalMovesRequired = rules.countPiecesInLine(board, fromRow, fromCol, 'V');
//                std::cout << "Max horizontal moves required: " << horizontalMovesRequired << "\n";
//                std::cout << "Max vertical moves required: " << verticalMovesRequired << "\n";
//
//                // Generating and validating horizontal moves
//                for (int dCol = -horizontalMovesRequired; dCol <= horizontalMovesRequired; ++dCol) {
//                    if (dCol == 0) continue; // Skip no move
//                    int toCol = fromCol + dCol;
//                    if (!board.isPositionValid(fromRow, toCol)) continue;
//                    std::string toNotation = char('A' + toCol) + std::to_string(fromRow + 1);
//
//                    // Check for potential capturing move
//                    if (board.isOpponentPiece(fromRow, toCol, this->getPieceType())) {
//                        if (rules.isValidMove(board, *this, fromRow, fromCol, fromRow, toCol)) {
//                            std::cout << "Capturing move identified from " << fromNotation << " to " << toNotation << "\n";
//                            possibleMoves.push_back({ {fromRow, fromCol}, {fromRow, toCol} });
//                        }
//                    }
//                }
//
//                // Generating and validating vertical moves
//                for (int dRow = -verticalMovesRequired; dRow <= verticalMovesRequired; ++dRow) {
//                    if (dRow == 0) continue; // Skip no move
//                    int toRow = fromRow + dRow;
//                    if (!board.isPositionValid(toRow, fromCol)) continue;
//                    std::string toNotation = char('A' + fromCol) + std::to_string(toRow + 1);
//
//                    // Check for potential capturing move
//                    if (board.isOpponentPiece(toRow, fromCol, this->getPieceType())) {
//                        if (rules.isValidMove(board, *this, fromRow, fromCol, toRow, fromCol)) {
//                            std::cout << "Capturing move identified from " << fromNotation << " to " << toNotation << "\n";
//                            possibleMoves.push_back({ {fromRow, fromCol}, {toRow, fromCol} });
//                        }
//                    }
//                }
//            }
//        }
//    }
//    int fromRowTest = 1; // Example starting row, adjust as needed
//    int fromColTest = 0; // Example starting column, adjust as needed
//    int toRowTest = 1;   // Example destination row, adjust as needed
//    int toColTest = 2;   // Example destination column, adjust as needed
//    possibleMoves.push_back({ {fromRowTest, fromColTest}, {toRowTest, toColTest} });
//    std::cout << "\nFinal Possible Moves:" << std::endl;
//    for (const auto& move : possibleMoves) {
//        auto start = move.first;
//        cout << "      " << "\n";
//        cout << start.first;
//        cout << start.second;
//        auto end = move.second;
//        std::string startNotation = properNotation({ start.first, start.second });
//        std::string endNotation = properNotation({ end.first, end.second });
//        std::cout << startNotation << " to " << endNotation << std::endl;
//    }
//}

//void ComputerPlayer::generateAllPossibleMoves(Board& board) {
//    possibleMoves.clear();
//    std::cout << "Generating moves for piece type: " << this->getPieceType() << std::endl;
//
//    for (int fromRow = 0; fromRow < 8; ++fromRow) {
//        for (int fromCol = 0; fromCol < 8; ++fromCol) {
//            char piece = board.getPieceAt(fromRow, fromCol);
//            if (piece == this->getPieceType()) {
//                for (int dRow = -1; dRow <= 1; ++dRow) {
//                    for (int dCol = -1; dCol <= 1; ++dCol) {
//                        // Skip the current piece's position and diagonal moves for simplicity
//                        if ((dRow == 0 && dCol == 0) || (dRow != 0 && dCol != 0)) continue;
//
//                        int toRow = fromRow + dRow;
//                        int toCol = fromCol + dCol;
//
//                        // Ensure the move is within bounds and not capturing its own piece
//                        if (toRow >= 0 && toRow < 8 && toCol >= 0 && toCol < 8 && board.getPieceAt(toRow, toCol) != this->getPieceType()) {
//                            // Add move if it results in a valid position (empty or capturing an opponent's piece)
//                            if (board.getPieceAt(toRow, toCol) == '.' || board.isOpponentPiece(toRow, toCol, this->getPieceType())) {
//                                possibleMoves.push_back({ {fromRow, fromCol}, {toRow, toCol} });
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    // Debug output to list generated moves
//    for (const auto& move : possibleMoves) {
//        auto [from, to] = move;
//        std::string fromNotation = properNotation(from);
//        std::string toNotation = properNotation(to);
//        std::cout << "Generated move from " << fromNotation << " to " << toNotation << std::endl;
//    }

//}




  //std::pair<std::string, std::string> ComputerPlayer::selectAndExecuteMove(Board& board, char playerPieceType) {
  //    if (possibleMoves.empty()) {
  //        std::cout << "No possible moves to select from." << std::endl;
  //        return {};
  //    }

  //    // Randomly select a move
  //    int moveIndex = rand() % possibleMoves.size();
  //    auto selectedMove = possibleMoves[moveIndex];

  //    // Extract the start and end positions
  //    int startRow = selectedMove.first.first;
  //    int startCol = selectedMove.first.second;
  //    int endRow = selectedMove.second.first;
  //    int endCol = selectedMove.second.second;

  //    vector<pair<int, int>> capturePositions; // To hold positions of pieces captured during the move, if applicable

  //    // Convert indices to chess notation
  //    std::string startNotation = properNotation({ startRow, startCol });
  //    std::string endNotation = properNotation({ endRow, endCol });

  //    // Check if the move is valid using similar checks to those applied to human player moves
  //    if (rules.isValidMove(board, *this, startRow, startCol, endRow, endCol) &&
  //        rules.isPathClear(board, startRow, startCol, endRow, endCol, playerPieceType, capturePositions) &&
  //        rules.isValidEndingPosition(board, endRow, endCol, playerPieceType)) {

  //        // Execute the selected move using the Board class's movePiece method
  //        if (board.movePiece(startRow, startCol, endRow, endCol, playerPieceType)) {
  //            std::cout << "Move executed: " << startNotation << " to " << endNotation << std::endl;

  //            // Debug statement for captures
  //            if (!capturePositions.empty()) {
  //                std::cout << "Capture(s) triggered during the move:" << std::endl;
  //                for (auto& position : capturePositions) {
  //                    std::cout << "- Captured piece at " << properNotation(position) << std::endl;
  //                }
  //            }

  //            return { startNotation, endNotation }; // Return the move details for further processing if needed
  //        }
  //        else {
  //            std::cout << "Failed to execute move: " << startNotation << " to " << endNotation << std::endl;
  //            return {};
  //        }
  //    }
  //    else {
  //        std::cout << "AI selected an invalid move, attempting again." << std::endl;
  //        return selectAndExecuteMove(board, playerPieceType); // Recursively try another move if the selected one is invalid
  //    }
  //}
//LATEST WORKING
//std::pair<std::string, std::string> ComputerPlayer::selectAndExecuteMove(Board& board, char playerPieceType) {
//    if (possibleMoves.empty()) {
//        std::cout << "No possible moves to select from." << std::endl;
//        return {};
//    }
//
//    // Randomly select a move
//    int moveIndex = rand() % possibleMoves.size();
//    auto selectedMove = possibleMoves[moveIndex];
//
//    // Extract the start and end positions
//    int startRow = selectedMove.first.first;
//    int startCol = selectedMove.first.second;
//    int endRow = selectedMove.second.first;
//    int endCol = selectedMove.second.second;
//
//    vector<pair<int, int>> capturePositions; // To hold positions of pieces captured during the move, if applicable
//
//    // Convert indices to chess notation
//    std::string startNotation = properNotation({ startRow, startCol });
//    std::string endNotation = properNotation({ endRow, endCol });
//
//    // Before executing the move, check if it's valid including path clearance and ending position validity
//    if (rules.isValidMove(board, *this, startRow, startCol, endRow, endCol) &&
//        rules.isPathClear(board, startRow, startCol, endRow, endCol, playerPieceType, capturePositions) &&
//        rules.isValidEndingPosition(board, endRow, endCol, playerPieceType)) {
//        // Execute the move
//        if (board.movePiece(startRow, startCol, endRow, endCol, playerPieceType)) {
//            std::cout << "Move executed: " << startNotation << " to " << endNotation << std::endl;
//            // Now process captures after confirming the move is successful
//            rules.processCaptures(board, capturePositions);
//
//            // Debug statement for captures, if needed
//            // for (auto& position : capturePositions) {
//            //     std::cout << "- Captured piece at " << properNotation(position) << std::endl;
//            // }
//
//            return { startNotation, endNotation }; // Return the move details
//        }
//        else {
//            std::cout << "Failed to execute move: " << startNotation << " to " << endNotation << std::endl;
//            return {};
//        }
//    }
//    else {
//        std::cout << "AI selected an invalid move, attempting again." << std::endl;
//        return selectAndExecuteMove(board, playerPieceType); // Recursively try another move if the selected one is invalid
//    }
//}
// 
//WORKS NEWEST
//std::pair<std::string, std::string> ComputerPlayer::selectAndExecuteMove(Board& board, char playerPieceType) {
//    if (possibleMoves.empty()) {
//        std::cout << "No possible moves to select from." << std::endl;
//        return {};
//    }
//
//    //TESTING
//    //possibleMoves.clear();
//
//
//    // Randomly select a move from the list of possible moves
//    int moveIndex = rand() % possibleMoves.size();
//    const auto& selectedMove = possibleMoves[moveIndex]; // Use const reference to avoid copying
//
//    // Extract the start and end positions from the selected move
//    int startRow = selectedMove.start.first;
//    int startCol = selectedMove.start.second;
//    int endRow = selectedMove.end.first;
//    int endCol = selectedMove.end.second;
//    //TESTING PURPOSES
//    //int startRow = 2; // A3 is the third row (index 2)
//    //int startCol = 0; // A column
//    //int endRow = 2; // Still the third row for D3
//    //int endCol = 3;
//
//    vector<pair<int, int>> captures;
//    captures.push_back(make_pair(2, 1));
//    MoveDetails hardcodedMove{ {startRow, startCol}, {endRow, endCol}, captures };
//    possibleMoves.push_back(hardcodedMove);
//
//    const auto& selectedMove = possibleMoves[0]; // Directly use the hardcoded move
//
//    // Convert start and end positions to chess notation for output
//    std::string startNotation = properNotation({ startRow, startCol });
//    std::string endNotation = properNotation({ endRow, endCol });
//
//    // Attempt to execute the move
//    if (board.movePiece(startRow, startCol, endRow, endCol, playerPieceType)) {
//        std::cout << "Move executed: " << startNotation << " to " << endNotation << std::endl;
//
//        // If there are captured positions as part of this move, process them
//        if (!selectedMove.captures.empty()) {
//            rules.processCaptures(board, selectedMove.captures);
//
//            // Optionally, log the captures
//            for (const auto& capture : selectedMove.captures) {
//                std::cout << "Captured piece at " << properNotation(capture) << std::endl;
//            }
//        }
//
//        return { startNotation, endNotation }; // Return the move details for logging or further use
//    }
//    else {
//        std::cout << "Failed to execute move: " << startNotation << " to " << endNotation << std::endl;
//        return {}; // Return an empty pair to indicate failure
//    }
//}
std::pair<std::string, std::string> ComputerPlayer::selectAndExecuteMove(Board& board, char playerPieceType) {
    if (possibleMoves.empty()) {
        std::cout << "No possible moves to select from." << std::endl;
        return {};
    }

    // Randomly select a move from the list of possible moves
    srand(time(0)); // Ensure different random seed for each run
    int moveIndex = rand() % possibleMoves.size();
    const auto& selectedMove = possibleMoves[moveIndex]; // Use const reference to avoid copying

    // Extract the start and end positions from the selected move
    int startRow = selectedMove.start.first;
    int startCol = selectedMove.start.second;
    int endRow = selectedMove.end.first;
    int endCol = selectedMove.end.second;

    // Convert start and end positions to chess notation for output
    std::string startNotation = properNotation({ startRow, startCol });
    std::string endNotation = properNotation({ endRow, endCol });

    // Attempt to execute the move
    if (board.movePiece(startRow, startCol, endRow, endCol, playerPieceType)) {
        std::cout << "Move executed: " << startNotation << " to " << endNotation << std::endl;

        // If there are captured positions as part of this move, process them
        if (!selectedMove.captures.empty()) {
            // Optionally, log the captures
            for (const auto& capture : selectedMove.captures) {
                std::cout << "Captured piece at " << properNotation(capture) << std::endl;
            }
        }

        return { startNotation, endNotation }; // Return the move details for logging or further use
    }
    else {
        std::cout << "Failed to execute move: " << startNotation << " to " << endNotation << std::endl;
        return {}; // Return an empty pair to indicate failure
    }
}





//std::pair<std::string, std::string> ComputerPlayer::selectAndExecuteMove(Board& board, char playerPieceType) {
//    // Clear the possibleMoves vector and prepare for hardcoded moves
//    //possibleMoves.clear();
//
//    //int startRow, startCol, endRow, endCol;
//    //vector<pair<int, int>> captures; // Placeholder for captures of each move
//
//    //// Select the move based on the counter
//    //switch (moveCounter % 3) { // Use % 3 to cycle through the 3 moves
//    //case 0: // A3 to D3
//    //    startRow = 2; startCol = 0; endRow = 2; endCol = 3;
//    //    captures.push_back({ 2, 1 }); // Assuming capturing happens at D3
//    //    break;
//    //case 1: // D3 to A3
//    //    startRow = 2; startCol = 7; endRow = 2; endCol = 4;
//    //    captures.push_back({ 2, 2 }); // Assuming capturing happens at A3
//    //    break;
//    //case 2: // A3 to D3 again
//    //    startRow = 5; startCol = 0; endRow = 5; endCol = 3;
//    //    captures.push_back({ 2, 3 }); // Assuming capturing happens at D3
//    //    break;
//    //}
//
//    // Construct the move and add it to possibleMoves
//    MoveDetails move{ {startRow, startCol}, {endRow, endCol}, captures };
//    possibleMoves.push_back(move);
//
//    // Increment the counter for the next move
//    moveCounter++;
//
//    // Execute the hardcoded move
//    if (board.movePiece(startRow, startCol, endRow, endCol, playerPieceType)) {
//        // Convert the start and end positions to chess notation
//        std::string startNotation = properNotation({ startRow, startCol });
//        std::string endNotation = properNotation({ endRow, endCol });
//
//        std::cout << "Move executed: " << startNotation << " to " << endNotation << std::endl;
//
//        // Process any captures associated with the move
//        if (!captures.empty()) {
//            //rules.processCaptures(board, captures);
//            for (const auto& capture : captures) {
//                std::cout << "Captured piece at " << properNotation(capture) << std::endl;
//            }
//        }
//
//        return { startNotation, endNotation };
//    }
//    else {
//        std::cout << "Failed to execute move." << std::endl;
//        return {};
//    }
//}






void ComputerPlayer::displayPossibleMoves() const {
    std::cout << "Possible Moves:" << std::endl;
    for (const auto& moveDetails : possibleMoves) {
        auto start = moveDetails.start;
        auto end = moveDetails.end;
        std::string startNotation = properNotation(start);
        std::string endNotation = properNotation(end);
        std::cout << startNotation << " to " << endNotation;
        if (!moveDetails.captures.empty()) {
            std::cout << " with captures at: ";
            for (const auto& capture : moveDetails.captures) {
                std::cout << properNotation(capture) << " ";
            }
        }
        std::cout << std::endl;
    }
}





//LATEST WORKING
  //void ComputerPlayer::displayPossibleMoves() const {
  //    std::cout << "Possible Moves:" << std::endl;
  //    for (const auto& move : possibleMoves) {
  //        auto start = move.first;
  //        auto end = move.second;
  //        std::string startNotation = properNotation({ start.first, start.second });
  //        std::string endNotation = properNotation({ end.first, end.second });
  //        std::cout << startNotation << " to " << endNotation << std::endl;
  //    }
  //}
  std::string ComputerPlayer::revisedProperNotation(std::pair<int, int> position) const {
      // Convert the column index to a letter (A-H)
      char columnLetter = 'A' + position.second; // Assuming position.first is row, position.second is column

      // Convert the row index to a number (1-8), flipping the row index to match chess notation
      int rowNumber = 8 - position.first;

      return std::string(1, columnLetter) + std::to_string(rowNumber);
  }



  //void ComputerPlayer::selectAndExecuteMove(Board& board, char playerPieceType) {
  //    if (possibleMoves.empty()) {
  //        std::cout << "No possible moves to select from." << std::endl;
  //        return;
  //    }

  //    // Randomly select a move
  //    int moveIndex = rand() % possibleMoves.size(); // Generates a random index
  //    auto selectedMove = possibleMoves[moveIndex]; // Retrieves the move at the random index

  //    // Extract the start and end positions
  //    int startRow = selectedMove.first.first;
  //    int startCol = selectedMove.first.second;
  //    int endRow = selectedMove.second.first;
  //    int endCol = selectedMove.second.second;

  //    // Execute the selected move using the Board class's movePiece method
  //    if (board.movePiece(startRow, startCol, endRow, endCol, playerPieceType)) {
  //        std::cout << "Move executed: ";
  //    }
  //    else {
  //        std::cout << "Failed to execute move: ";
  //    }

  //    // Use properNotation for readable output
  //    std::string startNotation = revisedProperNotation({ startRow, startCol });
  //    std::string endNotation = revisedProperNotation({ endRow, endCol });
  //    std::cout << startNotation << " to " << endNotation << std::endl;
  //}

  //std::pair<std::string, std::string> ComputerPlayer::selectAndExecuteMove(Board& board, char playerPieceType) {
  //    if (possibleMoves.empty()) {
  //        std::cout << "No possible moves to select from." << std::endl;
  //        return {};
  //    }

  //    // Randomly select a move
  //    int moveIndex = rand() % possibleMoves.size();
  //    auto selectedMove = possibleMoves[moveIndex];

  //    // Extract the start and end positions
  //    int startRow = selectedMove.first.first;
  //    int startCol = selectedMove.first.second;
  //    int endRow = selectedMove.second.first;
  //    int endCol = selectedMove.second.second;

  //    // Convert indices to chess notation
  //    std::string startNotation = properNotation({ startRow, startCol });
  //    std::string endNotation = properNotation({ endRow, endCol });

  //    // Execute the selected move using the Board class's movePiece method
  //    if (board.movePiece(startRow, startCol, endRow, endCol, playerPieceType)) {
  //        std::cout << "Move executed: " << startNotation << " to " << endNotation << std::endl;
  //        return { startNotation, endNotation }; // Return the move details
  //    }
  //    else {
  //        std::cout << "Failed to execute move: " << startNotation << " to " << endNotation << std::endl;
  //        return {};
  //    }
  //}
  void ComputerPlayer::generateAllPossibleMoves( Board& board) {
      possibleMoves.clear();
      //std::cout << "Generating moves for piece type: " << this->getPieceType() << "\n";
      for (int fromRow = 0; fromRow < 8; ++fromRow) {
          for (int fromCol = 0; fromCol < 8; ++fromCol) {
              if (board.getPieceAt(fromRow, fromCol) == this->getPieceType()) {
                  // Horizontal moves
                  int horizontalMovesRequired = rules.countPiecesInLine(board, fromRow, fromCol, 'H');
                  for (int offset = 1; offset <= horizontalMovesRequired; ++offset) {
                      // Check moves to the right
                      addMoveIfValid(board, fromRow, fromCol, fromRow, fromCol + offset);
                      // Check moves to the left
                      addMoveIfValid(board, fromRow, fromCol, fromRow, fromCol - offset);
                  }
                  //cout << "BOARD AT THE END OF THE horizontal generate FUNCTION!\n";

                 // board.showBoard();


                  // Vertical moves
                  int verticalMovesRequired = rules.countPiecesInLine(board, fromRow, fromCol, 'V');
                  for (int offset = 1; offset <= verticalMovesRequired; ++offset) {
                      // Check moves down
                      addMoveIfValid(board, fromRow, fromCol, fromRow + offset, fromCol);
                      // Check moves up
                      addMoveIfValid(board, fromRow, fromCol, fromRow - offset, fromCol);
                  }
                  //board.showBoard();
                 // cout << "BOARD AT THE END OF THE vertical generate FUNCTION!\n";


              }
          }

          //displayPossibleMoves();
      }
  }

  /*void ComputerPlayer::addMoveIfValid( Board& board, int startRow, int startCol, int endRow, int endCol) {
      if (board.isPositionValid(endRow, endCol) && rules.isValidMove(board, *this, startRow, startCol, endRow, endCol)) {
          possibleMoves.push_back({ {startRow, startCol}, {endRow, endCol} });
      }
  }*/

  void ComputerPlayer::addMoveIfValid(Board& board, int startRow, int startCol, int endRow, int endCol) {
      std::vector<std::pair<int, int>> capturePositions; // Local capture positions
      if (board.isPositionValid(endRow, endCol) &&
          rules.isValidMove(board, *this, startRow, startCol, endRow, endCol) &&
          rules.isPathClear(board, startRow, startCol, endRow, endCol, this->getPieceType(), capturePositions) &&
          rules.isValidEndingPosition(board, endRow, endCol, this->getPieceType())) {

          MoveDetails move{ {startRow, startCol}, {endRow, endCol}, capturePositions };
          possibleMoves.push_back(move);
      }
  }

 