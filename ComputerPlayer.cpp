#include "ComputerPlayer.h"
#include <iostream>
#include <string>

using namespace std; 
ComputerPlayer::ComputerPlayer(const string& name) : Player(name) {}

void ComputerPlayer::askPlayer() {
    //getting computer name but it is not needed DELETE MAYBE
    playerName = "AI" + playerName; 
}

//choose piece
void ComputerPlayer::selectPiece(char row, int col) {
    piece = make_pair(row, col); 
}
//choose destination
void ComputerPlayer::setDestination(char row, int col) {
    destination =   make_pair(row, col); 
}
// return piece selected
  pair<char, int> ComputerPlayer::getSelectedPiece() const {
    return piece;
}
  // return destination
  pair<char, int> ComputerPlayer::getDestination() const {
    return destination;
}
  // trying to mimic chess notation
  string ComputerPlayer::properNotation(std::pair<int, int> position) const {
    return std::string(1, static_cast<char>('A' + position.first)) + std::to_string(position.second + 1);
}
