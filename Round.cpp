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
//cosntructor for setting board and players
//Round::Round(Player* p1, Player* p2) : player1(p1), player2(p2), currentPlayer(nullptr), isPlayer1Turn(true),player1Score(0), player2Score(0), winner(nullptr) {
//    srand(static_cast<unsigned int>(time(nullptr))); // seed
//    gameBoard.resetBoard(); // Initialize the board
//}
// 
Round::Round(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2) : player1(p1), player2(p2), currentPlayer(nullptr), isPlayer1Turn(true), player1Score(0), player2Score(0), winner(nullptr) {
    srand(static_cast<unsigned int>(time(nullptr))); // Seed
    gameBoard.resetBoard(); // Initialize the board
}

//decide who goes first
void Round::coinToss() {
    cout << "Enter 1 for heads or 2 for tails.\n";
    int userChoice;
    cin >> userChoice;
    int toss = rand() % 2 + 1; // get rand num
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
// change turns
void Round::switchTurn() {
    if (currentPlayer == player1) {
        currentPlayer = player2;
    }
    else {
        currentPlayer = player1;
    }
    cout << "It's now " << currentPlayer->getName() << "'s turn.\n";
}
// logic for movement
void Round::playerMove() {
    promptMove();
    promptDestination();
    cout << "Player " << currentPlayer->getName() << " moves piece from "
        << currentPlayer->properNotation(currentPlayer->getSelectedPiece())
        << " to " << currentPlayer->properNotation(currentPlayer->getDestination()) << endl;
    //switchTurn();
}
//ask for move
void Round::promptMove() {
    string from, to;
    cout << currentPlayer->getName() << ", it's your turn." << endl;
    cout << "Enter your move from (e.g., A6): ";
    cin >> from;
    cout << "Enter move to (e.g., B6): ";
    cin >> to;

    // Convert inputs using the map
    int fromCol = colToIndex[toupper(from[0])];
    int fromRow = from[1] - '1';
    int toCol = colToIndex[toupper(to[0])];
    int toRow = to[1] - '1';

    if (gameBoard.movePiece(fromRow, fromCol, toRow, toCol, currentPlayer->getPieceType())) {
        logMove(from, to);
    }
    else {
        cout << "Invalid move. Please try again." << endl;
    }
}
//ask for destination
void Round::promptDestination() {
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
        currentPlayer->setDestination(row - 1, col); // 0 based indexing adjustment
    }
    else {
        cout << "Invalid input. Please try again." << endl;
    }
}

