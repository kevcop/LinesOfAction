#include "Game.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "board.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <utility>

using namespace std;

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
    }
    else {
        currentPlayer = player2;
        std::cout << "Player " << player2->getName() << " wins the coin toss and will go second.\n";
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
    std::cout << currentPlayer->getName() << ", select a piece to move (row A-H, column 1-8): ";
    char row;
    int col;
    std::cin >> row >> col;
    currentPlayer->selectPiece(row, col - '0'); // Assuming col is entered as a number, adjust if necessary
}

void Game::promptDestination() {
    std::cout << currentPlayer->getName() << ", select a destination for the piece (row A-H, column 1-8): ";
    char row;
    int col;
    std::cin >> row >> col;
    currentPlayer->setDestination(row, col - '0'); // Adjust as needed
}

void Game::playerTurn() {
    std::string from, to;
    std::cout << currentPlayer->getName() << ", enter your move from (e.g., A6): ";
    std::cin >> from;
    std::cout << "Enter your move to (e.g., B6): ";
    std::cin >> to;

    auto [startRow, startCol] = parseInput(from); // Ensure parseInput is correctly implemented
    auto [endRow, endCol] = parseInput(to);

    if (startRow != -1 && startCol != -1 && endRow != -1 && endCol != -1) {
        if (gameBoard.movePiece(startRow, startCol, endRow, endCol,currentPlayer->getPieceType())) {
            std::cout << "Move successful.\n";
        }
        else {
            std::cout << "Invalid move. Try again.\n";
        }
    }
    else {
        std::cout << "Invalid input format.\n";
    }

    switchTurn(); // Assuming switchTurn correctly changes the currentPlayer
}


// Define parseInput function if not already defined
//std::pair<int, int> parseInput(const std::string& input) {
//    // Implementation as discussed previously
//}

std::pair<int, int> Game::parseInput(const std::string& input) const {
    if (input.length() != 2) {
        return { -1, -1 }; // Invalid input format
    }

    int col = toupper(input[0]) - 'A'; // Convert column letter to index (0-7 for A-H)
    int row = 8 - (input[1] - '0'); // Convert row number to index (0-7 for 1-8, assuming top-down numbering)

    // Validate row and column indices are within board bounds
    if (row >= 0 && row < 8 && col >= 0 && col < 8) {
        return { row, col };
    }
    else {
        return { -1, -1 }; // Return an invalid position if out of bounds
    }
}

// Additional methods...
