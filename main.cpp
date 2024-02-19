// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "board.h"
#include "Player.h"
#include "Game.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Round.h"
#include "Tournament.h"
using namespace std;

int main() {
// NEW APPROACH
    Board gameBoard; // create board object
    
    cout << "INITIAL BOARD\n";
    //gameBoard.showBoard();

    HumanPlayer humanPlayer("Kevin");
    ComputerPlayer computerPlayer("AI");

   /* Game game(&humanPlayer, &computerPlayer);
    game.startGame();*/
    /*Round game(&humanPlayer, &computerPlayer);
    game.startGame();*/

    Tournament tourney(&humanPlayer, &computerPlayer);
    tourney.playNextRound();
    //game.coinToss();
    //game.playerTurn();
    /* OLD APPROACH */
    //for (int i = 0; i < 2; ++i) {
    //    cout << "Current Board:" << endl;
    //    gameBoard.showBoard();  // Display the current state of the board

    //    game.playerMove();  // Prompt the current player for a move and execute it

    //    // Optionally, after each move, you can display the move log to see the history of moves
    //    game.displayMoveLog();
    //}
    //game.playerMove();
    // Example test for ComputerPlayer (this should be adjusted to fit your implementation)
 /*   computerPlayer.selectPiece('A', 1);
    computerPlayer.setDestination('B', 2);

    auto piece = computerPlayer.getSelectedPiece();
    auto destination = computerPlayer.getDestination();*/

    /*string p1_name, p2_name;
    cout << "Enter player 1 name: \n";
    cin >> p1_name;
    cout << "Enter player 2 name: \n";
    cin >> p2_name;*/
   /* Game startGame;
    startGame.setPlayerNames(p1_name, p2_name);
    startGame.coinToss(p1_name,p2_name);*/

    //startGame.playerMove();
    //Player p1_name;
    //Player p2_name;
    //Game startGame(p1_name, p2_name);

    //cout << "Player 1: " << p1_name.getName() << endl;
    //Player p1(p1_name);
    return 0;
}