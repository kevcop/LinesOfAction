#include "Game.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "board.h"
#include "Round.h"
#include "Tournament.h"
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
Round::Round(Player* p1, Player* p2) : player1(p1), player2(p2), currentPlayer(nullptr), isPlayer1Turn(true),player1Score(0), player2Score(0), winner(nullptr) {
    srand(static_cast<unsigned int>(time(nullptr))); // seed
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
// handles the move logic and validates
void Round::playerTurn() {
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

    //ask for location
    cout << "Select a destination for the piece." << endl;
    cout << "Column (A-H): ";
    cin >> toColLetter;
    cout << "Row (1-8): ";
    cin >> toRow;


    int toCol = toupper(toColLetter) - 'A';
    toRow -= 1;
    vector<pair<int, int>> capturePositions;

    // validation checks
    if (rules.isValidMove(gameBoard, *currentPlayer, fromRow, fromCol, toRow, toCol) &&
        rules.isPathClear(gameBoard, fromRow, fromCol, toRow, toCol, currentPlayer->getPieceType(), capturePositions) &&
        rules.isValidEndingPosition(gameBoard, toRow, toCol, currentPlayer->getPieceType())) {

        // execute the move
        gameBoard.movePiece(fromRow, fromCol, toRow, toCol, currentPlayer->getPieceType());

        // record move
        string fromPosition = fromColLetter + to_string(fromRow + 1);
        string toPosition = toColLetter + to_string(toRow + 1);
        logMove(fromPosition, toPosition);
        displayMoveLog();

        cout << "Move successful." << endl;

        gameBoard.showBoard();
    }
    else {
        cout << "Invalid move. Please try again." << endl;
        return; // dont want to switch turns if invalid move
    }

    switchTurn(); //next player's turn
}

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
//START GAME REVISED

//void Round::startGame(Player * startingPlayer = nullptr) {
//    if (startingPlayer != nullptr) {
//        currentPlayer = startingPlayer;
//    }
//    else
//    {
//        coinToss()
//    }
//    if (performCoinToss) {
//        coinToss();
//    }
//    // Initial setup, such as deciding who goes first
//    coinToss(); // This method decides who starts and sets `currentPlayer` accordingly
//
//     Main game loop
//    bool gameOver = false;
//    while (!gameOver) {
//        gameBoard.showBoard(); // Display the board at the start of each turn
//        playerTurn(); // Conduct the current player's turn
//
//         Check if all pieces of one color are connected after each turn
//        bool blackConnected = checkConnectedGroup('B');
//        bool whiteConnected = checkConnectedGroup('W');
//
//        if (blackConnected || whiteConnected) {
//             If any color's pieces are all connected, the round is considered over
//            determineWinner(); // Determine and announce the winner based on the game state
//            updateScores(); // Update the scores based on this round's outcome
//
//            gameOver = true; // Mark the game as over
//            cout << "Round over!" << endl;
//             Here, you might want to prompt for another round or end the game session
//        }
//         No need to switch turns here, as it's already handled at the end of playerTurn()
//    }
//
//    gameBoard.showBoard();
//    cout << "Game over!" << endl;
//     Additional end-of-game logic could be placed here if needed
//}


//void Round::startGame() {
//    // Initial setup, such as deciding who goes first
//    coinToss(); // This method decides who starts and sets `currentPlayer` accordingly
//
//    // Main game loop
//    bool gameOver = false;
//    while (!gameOver) {
//        gameBoard.showBoard(); // Display the board at the start of each turn
//        playerTurn(); // Conduct the current player's turn
//
//        if (checkRoundOver()) {
//            determineWinner(); // Determine and announce the winner
//            updateScores(); // Update the scores based on this round's outcome
//            gameOver = true; // Mark the game as over
//        }
//        // The turn switch is now handled at the end of playerTurn()
//    }
//
//    gameBoard.showBoard();
//    cout << "Game over!" << endl;
//    // Additional end-of-game logic could be placed here if needed
//}

void Round::startGame() {
    // Initial setup, such as deciding who goes first
    coinToss(); // This method decides who starts and sets `currentPlayer` accordingly

    // Main game loop
    bool gameOver = false;
    while (!gameOver) {
        gameBoard.showBoard(); // Display the board at the start of each turn
        playerTurn(); // Conduct the current player's turn

        // Check if all pieces of one color are connected after each turn
        bool blackConnected = checkConnectedGroup('B');
        bool whiteConnected = checkConnectedGroup('W');

        if (blackConnected || whiteConnected) {
            // If any color's pieces are all connected, the round is considered over
            determineWinner(); // Determine and announce the winner based on the game state
            updateScores(); // Update the scores based on this round's outcome

            gameOver = true; // Mark the game as over
            cout << "Round over!" << endl;
            // Here, you might want to prompt for another round or end the game session
        }
        // No need to switch turns here, as it's already handled at the end of playerTurn()
    }

    gameBoard.showBoard();
    cout << "Game over!" << endl;
    // Additional end-of-game logic could be placed here if needed
}


    // Game has ended, display final board state and any concluding messages


void Round::updateScores() {
    auto [blackCount, whiteCount] = gameBoard.countPiecesByColor();

    // Assuming player1 is always black and player2 is white for this example
    int piecesPlayer1 = (player1->getPieceType() == 'B') ? blackCount : whiteCount;
    int piecesPlayer2 = (player2->getPieceType() == 'B') ? blackCount : whiteCount;

    // Update scores based on the difference in the number of pieces
    player1Score += piecesPlayer1 - piecesPlayer2;
    player2Score += piecesPlayer2 - piecesPlayer1;
}

int Round::calculateScore() const {
    auto [blackCount, whiteCount] = gameBoard.countPiecesByColor();

    // Example calculation - adjust based on your scoring logic
    int piecesPlayer1 = (player1->getPieceType() == 'B') ? blackCount : whiteCount;
    int piecesPlayer2 = (player2->getPieceType() == 'B') ? blackCount : whiteCount;

    return piecesPlayer1 - piecesPlayer2;
}

bool Round::checkRoundOver() const {
    // Placeholder logic - adjust according to when you consider a round to be over
    // For example, check if all pieces of a player are connected or if a player has no moves left
    // NOTE: You'll need to implement logic to check for game over conditions, such as all pieces connected.
    // This is a placeholder and the actual implementation may vary.
   // return gameBoard.isGameOver(); // Assuming Board has an isGameOver method to check the condition
    return false;
}


void Round::determineWinner() {
    // Check if all pieces of one color are connected for both players
    bool player1Connected = checkConnectedGroup(player1->getPieceType());
    bool player2Connected = checkConnectedGroup(player2->getPieceType());

    if (player1Connected && !player2Connected) {
        std::cout << player1->getName() << " wins this round!" << std::endl;
        winner = player1;
    }
    else if (!player1Connected && player2Connected) {
        std::cout << player2->getName() << " wins this round!" << std::endl;
        winner = player2;
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
    updateScores();
}
//void Round::determineWinner() {
//    auto [blackCount, whiteCount] = gameBoard.countPiecesByColor();
//
//    // Assuming player1 is always black and player2 is white for simplicity in this example
//    int piecesPlayer1 = (player1->getPieceType() == 'B') ? blackCount : whiteCount;
//    int piecesPlayer2 = (player2->getPieceType() == 'B') ? blackCount : whiteCount;
//
//    if (piecesPlayer1 > piecesPlayer2) {
//        std::cout << player1->getName() << " wins this round!" << std::endl;
//        winner = player1;
//    }
//    else if (piecesPlayer2 > piecesPlayer1) {
//        std::cout << player2->getName() << " wins this round!" << std::endl;
//        winner = player2;
//    }
//    else {
//        std::cout << "This round is a draw." << std::endl;
//        winner = nullptr; // No winner in case of a draw
//    }
//
//    // Update scores after determining the winner
//    updateScores();
//}

//ALGO APPROACH

// Constructor and other methods of Round class...

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

void Round::startGameWithoutCoinToss() {
    // Assume currentPlayer has already been set based on the outcome of the previous round
    // or another rule specific to your game's tournament structure.

    // Main game loop remains the same as in startGame
    bool gameOver = false;
    while (!gameOver) {
        gameBoard.showBoard(); // Display the board at the start of each turn
        playerTurn(); // Conduct the current player's turn

        // Here, we include the same logic to check if the round is over
        // and to determine the winner, as in your original startGame method.
        if (checkRoundOver()) {
            determineWinner(); // Determine and announce the winner
            updateScores(); // Update the scores based on this round's outcome
            gameOver = true; // Mark the game as over
        }
        // The turn switch is handled at the end of playerTurn()
    }

    gameBoard.showBoard();
    std::cout << "Game over!" << std::endl;
    // Additional end-of-game logic could be placed here if needed
}
#include "Round.h"

// Constructor and other Round methods...

void Round::setStartingPlayer(Player* startingPlayer) {
    currentPlayer = startingPlayer;
    // Determine if it is player 1's turn based on the starting player
    isPlayer1Turn = (currentPlayer == player1);

    // Optionally, adjust game setup based on the starting player
    // For example, if you have game state that depends on who starts
}

// Rest of the Round class definition...
