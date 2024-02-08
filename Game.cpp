#include "Game.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Constructor
//Game::Game(Player* p1, Player* p2) : player1(p1), player2(p2), currentPlayer(nullptr), isPlayer1Turn(false) {
//    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed random once per game start
//}

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

// Additional methods...
