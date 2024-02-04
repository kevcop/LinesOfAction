#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
using namespace std;

class Player {
private:
	string playerName;
	char colorSelect;
	int turn;
public:
	int age;
	Player();
	void askPlayer();
	string getName() const;
	bool operator==(const Player& test) const {
		return playerName == test.playerName;
	}
};

#endif // !PLAYER_H

