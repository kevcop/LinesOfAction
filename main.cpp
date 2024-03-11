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
#include "Serialization.h"
using namespace std;

int main() {
// NEW APPROACH
    Board gameBoard; // create board object
    
    cout << "INITIAL BOARD\n";
    //gameBoard.showBoard();

    //HumanPlayer humanPlayer("Kevin");
    //ComputerPlayer computerPlayer("AI");

    auto humanPlayer = std::make_shared<HumanPlayer>("Kevin");
    auto computerPlayer = std::make_shared<ComputerPlayer>("AI");
    auto computerPlayer2 = std::make_shared<ComputerPlayer>("AI2");

    auto humanPlayer2 = std::make_shared<HumanPlayer>("Kevin2");


   /* game game(&humanplayer, &computerplayer);
    game.startgame();
    round game(&humanplayer, &computerplayer);
    game.startgame(); */

    //cout << "Do you want to load a saved game? (yes/no): ";
    //cin >> choice;

    //if (choice == "yes") {
    //    // Attempt to load the game state
    //    if (Serialization::loadGameState(gameBoard, *dynamic_pointer_cast<HumanPlayer>(humanPlayer), *dynamic_pointer_cast<ComputerPlayer>(computerPlayer), isPlayer1Turn)) {
    //        cout << "Game loaded successfully.\n";
    //        // Optionally, show the loaded board state and current turn
    //        cout << "LOADED BOARD STATE:\n";
    //        gameBoard.showBoard();
    //        Tournament tourney(humanPlayer, computerPlayer2);
    //        tourney.playNextRound();
    //        bool isPlayer1Turn;
    //    }

    /*cout << "Do you want to save the game state? (yes/no): ";
    string saveChoice;
    cin >> saveChoice;*/

    //if (saveChoice == "yes") {
    //    // Assuming the Serialization class has a static method to save the game state
    //    // Adjust the parameters as necessary
    //    Serialization::saveGameState(gameBoard, *humanPlayer, *computerPlayer, isPlayer1Turn, humanPlayer->getScore(), computerPlayer->getScore());
    //    cout << "Game state saved successfully.\n";
    //}

    //cout << "Do you want to load a saved game? (yes/no): ";
    //string choice;
    //cin >> choice;

    //if (choice == "yes") {
    //    if (Serialization::loadGameState(gameBoard, humanPlayer, computerPlayer, isPlayer1Turn)) {
    //        cout << "Game loaded successfully.\n";
    //        // Optionally, show the loaded board state and current turn
    //        cout << "LOADED BOARD STATE:\n";
    //        gameBoard.showBoard();
        //}
    //}
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


    //cout << "Would you like to load a saved game? (yes/no): ";
    //string choice;
    //cin >> choice;
    ////Round round(humanPlayer, computerPlayer);
    //std::unique_ptr<Round> round;

    //if (choice == "yes") {
    //    round = Serialization::loadGameState();
    //    cout << "Game loaded successfully." << endl;
    //    // Display the loaded game state
    //    cout << "Current Board State:" << endl;
    //    round->getGameBoard().showBoard(); // Assuming your Board class has a showBoard method
    //    cout << "It's " << round->getCurrentPlayer()->getName() << "'s turn." << endl;
    //    cout << "Human Rounds Won: " << round->getPlayer1()->getRoundsWon() << ", Score: " << round->getPlayer1()->getScore() << endl;
    //    cout << "Computer Rounds Won: " << round->getPlayer2()->getRoundsWon() << ", Score: " << round->getPlayer2()->getScore() << endl;
    //}

cout << "Would you like to load a saved game? (yes/no): ";
string choice;
cin >> choice;

if (choice == "yes") {
    // Hardcoded file path
    string filename = R"(C:\Users\kchic\Desktop\linesofActionNew\gameState.txt)";

    auto loadedRound = Serialization::loadGameState(filename); // This should now return a unique_ptr<Round>

    if (loadedRound) {
        cout << "Game loaded successfully." << endl;
        // Assuming the Tournament class has been adjusted to accept a loaded round
        Tournament tournament(loadedRound->getPlayer1(), loadedRound->getPlayer2());
        tournament.resumeTournament(std::move(loadedRound));
        //loadedRound->continueGameFromSavedState();
    }
    else {
        cout << "Failed to load the game from " << filename << "." << endl;
    }
}
else {
    // Initialization for a new game or other logic
    cout << "Starting a new game..." << endl;
    // You can initialize your new game here
}// Other logic for starting a new game or exiting
}
