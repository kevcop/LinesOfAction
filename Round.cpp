#include "Game.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "board.h"
#include "Round.h"
#include "Tournament.h"
#include "Serialization.h"
#include "Rules.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <map>
#include <vector>
using namespace std;
//used to keep track of moves
vector<string> moveLog;
//translate cols
map<char, int> colToIndex = {
{'A', 0}, {'B', 1}, {'C', 2}, {'D', 3},
{'E', 4}, {'F', 5}, {'G', 6}, {'H', 7}
};

Round::Round(shared_ptr<Player> p1, shared_ptr<Player> p2) : player1(p1), player2(p2), currentPlayer(nullptr), isPlayer1Turn(true), player1Score(0), player2Score(0), winner(nullptr) {
    //creating seed
    srand(static_cast<unsigned int>(time(nullptr))); 
    //reset board to initial state
    gameBoard.resetBoard(); 
}

/**
 * Function Name: coinToss
 * Purpose: Decides which player starts the game through a coin toss.
 * Parameters: None
 * Return Value: None
 * Algorithm:
 *     1. Prompt the user to choose heads (1) or tails (2).
 *     2. Generate a random number (1 or 2) representing the coin toss result.
 *     3. Compare the user's choice with the toss result to determine the starting player.
 *     4. Assign the piece types ('B' or 'W') to the players based on the coin toss outcome.
 * Reference: None
 */
void Round::coinToss() {
    cout << "Enter 1 for heads or 2 for tails.\n";
    //tracks the user choice for heads or tails
    int userChoice;
    cin >> userChoice;
    //gen rand num
    int toss = rand() % 2 + 1; 
    // assign first move
    if (userChoice == toss) {
        currentPlayer = player1;
        cout << "Player " << player1->getName() << " wins the coin toss and will go first.\n";
        player1->setPieceType('B');
        player2->setPieceType('W');
    }
    else {
        currentPlayer = player2;
        cout << "Player " << player2->getName() << " wins the coin toss and will go first.\n";
        player2->setPieceType('B');
        player1->setPieceType('W');
    }
}
/**
 * Function Name: switchTurn
 * Purpose: Switches the turn between the two players.
 * Parameters: None
 * Return Value: None
 * Algorithm:
 *     1. Check which player is currently playing.
 *     2. Switch the currentPlayer to the other player.
 *     3. Announce the next player's turn.
 * Reference: None
 */
void Round::switchTurn() {
    if (currentPlayer == player1) {
        //switch to player 2 
        currentPlayer = player2;
    }
    else {
        //switch to player 1 
        currentPlayer = player1;
    }
    //indicate whose turn it is
    cout << "It's now " << currentPlayer->getName() << "'s turn.\n";
}
/**
 * Function Name: playerMove
 * Purpose: Manages the movement of a player's piece.
 * Parameters: None
 * Return Value: None
 * Algorithm:
 *     1. Prompt the current player for the move they wish to make.
 *     2. Validate and execute the move if it is legal.
 *     3. Log the move.
 * Reference: None
 */
void Round::playerMove() {
    //prompt for move
    promptMove();
    //prompt for destination
    promptDestination();
    //output move executed 
    cout << "Player " << currentPlayer->getName() << " moves piece from "
        << currentPlayer->properNotation(currentPlayer->getSelectedPiece())
        << " to " << currentPlayer->properNotation(currentPlayer->getDestination()) << endl;
    //switchTurn();
}
/**
 * Function Name: promptMove
 * Purpose: Asks the current player for their move.
 * Parameters: None
 * Return Value: None
 * Algorithm:
 *     1. Prompt the current player for the starting and ending position of the move.
 *     2. Validate the input format.
 *     3. Attempt to execute the move and log it if successful.
 * Reference: None
 */
