#include "Game.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "board.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <map>
#include <vector>
using namespace std;
vector<string> moveLog;
std::map<char, int> colToIndex = {
    {'A', 0}, {'B', 1}, {'C', 2}, {'D', 3},
    {'E', 4}, {'F', 5}, {'G', 6}, {'H', 7}
};


// Constructor
//Game::Game(Player* p1, Player* p2) : player1(p1), player2(p2), currentPlayer(nullptr), isPlayer1Turn(false) {
//    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed random once per game start
//}
Game::Game(Player* p1, Player* p2) : player1(p1), player2(p2), currentPlayer(nullptr), isPlayer1Turn(true) {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed random
    gameBoard.resetBoard(); // Initialize the board
}

void Game::coinToss() {
    std::cout << "Enter 1 for heads or 2 for tails.\n";
    int userChoice;
    std::cin >> userChoice;
    int toss = std::rand() % 2 + 1; // Generates a random number, either 1 or 2

    if (userChoice == toss) {
        currentPlayer = player1;
        std::cout << "Player " << player1->getName() << " wins the coin toss and will go first.\n";
        player1->setPieceType('B');
        player2->setPieceType('W');
    }
    else {
        currentPlayer = player2;
        std::cout << "Player " << player2->getName() << " wins the coin toss and will go first.\n";
        player2->setPieceType('B');
        player1->setPieceType('W');
    }
}

void Game::switchTurn() {
    if (currentPlayer == player1) {
        currentPlayer = player2;
    }
    else {
        currentPlayer = player1;
    }
    std::cout << "It's now " << currentPlayer->getName() << "'s turn.\n";
}

void Game::playerMove() {
    promptMove();
    promptDestination();
    std::cout << "Player " << currentPlayer->getName() << " moves piece from "
        << currentPlayer->properNotation(currentPlayer->getSelectedPiece())
        << " to " << currentPlayer->properNotation(currentPlayer->getDestination()) << std::endl;
    switchTurn();
}

void Game::promptMove() {
    std::string from, to;
    std::cout << currentPlayer->getName() << ", it's your turn." << std::endl;
    std::cout << "Enter your move from (e.g., A6): ";
    std::cin >> from;
    std::cout << "Enter move to (e.g., B6): ";
    std::cin >> to;

    // Convert inputs using the map
    int fromCol = colToIndex[toupper(from[0])];
    int fromRow = from[1] - '1'; // Assuming row input is 1-8, adjust to 0-based index
    int toCol = colToIndex[toupper(to[0])];
    int toRow = to[1] - '1';

    // Assuming Board class has a method to execute move
    if (gameBoard.movePiece(fromRow, fromCol, toRow, toCol, currentPlayer->getPieceType())) {
        logMove(from, to);
    }
    else {
        std::cout << "Invalid move. Please try again." << std::endl;
    }
}



void Game::promptDestination() {
    char colLetter;
    int row;
    cout << currentPlayer->getName() << ", select a destination for the piece." << endl;
    cout << "Column (A-H): ";
    cin >> colLetter;
    cout << "Row (1-8): ";
    cin >> row;

    // Convert column letter to index
    int col = toupper(colLetter) - 'A';
    if (col >= 0 && col < 8 && row >= 1 && row <= 8) {
        currentPlayer->setDestination(row - 1, col); // Adjust row to 0-based index
    }
    else {
        cout << "Invalid input. Please try again." << endl;
    }
}


//void Game::playerTurn() {
//    bool moveSuccessful = false;
//    while (!moveSuccessful) {
//        std::string from, to;
//        std::cout << currentPlayer->getName() << ", it's your turn. " << std::endl;
//        std::cout << "Enter your move (e.g., A6 to B6): ";
//        std::cin >> from >> to;
//
//        auto [startRow, startCol] = parseInput(from);
//        auto [endRow, endCol] = parseInput(to);
//
//        // Check for valid input before attempting to move
//        if (startRow != -1 && startCol != -1 && endRow != -1 && endCol != -1) {
//            moveSuccessful = gameBoard.movePiece(startRow, startCol, endRow, endCol, currentPlayer->getPieceType());
//            if (!moveSuccessful) {
//                std::cout << "Invalid move. Please try again." << std::endl;
//            }
//        }
//        else {
//            std::cout << "Invalid input format. Please use the format 'A6 to B6'." << std::endl;
//        }
//    }
//
//    switchTurn(); // Move to next player's turn
//}
// Inside Game.h or Game.cpp, depending on your structure

