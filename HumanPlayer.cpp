#include "HumanPlayer.h"
#include <iostream>
using namespace std;

//constructor for name 
HumanPlayer::HumanPlayer(const string& name) : Player(name) {}

//prompt user to enter name
void HumanPlayer::askPlayer() {
    cout << "Enter your name: ";
    cin >> playerName;
}
// keep track of chosen piece
void HumanPlayer::selectPiece(char row, int col) {
    piece = std::make_pair(row, col);
}
// establish desired location
void HumanPlayer::setDestination(char row, int col) {
    destination = std::make_pair(row, col);
}
// return piece selected
pair<char, int> HumanPlayer::getSelectedPiece() const {
    return piece;
}
// return desired location
pair<char, int> HumanPlayer::getDestination() const {
    return destination;
}
// trying to mimic chess notation
std::string HumanPlayer::properNotation(std::pair<int, int> position) const {
    return std::string(1, static_cast<char>('A' + position.first)) + std::to_string(position.second + 1);
}
