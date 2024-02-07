#include "HumanPlayer.h"
#include <iostream>

HumanPlayer::Human(const std::string& name) : Player(name) {}

void HumanPlayer::askPlayer() {
    std::cout << "Enter your name: ";
    std::cin >> playerName;
}

void HumanPlayer::selectPiece(char row, int col) {
    piece = { row, col };
}

void HumanPlayer::setDestination(char row, int col) {
    destination = { row, col };
}

std::pair<char, int> HumanPlayer::getSelectedPiece() const {
    return piece;
}

std::pair<char, int> HumanPlayer::getDestination() const {
    return destination;
}

std::string HumanPlayer::properNotation(std::pair<int, int> position) const {
    return std::string(1, position.first + 'A') + std::to_string(position.second + 1);
}
