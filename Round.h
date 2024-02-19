#pragma once
#ifndef Round_H
#define Round_H
#define PLAYER_h
#include "Player.h"
#include "board.h"
#include <iostream>
#include <utility>
#include "Rules.h"
#include "Tournament.h"

using namespace std;

class Round {
private:
	//pointers to the players
	Player* player1;
	Player* player2;
	Player* currentPlayer;


	Board gameBoard; //board 
	bool isPlayer1Turn; //player turns
	int player1Score;
	int player2Score;
	Player* winner;
	pair <char, int> destination; //location
	Rules rules; //object of rules class to validate

	bool skipCoinToss;

public:
	//initialize game with two players
	Round(Player* p1, Player* p2);

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
	//method for handling run of game
	void startGame();


	//NEW FEATURES

	void updateScores(); // Update scores after a round
	int calculateScore() const; // Calculate the score for the round
	bool checkRoundOver() const; // Check if the round is over
	void determineWinner(); // Determine the winner of the round and update scores

	bool checkConnectedGroup(char color) const; // New function to check if all pieces of one color are connected
	void DFS(int row, int col, char color, std::vector<std::vector<bool>>& visited) const; // Utility function for DFS traversal
	bool isSafe(int row, int col, char color, std::vector<std::vector<bool>>& visited) const; // Check if a cell can be included in DFS


	int getPlayer1Score() {
		return player1Score;
	}

	int getPlayer2Score() {
		return player2Score;
	}

	Player* getRoundWinner() const {
		return winner;
	}

	void startGameWithoutCoinToss();
	void setStartingPlayer(Player* startingPlayer);
};


#endif // !GAME_H
