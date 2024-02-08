#include "ComputerPlayer.h"
#include <iostream>
#include <string>

ComputerPlayer::ComputerPlayer(const std::string& name) : Player(name) {}

void ComputerPlayer::askPlayer() {
    // For a computer player, this might set a default name or generate one.
    playerName = "AI_" + playerName; // Example of setting a computer player's name.
}

void ComputerPlayer::selectPiece(char row, int col) {
    // AI logic to select a piece. Placeholder example:
    piece = std::make_pair(row, col); // This would be determined by the AI's strategy.
}

void ComputerPlayer::setDestination(char row, int col) {
    // AI logic to set a destination. Placeholder example:
    destination = std::make_pair(row, col); // This would be determined by the AI's strategy.
}

std::pair<char, int> ComputerPlayer::getSelectedPiece() const {
    return piece;
}

std::pair<char, int> ComputerPlayer::getDestination() const {
    return destination;
}

std::string ComputerPlayer::properNotation(std::pair<int, int> position) const {
    // Adjust the conversion if your indexing starts from 0 or 1 accordingly
    return std::string(1, static_cast<char>('A' + position.first)) + std::to_string(position.second + 1);
}
