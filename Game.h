#pragma once
#ifndef GAME_H
#define GAME_H
#define PLAYER_h
#include "Player.h"
#include <iostream>

using namespace std;

class Game {
private:
	Player p1;
	Player p2;
	Player *currrentPlayerTurn;
	bool isPlayer1Turn;
public:
	Game();
	void setPlayerNames(const string& player1Name, const string& player2Name);
	void coinToss(const string& player1Name, const string& player2Name);

	void switchTurn();
	void displayPlayerJoin(const Player& player);
};
#endif // !GAME_H