void Round::playerTurn() {
    cout << "Start of Player turn" << endl;
    if (auto compPlayer = std::dynamic_pointer_cast<ComputerPlayer>(currentPlayer)) {
        cout << "Computer detected" << endl;
        // Generate all possible moves for the computer player
       // cout << "before generating all possible moves!\n";
        //gameBoard.showBoard();
            compPlayer->generateAllPossibleMoves(gameBoard);
           
        // Let the computer player select one of the generated moves and execute it
        //compPlayer->selectAndExecuteMove(gameBoard, compPlayer->getPieceType());

        // Assuming selectAndExecuteMove handles move execution, logging, and displaying,
        // there's no need for the commented-out manual execution and logging here.
        // Hence, the next lines regarding manual execution and logging are removed.
           // cout << "After the ai generates it move " << endl;
            //gameBoard.showBoard();
        auto moveDetails = compPlayer->selectAndExecuteMove(gameBoard, compPlayer->getPieceType());
        
        if (!moveDetails.first.empty() && !moveDetails.second.empty()) {
            logMove(moveDetails.first, moveDetails.second);
            displayMoveLog(); // Optional: Display the move log to see all moves made so far
        }
        vector<pair<int, int >> captures;
        rules.processCaptures(gameBoard, captures);
        gameBoard.showBoard(); // Display the updated board state
        switchTurn(); // Exit the method early for computer player
    }
    else {
        cout << currentPlayer->getName() << ", it's your turn." << endl;
        char fromColLetter, toColLetter;
        int fromRow, toRow;

        // Prompt for current location of the piece
        cout << "Select a piece to move." << endl;
        cout << "Column (A-H): ";
        cin >> fromColLetter;
        cout << "Row (1-8): ";
        cin >> fromRow;

        int fromCol = toupper(fromColLetter) - 'A';
        fromRow -= 1;

        // Ask for location
        cout << "Select a destination for the piece." << endl;
        cout << "Column (A-H): ";
        cin >> toColLetter;
        cout << "Row (1-8): ";
        cin >> toRow;

        int toCol = toupper(toColLetter) - 'A';
        toRow -= 1;
        vector<pair<int, int>> capturePositions;

        // Validation checks
        if (rules.isValidMove(gameBoard, *currentPlayer, fromRow, fromCol, toRow, toCol) &&
            rules.isPathClear(gameBoard, fromRow, fromCol, toRow, toCol, currentPlayer->getPieceType(), capturePositions) &&
            rules.isValidEndingPosition(gameBoard, toRow, toCol, currentPlayer->getPieceType())) {
            
            cout << "Passed validation checks!" << endl;
            // Execute the move
            //gameBoard.movePiece(fromRow, fromCol, toRow, toCol, currentPlayer->getPieceType());
            //cout << "Attempting to move piece from " << fromPosition << " to " << toPosition << endl;
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
            return; // Don't want to switch turns if invalid move
        }

        switchTurn(); // Next player's turn
        std::string saveChoice;
        std::cout << "Turn has switched. Would you like to save the game at this point? (yes/no): ";
        std::cin >> saveChoice;

        if (saveChoice == "yes") {
            // Assume getCurrentPlayer() returns the player whose turn is next
            std::shared_ptr<Player> nextPlayer = getCurrentPlayer();
            std::string nextPlayerName = nextPlayer->getName();
            char nextPlayerPieceType = nextPlayer->getPieceType();

            // Save the game state. Adjust the parameters as necessary.
            Serialization::saveGameState(*this);
            std::cout << "Game state saved successfully.\n";

            cout << "The game will now close!" << endl;
            exit(1);
        }
    }
}

