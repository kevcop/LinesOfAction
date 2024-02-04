#include "Game.h"
#include "Player.h"
#include <iostream>
using namespace std;

Game::Game(Player p1, Player p2): p1(p1), p2(p2) {
	//coinToss();
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