void Game::playerTurn() {
    std::string fromLocation, toLocation;

    std::cout << currentPlayer->getName() << ", it's your turn." << std::endl;

    // Prompt for current location of the piece
    std::cout << "Select a piece to move." << std::endl;
    promptPieceLocation(fromLocation);

    // Prompt for destination
    std::cout << "Select a destination for the piece." << std::endl;
    promptPieceLocation(toLocation);

    // Process the move
    int fromCol = fromLocation[0] - '0';
    int fromRow = fromLocation[1] - '0';
    int toCol = toLocation[0] - '0';
    int toRow = toLocation[1] - '0';

    logMove(fromLocation, toLocation);

    displayMoveLog();
    //if (gameBoard.movePiece(fromRow, fromCol, toRow, toCol, currentPlayer->getPieceType())) {
    //    std::cout << "Move successful." << std::endl;
    //    // Optionally log the move here
    //}
    //else {
    //    std::cout << "Invalid move. Please try again." << std::endl;
    //}

    // Assuming you have a method to switch turns

    switchTurn();
}



// Define parseInput function if not already defined
//std::pair<int, int> parseInput(const std::string& input) {
//    // Implementation as discussed previously
//}

//pair<int, int> Game::parseInput(const std::string& input) const {
//    //if (input.length() != 2) {
//    //    return { -1, -1 }; // Invalid format
//    //}
//
//    //auto colIt = columnMap.find(toupper(input[0])); // Find the column in the map
//    //int row = input[1] - '1'; // Convert row from '1'-'8' to 0-7
//
//    //if (colIt != columnMap.end() && row >= 0 && row < 8) {
//    //    return { row, colIt->second }; // Return the row and the found column index
//    //}
//    //else {
//    //    return { -1, -1 }; // Out of bounds or invalid column
//    //}
//    return 0;
//}
//void Game::logMove(const std::string& from, const std::string& to) {
//    std::string moveSummary = currentPlayer->getName() + " moves from " + from + " to " + to;
//    moveLog.push_back(moveSummary);
//}
void Game::logMove(const std::string& from, const std::string& to) {
    // Assuming from and to are in the format "colIndexRowIndex"
    int fromColIndex = std::stoi(from.substr(0, 1));
    int fromRowIndex = std::stoi(from.substr(1, 1)) + 1; // Adjust for user-friendly display
    int toColIndex = std::stoi(to.substr(0, 1));
    int toRowIndex = std::stoi(to.substr(1, 1)) + 1; // Adjust for user-friendly display

    // Convert column index back to letter
    char fromColLetter = 'A' + fromColIndex;
    char toColLetter = 'A' + toColIndex;

    std::string moveSummary = currentPlayer->getName() + " moves from " + fromColLetter + std::to_string(fromRowIndex) + " to " + toColLetter + std::to_string(toRowIndex);
    moveLog.push_back(moveSummary);
}



void Game::displayMoveLog() const {
    cout << "Move Log:" << endl;
    for (const auto& move : moveLog) {
        cout << move << endl;
    }
}

void Game::promptPieceLocation(std::string& locationDescription) {
    char column;
    int row;
    std::cout << "Enter column (A-H): ";
    std::cin >> column;
    std::cout << "Enter row (1-8): ";
    std::cin >> row;

    int colIndex = translateColumn(toupper(column)); // Ensure uppercase for map access
    locationDescription = std::to_string(colIndex) + std::to_string(row - 1); // Store as "colIndexRowIndex"
}

int Game::translateColumn(char columnLetter) {
    if (colToIndex.find(columnLetter) != colToIndex.end()) {
        return colToIndex[columnLetter];
    }
    return -1; // Indicate invalid input
}

// Additional methods...