void Round::promptMove() {
    //store input for from and to positions
    string from, to;
    //indicate the turn ownership
    cout << currentPlayer->getName() << ", it's your turn." << endl;
    //recording initial piece selection
    cout << "Enter your move from (e.g., A6): ";
    cin >> from;
    //record destination
    cout << "Enter move to (e.g., B6): ";
    cin >> to;

    // Convert inputs using the map
    int fromCol = colToIndex[toupper(from[0])];
    int fromRow = from[1] - '1';
    int toCol = colToIndex[toupper(to[0])];
    int toRow = to[1] - '1';
    //execute move if valid and log 
    if (gameBoard.movePiece(fromRow, fromCol, toRow, toCol, currentPlayer->getPieceType())) {
        logMove(from, to);
    }
    //if move is deemed invalid, prompt for another move 
    else {
        cout << "Invalid move. Please try again." << endl;
    }
}
/**
 * Function Name: promptDestination
 * Purpose: Prompts the current player to select a destination for their piece.
 * Parameters: None
 * Return Value: None
 * Algorithm:
 *     1. Ask the player for the column (A-H) and row (1-8) of the destination.
 *     2. Convert the column letter to an index and adjust row for 0-based indexing.
 *     3. Call setDestination with the converted column and row values.
 * Reference: None
 */
void Round::promptDestination() {
    //prompt user to enter a destination
    char colLetter;
    int row;
    cout << currentPlayer->getName() << ", select a destination for the piece." << endl;
    cout << "Column (A-H): ";
    cin >> colLetter;
    cout << "Row (1-8): ";
    cin >> row;

    //convert column letter to index
    int col = toupper(colLetter) - 'A';
    if (col >= 0 && col < 8 && row >= 1 && row <= 8) {
        currentPlayer->setDestination(row - 1, col); 
    }
    else {
        cout << "Invalid input. Please try again." << endl;
    }
}
/**
 * Function Name: playerTurn
 * Purpose: Executes the logic for the current player's turn.
 * Parameters: None
 * Return Value: None
 * Algorithm:
 *     1. If the current player is a computer, generate and execute a move.
 *     2. If the current player is a human, prompt for a piece to move and a destination, then attempt the move.
 *     3. Log the move, display the move log, and update the board display.
 * Reference: None
 */
