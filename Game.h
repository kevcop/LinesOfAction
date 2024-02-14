#pragma once
#ifndef GAME_H
#define GAME_H
#define PLAYER_h
#include "Player.h"
#include "board.h"
#include <iostream>
#include <utility>
#include "Rules.h"

using namespace std;

class Game {
private:
	//pointers to the players
	Player *player1; 
	Player *player2;
	Player *currentPlayer;


	Board gameBoard; //board 
	bool isPlayer1Turn; //player turns
	pair <char, int> destination; //location
	Rules rules; //object of rules class to validate

public:
	//initialize game with two players
	Game(Player* p1, Player* p2);

	//void setPlayerNames(const string& player1Name, const string& player2Name);
	void coinToss(); //determine who goes first
	//switch player turn
	void switchTurn();
	//logic of a turn
	void playerTurn();
	//handles movement
	void playerMove();
	//select a piece
	void promptMove();
	//select a location
	void promptDestination();
	//return selected piece
	pair<char, int> getDestination()const {
		return destination;
	}
	//record move just made
	void logMove(const string& from, const string& to);
	//record all moves
	void displayMoveLog() const;
	//ask for destination 
	void promptPieceLocation(string& locationDescription);
	//used for proper column identifying 
	int translateColumn(char columnLetter);
	
};
#endif // !GAME_H
