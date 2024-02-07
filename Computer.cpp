#include "ComputerPlayer.h"
#include <iostream>

ComputerPlayer::Computer(const std::string& name) : Player(name) {}

void ComputerPlayer::askPlayer() {
    // For a computer player, this might set a default name or generate one.
    playerName = "AI_" + playerName; // Example of setting a computer player's name.
}

void ComputerPlayer::selectPiece(char row, int col) {
    // AI logic to select a piece. Placeholder example:
    piece = { row, col }; // This would be determined by the AI's strategy.
}

void ComputerPlayer::setDestination(char row, int col) {
    // AI logic to set a destination. Placeholder example:
    destination = { row, col }; // This would be determined by the AI's strategy.
}

std::pair<char, int> ComputerPlayer::getSelectedPiece() const {
    return piece;
}

std::pair<char, int> ComputerPlayer::getDestination() const {
    return destination;
}

std::string ComputerPlayer::properNotation(std::pair<int, int> position) const {
    return std::string(1, position.first + 'A') + std::to_string(position.second + 1);
}
