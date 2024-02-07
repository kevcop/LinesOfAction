#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <utility>
using namespace std;

class Player {
private:
	string playerName;
	char colorSelect;
	int turn;
	pair<char, int> piece;
	pair<char, int> destination;
public:
	Player();
	explicit Player(const string& name);
	void setPlayerName(const string& name);//setter
	void askPlayer();
	string getName() const;
	bool operator==(const Player& test) const { //assists with checking whose turn it is
		return playerName == test.playerName;
	}
	//movement related
	void selectPiece(char row, int col);
	void setDestination(char row, int col);
	pair<char, int> getSelectedPiece() const;
	pair<char, int> getDestination() const;
	string properNotation(pair<int, int> position) const;
};

#endif // !PLAYER_H

