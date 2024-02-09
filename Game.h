#pragma once
#ifndef GAME_H
#define GAME_H
#define PLAYER_h
#include "Player.h"
#include "board.h"
#include <iostream>
#include <utility>

using namespace std;

class Game {
private:
	Player *player1;
	Player *player2;
	Player *currentPlayer;
	Board gameBoard;
	bool isPlayer1Turn;
	pair <char, int> destination;
	//pair<int, int> parseInput(const string& input) const;

public:
	Game(Player* p1, Player* p2);
	void setPlayerNames(const string& player1Name, const string& player2Name);
	void coinToss();

	void switchTurn();

	void playerTurn();
	void displayPlayerJoin(const Player& player);

	void playerMove();
	void promptMove();
	void promptDestination();
	pair<char, int> getDestination()const {
		return destination;
	}
	void logMove(const string& from, const string& to);
	void displayMoveLog() const;

	void promptPieceLocation(string& locationDescription);
	int translateColumn(char columnLetter);
	
};
#endif // !GAME_H
