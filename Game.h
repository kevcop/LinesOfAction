#pragma once
#ifndef GAME_H
#define GAME_H
#define PLAYER_h
#include "Player.h"
#include <iostream>
#include <utility>

using namespace std;

class Game {
private:
	Player *player1;
	Player *player2;
	Player *currentPlayer;
	bool isPlayer1Turn;
	pair <char, int> destination;
public:
	Game(Player* p1, Player * p2):player1(p1),player2(p2),currentPlayer(nullptr){}
	void setPlayerNames(const string& player1Name, const string& player2Name);
	void coinToss();

	void switchTurn();
	void displayPlayerJoin(const Player& player);

	void playerMove();
	void promptMove();
	void promptDestination();
	pair<char, int> getDestination()const {
		return destination;
	}
};
#endif // !GAME_H
