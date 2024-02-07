// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "board.h"
#include "Player.h"
#include "Game.h"
using namespace std;

int main() {
    Board gameBoard; // create board object
    
    cout << "INITIAL BOARD\n";
    gameBoard.showBoard();
    string p1_name, p2_name;
    cout << "Enter player 1 name: \n";
    cin >> p1_name;
    cout << "Enter player 2 name: \n";
    cin >> p2_name;
    Game startGame;
    startGame.setPlayerNames(p1_name, p2_name);
    startGame.coinToss(p1_name,p2_name);
    //Player p1_name;
    //Player p2_name;
    //Game startGame(p1_name, p2_name);

    //cout << "Player 1: " << p1_name.getName() << endl;
    //Player p1(p1_name);
    return 0;
}//this is a test



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