void Round::playerTurn() {
    //checking if currentPlayer is computer 
    if (auto compPlayer = dynamic_pointer_cast<ComputerPlayer>(currentPlayer)) {
        cout << "Computer detected" << endl;
        //call computer player function to generate moves based on the current game board
        compPlayer->generateAllPossibleMoves(gameBoard);
        //record move selected by computer
        auto moveDetails = compPlayer->selectAndExecuteMove(gameBoard, compPlayer->getPieceType());
        //check to see if moveDetails is empty
        if (!moveDetails.first.empty() && !moveDetails.second.empty()) {
            //record move made
            logMove(moveDetails.first, moveDetails.second);
            displayMoveLog(); // Optional: Display the move log to see all moves made so far
        }
        //used to record the captures
        vector<pair<int, int >> captures;
        //call function to initiate a capturing of piece
        rules.processCaptures(gameBoard, captures);
        //display board
        gameBoard.showBoard();
        //switch turn after successful move
        switchTurn();
    }
    else {
        //human player turn
        cout << currentPlayer->getName() << ", it's your turn." << endl;

        // Prompt for help or move
        char choice;
        cout << "Enter '1' for help or any other key to continue with your move: ";
        cin >> choice;

        if (choice == '1') {
            // Generate and display possible moves
            vector<MoveDetails> possibleMoves = generateAllPossibleMovesForPlayer(gameBoard, *currentPlayer);
            displayPossibleMoves(possibleMoves);
            cout << "Enter any key to continue with your move." << endl;
            cin >> choice; // Pause before allowing the player to make their move
        }

        char fromColLetter, toColLetter;
        int fromRow, toRow;

        // Prompt for current location of the piece
        cout << "Select a piece to move." << endl;
        cout << "Column (A-H): ";
        cin >> fromColLetter;
        cout << "Row (1-8): ";
        cin >> fromRow;
        //convert to upper due to nature
        int fromCol = toupper(fromColLetter) - 'A';
        fromRow -= 1;

        // Ask for destination
        cout << "Select a destination for the piece." << endl;
        cout << "Column (A-H): ";
        cin >> toColLetter;
        cout << "Row (1-8): ";
        cin >> toRow;
        //convert to upper 
        int toCol = toupper(toColLetter) - 'A';
        toRow -= 1;
        //variable used for recording captures
        vector<pair<int, int>> capturePositions;

        // Validation checks
        if (rules.isValidMove(gameBoard, *currentPlayer, fromRow, fromCol, toRow, toCol) &&
            rules.isPathClear(gameBoard, fromRow, fromCol, toRow, toCol, currentPlayer->getPieceType(), capturePositions) &&
            rules.isValidEndingPosition(gameBoard, toRow, toCol, currentPlayer->getPieceType())) {

            cout << "Passed validation checks!" << endl;
            //log move and update board if move is successful
            if (gameBoard.movePiece(fromRow, fromCol, toRow, toCol, currentPlayer->getPieceType())) {
                cout << "Move successful." << endl;

                cout << "Capture positions: ";
                for (const auto& capture : capturePositions) {
                    cout << "(" << capture.first << ", " << capture.second << "), ";
                }
                cout << endl;

                //rules.processCaptures(gameBoard, capturePositions);
            }
            else {
                cout << "Move failed to execute." << endl;
            }

            // Record move
            string fromPosition = fromColLetter + to_string(fromRow + 1);
            string toPosition = toColLetter + to_string(toRow + 1);
            logMove(fromPosition, toPosition);
            displayMoveLog();
            cout << "Move successful." << endl;
            gameBoard.showBoard();
        }
        else {
            cout << "Invalid move. Please try again." << endl;
            return; // Don't want to switch turns if the move is invalid
        }

        switchTurn(); // Next player's turn
        string saveChoice;
        //prompt for saving a game
        cout << "Turn has switched. Would you like to save the game at this point? (yes/no): ";
        cin >> saveChoice;

        if (saveChoice == "yes") {
            // Assume getCurrentPlayer() returns the player whose turn is next
            shared_ptr<Player> nextPlayer = getCurrentPlayer();
            string nextPlayerName = nextPlayer->getName();
            char nextPlayerPieceType = nextPlayer->getPieceType();

            // Save the game state. Adjust the parameters as necessary.
            Serialization::saveGameState(*this);
            cout << "Game state saved successfully.\n";

            cout << "The game will now close!" << endl;
            exit(1);
        }
    }
}

/**
 * Function Name: logMove
 * Purpose: Records a move made by the current player.
 * Parameters:
 *     from, a string - the starting position of the move in chess notation.
 *     to, a string - the ending position of the move in chess notation.
 * Return Value: None
 * Algorithm:
 *     1. Construct a summary string from the move details.
 *     2. Add the summary to the moveLog vector.
 * Reference: None
 */
void Round::logMove(const string& from, const string& to) {
    //record move made
    string moveSummary = currentPlayer->getName() + " moves from " + from + " to " + to;
    //add to vector 
    moveLog.push_back(moveSummary);
}

/**
 * Function Name: displayMoveLog
 * Purpose: Displays all moves made in the game so far.
 * Parameters: None
 * Return Value: None
 * Algorithm:
 *     1. Iterate through the moveLog vector and print each move.
 * Reference: None
 */
void Round::displayMoveLog() const {
    cout << "Move Log:" << endl;
    //iterate through vector and output move
    for (const auto& move : moveLog) {
        cout << move << endl;
    }
}

/**
 * Function Name: promptPieceLocation
 * Purpose: Asks the player for a piece's location using chess notation.
 * Parameters:
 *     locationDescription, a string reference to store the piece's location in a descriptive format.
 * Return Value: None
 * Algorithm:
 *     1. Prompt the player for the column and row of the piece.
 *     2. Convert the input into a standardized description format.
 * Reference: None
 */
void Round::promptPieceLocation(string& locationDescription) {
    char column;
    int row;
    cout << "Enter column (A-H): ";
    cin >> column;
    cout << "Enter row (1-8): ";
    cin >> row;
    //translate column input to an index 
    int colIndex = translateColumn(toupper(column));
    locationDescription = to_string(colIndex) + to_string(row - 1);
}

