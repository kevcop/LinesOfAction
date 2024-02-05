#include "player.h"
#include <iostream>
using namespace std;

 Player::Player() {
	 //askPlayer();
	 //cout << "Player " << playerName<<" has joined the game.\n";
}

 void Player::askPlayer() {
	 cout << "Enter name\n";
	 cin >> playerName;
 }

 string Player::getName() const {
	 return playerName;
 }

 void Player::setPlayerName(const string& name) {
	 playerName = name;
 }