//// handles the move logic and validates
//void Round::playerTurn() {
//    cout << currentPlayer->getName() << "'s turn." << endl;
//    if (auto compPlayer = std::dynamic_pointer_cast<ComputerPlayer>(currentPlayer)) {
//        // Generate all possible moves and choose the best one
//        compPlayer->generateAllPossibleMoves(gameBoard);
//        compPlayer->chooseBestMove();
//
//        auto selectedPiece = compPlayer->getSelectedPiece();
//        auto destination = compPlayer->getDestination();
//
//        // Execute the move
//        gameBoard.movePiece(selectedPiece.first - 'A', selectedPiece.second - 1, destination.first - 'A', destination.second - 1, compPlayer->getPieceType());
//
//        // Logging and displaying the move
//        cout << "Computer moved from " << compPlayer->properNotation(selectedPiece) << " to " << compPlayer->properNotation(destination) << endl;
//
//        switchTurn(); // Switch turn after computer's move
//        return; // Exit the method early for computer player
//    }
//
//
//    char fromColLetter, toColLetter;
//    int fromRow, toRow;
//
//    // Prompt for current location of the piece
//    cout << "Select a piece to move." << endl;
//    cout << "Column (A-H): ";
//    cin >> fromColLetter;
//    cout << "Row (1-8): ";
//    cin >> fromRow;
//
//    int fromCol = toupper(fromColLetter) - 'A';
//    fromRow -= 1;
//
//    //ask for location
//    cout << "Select a destination for the piece." << endl;
//    cout << "Column (A-H): ";
//    cin >> toColLetter;
//    cout << "Row (1-8): ";
//    cin >> toRow;
//
//
//    int toCol = toupper(toColLetter) - 'A';
//    toRow -= 1;
//    vector<pair<int, int>> capturePositions;
//
//    // validation checks
//    if (rules.isValidMove(gameBoard, *currentPlayer, fromRow, fromCol, toRow, toCol) &&
//        rules.isPathClear(gameBoard, fromRow, fromCol, toRow, toCol, currentPlayer->getPieceType(), capturePositions) &&
//        rules.isValidEndingPosition(gameBoard, toRow, toCol, currentPlayer->getPieceType())) {
//
//        // execute the move
//        gameBoard.movePiece(fromRow, fromCol, toRow, toCol, currentPlayer->getPieceType());
//
//        // record move
//        string fromPosition = fromColLetter + to_string(fromRow + 1);
//        string toPosition = toColLetter + to_string(toRow + 1);
//        logMove(fromPosition, toPosition);
//        displayMoveLog();
//
//        cout << "Move successful." << endl;
//
//        gameBoard.showBoard();
//    }
//    else {
//        cout << "Invalid move. Please try again." << endl;
//        return; // dont want to switch turns if invalid move
//    }
//    /*cout << "Do you want to save the game? (yes/no): ";
//    string input;
//    cin >> input;
//    if (input == "yes") {
//        Serialization::saveGameState(gameBoard, *player1, *player2, isPlayer1Turn, player1Score, player2Score);
//        cout << "Game saved successfully.\n";
//    }*/
//    switchTurn(); //next player's turn
//}
// 
// 
//void Round::playerTurn() {
//    cout << currentPlayer->getName() << ", it's your turn." << endl;
//
//    char fromColLetter, toColLetter;
//    int fromRow, toRow;
//
//    // Prompt for current location of the piece
//    cout << "Select a piece to move." << endl;
//    cout << "Column (A-H): ";
//    cin >> fromColLetter;
//    cout << "Row (1-8): ";
//    cin >> fromRow;
//
//    int fromCol = toupper(fromColLetter) - 'A';
//    fromRow -= 1;
//
//    //ask for location
//    cout << "Select a destination for the piece." << endl;
//    cout << "Column (A-H): ";
//    cin >> toColLetter;
//    cout << "Row (1-8): ";
//    cin >> toRow;
//
//
//    int toCol = toupper(toColLetter) - 'A';
//    toRow -= 1;
//    vector<pair<int, int>> capturePositions;
//
//    // validation checks
//    if (rules.isValidMove(gameBoard, *currentPlayer, fromRow, fromCol, toRow, toCol) &&
//        rules.isPathClear(gameBoard, fromRow, fromCol, toRow, toCol, currentPlayer->getPieceType(), capturePositions) &&
//        rules.isValidEndingPosition(gameBoard, toRow, toCol, currentPlayer->getPieceType())) {
//
//        // execute the move
//        gameBoard.movePiece(fromRow, fromCol, toRow, toCol, currentPlayer->getPieceType());
//
//        // record move
//        string fromPosition = fromColLetter + to_string(fromRow + 1);
//        string toPosition = toColLetter + to_string(toRow + 1);
//        logMove(fromPosition, toPosition);
//        displayMoveLog();
//
//        cout << "Move successful." << endl;
//
//        gameBoard.showBoard();
//    }
//    else {
//        cout << "Invalid move. Please try again." << endl;
//        return; // dont want to switch turns if invalid move
//    }
//    /*cout << "Do you want to save the game? (yes/no): ";
//    string input;
//    cin >> input;
//    if (input == "yes") {
//        Serialization::saveGameState(gameBoard, *player1, *player2, isPlayer1Turn, player1Score, player2Score);
//        cout << "Game saved successfully.\n";
//    }*/
//    switchTurn(); //next player's turn
//}

// record recent move
void Round::logMove(const string& from, const string& to) {

    string moveSummary = currentPlayer->getName() + " moves from " + from + " to " + to;
    moveLog.push_back(moveSummary);
}

// record all moves
void Round::displayMoveLog() const {
    cout << "Move Log:" << endl;
    for (const auto& move : moveLog) {
        cout << move << endl;
    }
}

// ask fo location index
void Round::promptPieceLocation(string& locationDescription) {
    char column;
    int row;
    cout << "Enter column (A-H): ";
    cin >> column;
    cout << "Enter row (1-8): ";
    cin >> row;

    int colIndex = translateColumn(toupper(column));
    locationDescription = to_string(colIndex) + to_string(row - 1);
}

//translate column 
int Round::translateColumn(char columnLetter) {
    if (colToIndex.find(columnLetter) != colToIndex.end()) {
        return colToIndex[columnLetter];
    }
    return -1; // not a valid input
}


