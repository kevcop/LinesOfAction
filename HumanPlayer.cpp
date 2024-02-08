#include "HumanPlayer.h"
#include <iostream>
#include <string> // This include is actually redundant because string is included in HumanPlayer.h

HumanPlayer::HumanPlayer(const std::string& name) : Player(name) {}

void HumanPlayer::askPlayer() {
    std::cout << "Enter your name: ";
    std::cin >> playerName;
}

void HumanPlayer::selectPiece(char row, int col) {
    piece = std::make_pair(row, col);
}

void HumanPlayer::setDestination(char row, int col) {
    destination = std::make_pair(row, col);
}

std::pair<char, int> HumanPlayer::getSelectedPiece() const {
    return piece;
}

std::pair<char, int> HumanPlayer::getDestination() const {
    return destination;
}

std::string HumanPlayer::properNotation(std::pair<int, int> position) const {
    // Assuming the row is represented by 'position.first' and column by 'position.second'
    // Adjust the conversion if your indexing starts from 0 or 1 accordingly
    return std::string(1, static_cast<char>('A' + position.first)) + std::to_string(position.second + 1);
}
