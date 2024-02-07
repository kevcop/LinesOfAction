#include "Game.h"
#include "Player.h"
#include <iostream>
using namespace std;

//Game::Game(Player p1, Player p2): p1(p1), p2(p2) {
//	//coinToss();
//}
Game::Game() : isPlayer1Turn(false),currrentPlayerTurn(nullptr) {

}
void Game::setPlayerNames(const string &player1Name, const string &player2Name) {
	p1.setPlayerName(player1Name);
	p2.setPlayerName(player2Name);
	cout << "Player 1 :" << p1.getName() << "\n";
	cout << "Player 2 :" << p2.getName() << "\n";

	currrentPlayerTurn = &p1;


}
void Game::coinToss(const string& player1Name, const string& player2Name)
{
	int userChoice;
	int firstTurn;
	int toss;
	cout << "Enter 1 for heads or 2 for tails.\n";
	cin >> userChoice;
	toss = rand() % 2 + 1;
	if ((userChoice == toss)) {
		cout << "player " << player1Name << "wins the coin toss and will go first\n";
		currrentPlayerTurn->setPlayerName(player1Name);
	}
	else {
		cout << "Player " << player2Name << "wins the coin toss and will go first.\n";
		currrentPlayerTurn->setPlayerName(player2Name);
	}
	/*if ((userChoice == 1 and toss == 1) || (userChoice == 2 && toss == 2)) {
		cout << "Player " << p1.getName() << " wins the coin toss and will go first\n";
		currrentPlayerTurn = p1;
	}
	else
	{
		cout << "Player " << p2.getName() << " wins the coin toss and will go first\n";
		currrentPlayerTurn = p2;
	}
	cout << "Player " << currrentPlayerTurn.getName() << "goes first\n";*/
}
//void Game::switchTurn() {
//	if (currrentPlayerTurn==p1)
//	{
//		currrentPlayerTurn = p2;
//	}
//	else {
//		currrentPlayerTurn = p1;
//	}
//	cout << "It's " << currrentPlayerTurn.getName() << "'s turn!\n";
//}
void Game::displayPlayerJoin(const Player& player) {
	cout << "Player " << player.getName() << " has joined the game.\n";

	cout << "Player " << p1.getName() << "has joined\n";
}
//player pointer, computer and human classes

void Game::playerMove() {
	promptMove();
	promptDestination();
	//cout << "Player " << currrentPlayerTurn->getName() << "moves piece from " << currrentPlayerTurn->properNotation(currrentPlayerTurn->getSelectedPiece()) << "to" << currrentPlayerTurn->properNotation(currrentPlayerTurn->getDestination()) << endl;
	//cout << "Player " << currrentPlayerTurn->getName() << " moves piece from " << currrentPlayerTurn->getSelectedPiece().first <<currrentPlayerTurn->getSelectedPiece().second<< "to " << currrentPlayerTurn->getDestination().first <<currrentPlayerTurn->getDestination().second<< endl;
	//cout << "Player " << currrentPlayerTurn->getName() << " moves piece from " << currrentPlayerTurn->getSelectedPiece().first << currrentPlayerTurn->getSelectedPiece().second << " to " << currrentPlayerTurn->properNotation(currrentPlayerTurn->getDestination()) << endl;
	cout << "Player " << currrentPlayerTurn->getName() << " moves piece from " << currrentPlayerTurn->properNotation(currrentPlayerTurn->getSelectedPiece()) << " to " << currrentPlayerTurn->properNotation(getDestination()) << endl;
	//switchTurn();
}

void Game::promptMove() {
	cout << "Player " << currrentPlayerTurn->getName() << ", select a piece to move:\n";
	char row;
	int col;
	cout << "Enter the row(A-H): ";
	cin >> row;
	cout << "Enter the column (1-8): ";
	cin >> col;
	currrentPlayerTurn->selectPiece(row, col);
}

void Game::promptDestination() {
	cout << "Player " << currrentPlayerTurn->getName() << ", set the destination";
	char row;
	int col;
	cout << "Enter the row (A-H): ";
	cin >> row;
	cout << "Enter the column (1-8): ";
	cin >> col;

	destination = make_pair(row, col);
	
}