void Round::startGame(shared_ptr<Player> startingPlayer = nullptr) {
    if (startingPlayer != nullptr) {
        this->currentPlayer = startingPlayer;
    }
    else {
        coinToss();
    }
    //coinToss(); // 

    // Main game loop
    bool gameOver = false;
    while (!gameOver) {
        gameBoard.showBoard(); // Display the board at the start of each turn
        playerTurn(); // the current player's turn

        // Check if all pieces of one color are connected after each turn
        bool blackConnected = checkConnectedGroup('B');
        bool whiteConnected = checkConnectedGroup('W');

        if (blackConnected || whiteConnected) {
            // If any color's pieces are all connected, the round is considered over
            determineWinner(); // Determine and announce the winner based on the game state
            updateScores(); // Update the scores based on this round's outcome

            gameOver = true; // Mark the game as over
            cout << "Round over!" << endl;
        }
    }

    gameBoard.showBoard();
    cout << "Game over!" << endl;
}




//void Round::updateScores() {
//    auto [blackCount, whiteCount] = gameBoard.countPiecesByColor(); //COUNT PIECES
//
//
//    int piecesPlayer1 = (player1->getPieceType() == 'B') ? blackCount : whiteCount; //get pieces
//    int piecesPlayer2 = (player2->getPieceType() == 'B') ? blackCount : whiteCount;
//
//    // Update scores based on the difference in the number of pieces
//    player1Score += piecesPlayer1 - piecesPlayer2; 
//    player2Score += piecesPlayer2 - piecesPlayer1;
//}

void Round::updateScores() {
    auto [blackCount, whiteCount] = gameBoard.countPiecesByColor(); // Count pieces

    int player1Pieces = player1->getPieceType() == 'B' ? blackCount : whiteCount;
    int player2Pieces = player2->getPieceType() == 'B' ? blackCount : whiteCount;

    // Assuming winner has been correctly identified
    if (winner == player1) {
        // Calculate score difference for the winner
        int scoreDifference = player1Pieces - player2Pieces;
        player1Score += scoreDifference; // Only winner's score is updated
        cout << "score difference: " << scoreDifference;

    }
    else if (winner == player2) {
        // Calculate score difference for the winner
        int scoreDifference = player2Pieces - player1Pieces;
        player2Score += scoreDifference; // Only winner's score is updated
        cout << "score difference: " << scoreDifference;

    }
    // The loser does not gain or lose points from the round outcome
}

int Round::calculateScore() const {
    auto [blackCount, whiteCount] = gameBoard.countPiecesByColor(); //COUNT PIECES

    // Example calculation - adjust based on your scoring logic
    int piecesPlayer1 = (player1->getPieceType() == 'B') ? blackCount : whiteCount; //get pieces
    int piecesPlayer2 = (player2->getPieceType() == 'B') ? blackCount : whiteCount; //get pieces

    return piecesPlayer1 - piecesPlayer2; //score calc
}

bool Round::checkRoundOver() const {
  //place holder
    return false;
}


void Round::determineWinner() {
    // Check if all pieces of one color are connected for both players
    bool player1Connected = checkConnectedGroup(player1->getPieceType());
    bool player2Connected = checkConnectedGroup(player2->getPieceType());

    if (player1Connected && !player2Connected) {
        std::cout << player1->getName() << " wins this round!" << std::endl;
        winner = player1;
        player1->setRoundsWon(player1->getRoundsWon()+1);
    }
    else if (!player1Connected && player2Connected) {
        std::cout << player2->getName() << " wins this round!" << std::endl;
        winner = player2;
        player2->setRoundsWon(player2->getRoundsWon() + 1);

    }
    else if (player1Connected && player2Connected) {
        // This scenario may indicate an error or a special rule.
        std::cout << "Both players seem to have connected groups. Check for a possible error." << std::endl;
        winner = nullptr; // Handle according to your game's rules.
    }
    else {
        std::cout << "No player has formed a connected group yet." << std::endl;
        // The game continues if no winner is determined.
        winner = nullptr;
    }

    // Update scores after determining the winner
    //updateScores();
    calculateScore();
}


//ALGO APPROACH


// Check if all pieces of one color are connected
bool Round::checkConnectedGroup(char color) const {
    int startRow = -1, startCol = -1;
    std::vector<std::vector<bool>> visited(8, std::vector<bool>(8, false));

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
                return false; // Found an unvisited piece of the same color
            }
        }
    }

    return true; // All pieces of the color are connected
}

