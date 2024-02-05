#include "Game.h"
#include "Player.h"
#include <iostream>
using namespace std;

//Game::Game(Player p1, Player p2): p1(p1), p2(p2) {
//	//coinToss();
//}
Game::Game() : isPlayer1Turn(false) {

}
void Game::setPlayerNames(const string &player1Name, const string &player2Name) {
	p1.setPlayerName(player1Name);
	p2.setPlayerName(player2Name);
	cout << "Player 1 :" << p1.getName() << "\n";
	cout << "Player 2 :" << p2.getName() << "\n";


}
void Game::coinToss() 
{
	int userChoice;
	int firstTurn;
	int toss;
	cout << "Enter 1 for heads or 2 for tails.\n";
	cin >> userChoice;
	toss = rand() % 2 + 1;
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