/**
 * Function Name: translateColumn
 * Purpose: Converts a column letter to its corresponding index.
 * Parameters:
 *     columnLetter, a char representing the column letter.
 * Return Value: The index of the column as an int.
 * Algorithm:
 *     1. Use the colToIndex map to convert the column letter to an index.
 * Reference: None
 */
int Round::translateColumn(char columnLetter) {
    //use mapping to convert the letter to an index
    if (colToIndex.find(columnLetter) != colToIndex.end()) {
        return colToIndex[columnLetter];
    }
    //indicates a invalid input
    return -1; 
}
/**
 * Function Name: startGame
 * Purpose: Initiates the game with an optional starting player.
 * Parameters:
 *     startingPlayer, a shared_ptr<Player> indicating the player to start, defaulting to nullptr.
 * Return Value: None
 * Algorithm:
 *     1. If a starting player is provided, use it as the currentPlayer; otherwise, perform a coin toss.
 *     2. Enter the main game loop, prompting for moves and checking game-ending conditions.
 * Reference: None
 */
void Round::startGame(shared_ptr<Player> startingPlayer = nullptr) {
    //set the starting player if its provided, otherwise intiate a coin toss
    if (startingPlayer != nullptr) {
        this->currentPlayer = startingPlayer;
    }
    else {
        coinToss();
    }
    //coinToss(); // 

    //main game loop
    //variable indicates if a game/round has ended
    bool gameOver = false;
    while (!gameOver) {
        //display board at each turn
        gameBoard.showBoard(); 
        //switch turns
        playerTurn(); // 

        // Check if all pieces of one color are connected after each turn
        bool blackConnected = checkConnectedGroup('B');
        bool whiteConnected = checkConnectedGroup('W');

        if (blackConnected || whiteConnected) {
            // If any color's pieces are all connected, the round is considered over
            //determine winner 
            determineWinner(); 
            //update scores
            updateScores(); 
            //game is over
            gameOver = true; 
            cout << "Round over!" << endl;
        }
    }
    //display ending state of board
    gameBoard.showBoard();
    cout << "Game over!" << endl;
}
/**
 * Function Name: updateScores
 * Purpose: Updates the scores for the players after determining the winner.
 * Parameters: None
 * Return Value: None
 * Algorithm:
 *     1. Count black and white pieces on the board.
 *     2. Determine the score difference based on the winner.
 *     3. Update the winner's score by the score difference.
 * Reference: None
 */
void Round::updateScores() {
    //count pieces for each player
    auto [blackCount, whiteCount] = gameBoard.countPiecesByColor(); 

    int player1Pieces = player1->getPieceType() == 'B' ? blackCount : whiteCount;
    int player2Pieces = player2->getPieceType() == 'B' ? blackCount : whiteCount;

    //adjust scores based on winners count
    if (winner == player1) {
        // Calculate score difference for the winner
        int scoreDifference = player1Pieces - player2Pieces;
        //only winner score updated
        player1Score += scoreDifference; 
        cout << "score difference: " << scoreDifference;

    }
    else if (winner == player2) {
        // Calculate score difference for the winner
        int scoreDifference = player2Pieces - player1Pieces;
        player2Score += scoreDifference; 
        cout << "score difference: " << scoreDifference;

    }
    // The loser does not gain or lose points from the round outcome
}
/**
 * Function Name: calculateScore
 * Purpose: Calculates the score difference between the two players.
 * Parameters: None
 * Return Value: The score difference as an integer.
 * Algorithm:
 *     1. Count black and white pieces on the board.
 *     2. Calculate the score difference based on players' pieces.
 * Reference: None
 */