// Utility function for DFS traversal
void Round::DFS(int row, int col, char color, std::vector<std::vector<bool>>& visited) const {
    static const int rowNbr[] = { -1, 1, 0, 0, -1, -1, 1, 1 };
    static const int colNbr[] = { 0, 0, -1, 1, -1, 1, -1, 1 };

    visited[row][col] = true;

    // Recur for all connected neighbours
    for (int k = 0; k < 8; ++k) {
        if (isSafe(row + rowNbr[k], col + colNbr[k], color, visited)) {
            DFS(row + rowNbr[k], col + colNbr[k], color, visited);
        }
    }
}

// Check if a cell can be included in DFS
bool Round::isSafe(int row, int col, char color, std::vector<std::vector<bool>>& visited) const {
    return (row >= 0) && (row < 8) && (col >= 0) && (col < 8) &&
        (gameBoard.getPieceAt(row, col) == color) && !visited[row][col];
}
//EXPERIMENTAL
void Round::startGameWithoutCoinToss() {

    // Main game loop remains the same as in startGame
    bool gameOver = false;
    while (!gameOver) {
        gameBoard.showBoard(); // Display the board at the start of each turn
        playerTurn(); // Conduct the current player's turn

        if (checkRoundOver()) {
            determineWinner(); // Determine and announce the winner
            updateScores(); // Update the scores based on this round's outcome
            gameOver = true; // Mark the game as over
        }
    }

    gameBoard.showBoard();
    std::cout << "Game over!" << std::endl;
}


void Round::setStartingPlayer(shared_ptr<Player> startingPlayer) {
    currentPlayer = startingPlayer;
    // Determine if it is player 1's turn based on the starting player
    isPlayer1Turn = (currentPlayer == player1);

}
shared_ptr<Player> Round::getRoundWinner() const {
    return winner;
}

void Round::setBoardState(const Board& loadedBoard) {
    this->gameBoard = loadedBoard; // Assuming `gameBoard` is your Board instance in `Round`
}

void Round::updatePlayerPieceTypes(char humanPieceType, char computerPieceType) {
    auto humanPlayer = std::dynamic_pointer_cast<HumanPlayer>(player1->getName() == "Human" ? player1 : player2);
    auto computerPlayer = std::dynamic_pointer_cast<ComputerPlayer>(player1->getName() == "AI" ? player1 : player2);

    if (humanPlayer) {
        humanPlayer->setPieceType(humanPieceType);
    }

    if (computerPlayer) {
        computerPlayer->setPieceType(computerPieceType);
    }
}

//void Round::continueRound() {
//    // Check if the game has a winner or if the game can continue
//    if (checkRoundOver()) {
//        determineWinner();
//        updateScores();
//        // Handle end of round logic here
//    }
//    else {
//        cout << "Resuming game...\n";
//        gameBoard.showBoard();
//        cout << "It's " << currentPlayer->getName() << "'s turn." << endl;
//
//        // Continue with the gameplay
//        //startGame();
//        cout << "Right before hitting player turn function" << endl;
//        playerTurn();
//    }
//}

void Round::continueRound() {
    bool gameOver = false;
    while (!gameOver) {
        gameBoard.showBoard(); // Display the board
        cout << "It's " << currentPlayer->getName() << "'s turn.\n";

        playerTurn(); // Proceed with the current player's turn

        // Check for game-ending conditions after each turn
        bool blackConnected = checkConnectedGroup('B');
        bool whiteConnected = checkConnectedGroup('W');
        if (blackConnected || whiteConnected) {
            determineWinner(); // Determine and announce the winner
            updateScores(); // Update scores based on round outcome
            gameOver = true; // End the game loop
            cout << "Round over!\n";
        }
        //else {
        //    switchTurn(); // Switch to the next player if the game isn't over
        //}
    }
}


void Round::continueGameFromSavedState() {
    cout << "Resuming game...\n";
    gameBoard.showBoard();
    cout << "It's " << currentPlayer->getName() << "'s turn." << endl;

    if (std::dynamic_pointer_cast<ComputerPlayer>(currentPlayer)) {
        continueComputerTurn();
    }
    else {
        continueHumanPlayerTurn();
    }
}

