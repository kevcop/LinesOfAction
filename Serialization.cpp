#include "serialization.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include <fstream>
#include <iostream>
#include <sstream>
// Include other necessary headers

void Serialization::saveGameState(const Board& board, const Player& player1, const Player& player2, bool isPlayer1Turn, int player1Score, int player2Score) {
    std::ofstream outFile("gameState.txt");
    if (!outFile) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    // Save board state
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            outFile << board.getPieceAt(row, col) << (col < 8 - 1 ? "," : "");
        }
        outFile << "\n";
    }

    // Save player details: piece type, scores
    outFile << player1.getPieceType() << "," << player1Score << "\n";
    outFile << player2.getPieceType() << "," << player2Score << "\n";

    // Save current round number and who's turn it is
    outFile << isPlayer1Turn << "\n";

    outFile.close();
}

bool Serialization::loadGameState(Board& board, HumanPlayer& humanPlayer, ComputerPlayer& computerPlayer, bool& isPlayer1Turn) {
    std::ifstream inFile("gameState.txt");
    if (!inFile) {
        std::cerr << "Error opening file for reading.\n";
        return false;
    }

    std::string line;
    // Skip the "Board:" line
    std::getline(inFile, line);

    // Load board state
    for (int row = 0; row < 8 && std::getline(inFile, line); ++row) {
        for (int col = 0, pos = 0; col < 8 && pos < line.length(); ++col, pos += 2) { // Assume 2 characters per cell including space
            char pieceType = line[pos];
            board.setPieceAt(row, col, pieceType); // Set the piece on the board
        }
    }

    // Skipping to "Human:" section
    while (std::getline(inFile, line) && line != "Human:") {}
    // Read human player details
    std::getline(inFile, line); // "Rounds won: X"
    humanPlayer.setRoundsWon(extractValue(line)); // Assuming a method to set rounds won
    std::getline(inFile, line); // "Score: Y"
    humanPlayer.setScore(extractValue(line)); // Assuming a method to set score

    // Skipping to "Computer:" section
    while (std::getline(inFile, line) && line != "Computer:") {}
    // Read computer player details
    std::getline(inFile, line); // "Rounds won: X"
    computerPlayer.setRoundsWon(extractValue(line));
    std::getline(inFile, line); // "Score: Y"
    computerPlayer.setScore(extractValue(line));

    // Read next player and color
    std::getline(inFile, line); // "Next player: PlayerName"
    std::string nextPlayer = line.substr(line.find(':') + 2);
    std::getline(inFile, line); // "Color: Color"
    char color = line.substr(line.find(':') + 2)[0];

    // Determine whose turn it is based on the next player and color
    isPlayer1Turn = (nextPlayer == "Human" && humanPlayer.getPieceType() == color) || (nextPlayer == "Computer" && computerPlayer.getPieceType() == color);

    inFile.close();
    return true;
}

// Helper function to extract integer values from strings
int Serialization::extractValue(const std::string& line) {
    size_t pos = line.find_last_of(' ');
    if (pos != std::string::npos) {
        return std::stoi(line.substr(pos + 1));
    }
    return 0; // Default case
}