int Round::calculateScore() const {
    auto [blackCount, whiteCount] = gameBoard.countPiecesByColor(); //COUNT PIECES

    
    int piecesPlayer1 = (player1->getPieceType() == 'B') ? blackCount : whiteCount; //get pieces
    int piecesPlayer2 = (player2->getPieceType() == 'B') ? blackCount : whiteCount; //get pieces
    //return score difference 
    return piecesPlayer1 - piecesPlayer2;
}
/**
 * Function Name: checkRoundOver
 * Purpose: Checks if the current round is over based on game conditions.
 * Parameters: None
 * Return Value: A boolean indicating if the round is over.
 * Algorithm:
 *     1. Placeholder function, implement based on game-ending conditions.
 * Reference: None
 */
bool Round::checkRoundOver() const {
  //place holder
    return false;
}
/**
 * Function Name: determineWinner
 * Purpose: Determines the winner of the current round based on the game state.
 * Parameters: None
 * Return Value: None
 * Algorithm:
 *     1. Check if all pieces of one color are connected for both players.
 *     2. Set the winner accordingly and update rounds won.
 *     3. Handle a draw or special conditions if necessary.
 * Reference: None
 */
void Round::determineWinner() {
    // Check if all pieces of one color are connected for both players
    bool player1Connected = checkConnectedGroup(player1->getPieceType());
    bool player2Connected = checkConnectedGroup(player2->getPieceType());
    //display winner
    if (player1Connected && !player2Connected) {
        cout << player1->getName() << " wins this round!" << endl;
        winner = player1;
        player1->setRoundsWon(player1->getRoundsWon()+1);
    }
    else if (!player1Connected && player2Connected) {
        cout << player2->getName() << " wins this round!" << endl;
        winner = player2;
        player2->setRoundsWon(player2->getRoundsWon() + 1);

    }
    //THESE CHECKS MAY NOT BE NECESSARY 
    else if (player1Connected && player2Connected) {
        
        cout << "Both players seem to have connected groups. Check for a possible error." << endl;
        winner = nullptr; 
    }
    else {
        cout << "No player has formed a connected group yet." << endl;
        winner = nullptr;
    }

    // Update scores after determining the winner
    //updateScores();
    calculateScore();
}


//ALGO APPROACH

/**
 * Function Name: checkConnectedGroup
 * Purpose: Checks if all pieces of a specified color are connected.
 * Parameters:
 *     color, a char representing the color to check for connectivity.
 * Return Value: A boolean indicating if all pieces of the color are connected.
 * Algorithm:
 *     1. Perform a depth-first search starting from any piece of the specified color.
 *     2. Check if all pieces of that color are reachable from the starting piece.
 * Reference: Chatgpt
 */
bool Round::checkConnectedGroup(char color) const {
    int startRow = -1, startCol = -1;
    //keeps track of pieces visited
    vector<vector<bool>> visited(8, vector<bool>(8, false));

    // Find the starting piece of the given color
    for (int row = 0; row < 8 && startRow == -1; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (gameBoard.getPieceAt(row, col) == color) {
                startRow = row;
                startCol = col;
                break;
            }
        }
    }

    // If no starting piece was found, return false
    if (startRow == -1) return false;

    // Start DFS from the first found piece
    DFS(startRow, startCol, color, visited);

    // Check if all pieces of the color are visited
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (gameBoard.getPieceAt(row, col) == color && !visited[row][col]) {
                //found unvisited piece
                return false; 
            }
        }
    }
    //all pieces are connected
    return true; 
}

/**
 * Function Name: DFS
 * Purpose: Performs a depth-first search to check connectivity of pieces.
 * Parameters:
 *     row, col, integers indicating the starting position for DFS.
 *     color, a char indicating the color of pieces to check for connectivity.
 *     visited, a reference to a 2D vector of bools marking visited positions.
 * Return Value: None
 * Algorithm:
 *     1. Recursively visit all connected positions of the specified color.
 * Reference: None
 */
void Round::DFS(int row, int col, char color, vector<vector<bool>>& visited) const {
    //define search directions
    static const int rowNbr[] = { -1, 1, 0, 0, -1, -1, 1, 1 };
    static const int colNbr[] = { 0, 0, -1, 1, -1, 1, -1, 1 };
    //mark pos as visited 
    visited[row][col] = true;

    // Recur for all connected neighbours
    for (int k = 0; k < 8; ++k) {
        //check to see if move is within bounds, correct color piece, and not visited yet
        if (isSafe(row + rowNbr[k], col + colNbr[k], color, visited)) {
            DFS(row + rowNbr[k], col + colNbr[k], color, visited);
        }
    }
}