void Round::continueHumanPlayerTurn() {
    // Display current game state to the player
    cout << "Resuming your turn...\n";
    gameBoard.showBoard();
    cout << "It's your turn, " << currentPlayer->getName() << ".\n";

    // Variables to store move input
    char fromColLetter, toColLetter;
    int fromRow, toRow;

    // Prompt player for move input
    cout << "Select a piece to move.\nColumn (A-H): ";
    cin >> fromColLetter;
    cout << "Row (1-8): ";
    cin >> fromRow;

    cout << "Select a destination for the piece.\nColumn (A-H): ";
    cin >> toColLetter;
    cout << "Row (1-8): ";
    cin >> toRow;

    // Convert input to zero-based indexing as necessary
    int fromCol = toupper(fromColLetter) - 'A';
    fromRow -= 1; // Adjusting to 0-indexed if necessary
    int toCol = toupper(toColLetter) - 'A';
    toRow -= 1; // Adjusting to 0-indexed if necessary

    // Vector to hold any capture positions, if applicable
    vector<pair<int, int>> capturePositions;

    cout << "Before entering the validation checks\n";
    gameBoard.showBoard();
    cout << "Attempting move from [" << fromRow << "," << fromCol << "] to [" << toRow << "," << toCol << "]\n";

    // Validate the move before attempting to execute it
    bool validMove = rules.isValidMove(gameBoard, *currentPlayer, fromRow, fromCol, toRow, toCol);
    cout << "isValidMove: " << validMove << "\n";
    bool pathClear = rules.isPathClear(gameBoard, fromRow, fromCol, toRow, toCol, currentPlayer->getPieceType(), capturePositions);
    cout << "isPathClear: " << pathClear << ", Captures: " << capturePositions.size() << "\n";
    bool validEndingPosition = rules.isValidEndingPosition(gameBoard, toRow, toCol, currentPlayer->getPieceType());
    cout << "isValidEndingPosition: " << validEndingPosition << "\n";

    if (validMove && pathClear && validEndingPosition) {
        if (gameBoard.movePiece(fromRow, fromCol, toRow, toCol, currentPlayer->getPieceType())) {
            cout << "Move successful!\n";
            rules.processCaptures(gameBoard, capturePositions);

            string fromPosition = string(1, fromColLetter) + to_string(fromRow + 1);
            string toPosition = string(1, toColLetter) + to_string(toRow + 1);
            logMove(fromPosition, toPosition);
            displayMoveLog();

            gameBoard.showBoard(); // Show the updated board state after the move
            switchTurn(); // Move to the next player's turn
        }
        else {
            cout << "Failed to execute move. Please try again.\n";
        }
    }
    else {
        cout << "Invalid move. Please try again.\n";
    }
}



void Round::continueComputerTurn() {
    // Display current game state and announce the computer's turn
    cout << "Resuming the computer's turn...\n";
    gameBoard.showBoard();
    cout << "It's the computer's turn, " << currentPlayer->getName() << ".\n";

    // Assuming the ComputerPlayer class has a method to generate and select a move
    auto compPlayer = std::dynamic_pointer_cast<ComputerPlayer>(currentPlayer);
    if (!compPlayer) {
        std::cerr << "Error: Current player is not a computer player as expected.\n";
        return;
    }

    // Generate all possible moves for the computer player
    compPlayer->generateAllPossibleMoves(gameBoard);

    // Select and execute one of the generated moves
    auto moveDetails = compPlayer->selectAndExecuteMove(gameBoard, compPlayer->getPieceType());

    // Check if a valid move was returned and executed
    if (!moveDetails.first.empty() && !moveDetails.second.empty()) {
        // Log the move
        logMove(moveDetails.first, moveDetails.second);
        displayMoveLog(); // Optionally display the move log to see all moves made so far

        cout << "Computer moved from " << moveDetails.first << " to " << moveDetails.second << ".\n";
    }
    else {
        // If no valid move could be made, handle accordingly (this may depend on your game's rules)
        std::cerr << "Computer player unable to make a valid move.\n";
    }

    // Show the updated board state after the computer's move
    gameBoard.showBoard();

    // Switch turn to the next player
    switchTurn();
}