/**
 * Function Name: isSafe
 * Purpose: Checks if a cell is safe to include in the DFS for checking connectivity.
 * Parameters:
 *     row, col, integers indicating the position to check.
 *     color, a char indicating the color of pieces to check for connectivity.
 *     visited, a reference to a 2D vector of bools marking visited positions.
 * Return Value: A boolean indicating if the position is safe to include in DFS.
 * Algorithm:
 *     1. Check if the position is within bounds, matches the specified color, and has not been visited.
 * Reference: None
 */
bool Round::isSafe(int row, int col, char color, vector<vector<bool>>& visited) const {
    //return true or false if a piece is safe to visit 
    return (row >= 0) && (row < 8) && (col >= 0) && (col < 8) &&
        (gameBoard.getPieceAt(row, col) == color) && !visited[row][col];
}
/**
 * Function Name: setStartingPlayer
 * Purpose: Sets the starting player for the game.
 * Parameters:
 *     startingPlayer, a shared_ptr<Player> indicating the player to start the game.
 * Return Value: None
 * Algorithm:
 *     1. Set currentPlayer to startingPlayer.
 *     2. Determine if it is player 1's turn based on the starting player.
 * Reference: None
 */
void Round::setStartingPlayer(shared_ptr<Player> startingPlayer) {
    currentPlayer = startingPlayer;
    // Determine if it is player 1's turn based on the starting player
    isPlayer1Turn = (currentPlayer == player1);

}
/**
 * Function Name: getRoundWinner
 * Purpose: Retrieves the winner of the current round.
 * Parameters: None
 * Return Value: A shared_ptr<Player> pointing to the winner of the round.
 * Algorithm:
 *     1. Return the winner member variable.
 * Reference: None
 */
shared_ptr<Player> Round::getRoundWinner() const {
    return winner;
}
/**
 * Function Name: setBoardState
 * Purpose: Sets the board to a specified state.
 * Parameters:
 *     loadedBoard, a Board object representing the new state of the board.
 * Return Value: None
 * Algorithm:
 *     1. Update the gameBoard member variable to reflect the loadedBoard state.
 * Reference: None
 */
void Round::setBoardState(const Board& loadedBoard) {
    //grants access to current object
    this->gameBoard = loadedBoard; 
}

/**
 * Function Name: continueRound
 * Purpose: Continues the round from the current state.
 * Parameters: None
 * Return Value: None
 * Algorithm:
 *     1. Resume gameplay from the current state, checking for game-ending conditions.
 * Reference: None
 */
void Round::continueRound() {
 
    bool gameOver = false;
    while (!gameOver) {
        //display board
        gameBoard.showBoard(); 
        cout << "It's " << currentPlayer->getName() << "'s turn.\n";
        //proceed with current player turn
        playerTurn(); 

        // Check for game-ending conditions after each turn
        bool blackConnected = checkConnectedGroup('B');
        bool whiteConnected = checkConnectedGroup('W');
        if (blackConnected || whiteConnected) {
            //annouce winner
            determineWinner(); // Determine and announce the winner
            //update scores
            updateScores(); 
            gameOver = true; // End the game loop
            cout << "Round over!\n";
        }
        //else {
        //    switchTurn(); // Switch to the next player if the game isn't over
        //}
    }
}
vector<Round::MoveDetails> Round::generateAllPossibleMovesForPlayer(Board& board, const Player& player) {
    vector<Round::MoveDetails> possibleMoves;

    // Iterate over all board positions to find the player's pieces
    for (int fromRow = 0; fromRow < 8; ++fromRow) {
        for (int fromCol = 0; fromCol < 8; ++fromCol) {
            // Check if the position contains one of the player's pieces
            if (board.getPieceAt(fromRow, fromCol) == player.getPieceType()) {
                // Generate all valid horizontal moves
                int horizontalMovesRequired = Rules::countPiecesInLine(board, fromRow, fromCol, 'H');
                for (int offset = 1; offset <= horizontalMovesRequired; ++offset) {
                    // Adding moves when moving right
                    addMoveIfValid(board, player, possibleMoves, fromRow, fromCol, fromRow, fromCol + offset);
                    // Adding moves when moving left
                    addMoveIfValid(board, player, possibleMoves, fromRow, fromCol, fromRow, fromCol - offset);
                }

                // Generate all valid vertical moves
                int verticalMovesRequired = Rules::countPiecesInLine(board, fromRow, fromCol, 'V');
                for (int offset = 1; offset <= verticalMovesRequired; ++offset) {
                    // Adding moves when moving down
                    addMoveIfValid(board, player, possibleMoves, fromRow, fromCol, fromRow + offset, fromCol);
                    // Adding moves when moving up
                    addMoveIfValid(board, player, possibleMoves, fromRow, fromCol, fromRow - offset, fromCol);
                }

                // Generate all valid diagonal moves (top-left to bottom-right and top-right to bottom-left)
                int diagonalMoves1 = Rules::countDiagonalPieces(board, fromRow, fromCol, fromRow + 1, fromCol + 1);
                for (int offset = 1; offset <= diagonalMoves1; ++offset) {
                    addMoveIfValid(board, player, possibleMoves, fromRow, fromCol, fromRow + offset, fromCol + offset); // Down-right
                    addMoveIfValid(board, player, possibleMoves, fromRow, fromCol, fromRow - offset, fromCol - offset); // Up-left
                }

                // Generate all valid diagonal moves (top-right to bottom-left and bottom-right to top-left)
                int diagonalMoves2 = Rules::countDiagonalPieces(board, fromRow, fromCol, fromRow + 1, fromCol - 1);
                for (int offset = 1; offset <= diagonalMoves2; ++offset) {
                    addMoveIfValid(board, player, possibleMoves, fromRow, fromCol, fromRow + offset, fromCol - offset); // Down-left
                    addMoveIfValid(board, player, possibleMoves, fromRow, fromCol, fromRow - offset, fromCol + offset); // Up-right
                }
            }
        }
    }

    return possibleMoves;
}

void Round::addMoveIfValid(Board& board, const Player& player, vector<Round::MoveDetails>& possibleMoves, int startRow, int startCol, int endRow, int endCol) {
    vector<pair<int, int>> capturePositions;
    if (board.isPositionValid(endRow, endCol) &&
        Rules::isValidMove(board, player, startRow, startCol, endRow, endCol) &&
        Rules::isPathClear(board, startRow, startCol, endRow, endCol, player.getPieceType(), capturePositions) &&
        Rules::isValidEndingPosition(board, endRow, endCol, player.getPieceType())) {

        // Create a Round::MoveDetails object with starting position, ending position, and any capture positions
        Round::MoveDetails move{ {startRow, startCol}, {endRow, endCol}, capturePositions };
        possibleMoves.push_back(move);
    }
}
void Round::displayPossibleMoves(const std::vector<MoveDetails>& possibleMoves) const {
    if (possibleMoves.empty()) {
        std::cout << "No possible moves available." << std::endl;
        return;
    }

    std::cout << "Possible Moves:" << std::endl;
    for (const auto& move : possibleMoves) {
        // Convert the start and end positions to a more readable format (e.g., A1 to B2)
        char startCol = static_cast<char>('A' + move.start.second);
        int startRow = move.start.first + 1;
        char endCol = static_cast<char>('A' + move.end.second);
        int endRow = move.end.first + 1;

        std::cout << startCol << startRow << " to " << endCol << endRow;

        if (!move.captures.empty()) {
            std::cout << " with captures at: ";
            for (const auto& capture : move.captures) {
                char captureCol = static_cast<char>('A' + capture.second);
                int captureRow = capture.first + 1;
                std::cout << captureCol << captureRow << " ";
            }
        }
        std::cout << std::endl;
    }
}





