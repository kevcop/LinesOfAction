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
    cout << "***************************************\n";
    cout << "*          Lines of Action            *\n";
    cout << "***************************************\n\n";
    cout << "Welcome to the game!\n\n";
    cout << "Please select a mode:\n";
    cout << "1. Start game with Player vs Player\n";
    cout << "2. Start game with Player vs Computer\n";
    cout << "3. Start game with Computer vs Computer\n";
    cout << "4. Load a game\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    // Variables for player names, could be used based on the choice
    string player1Name, player2Name;

    // Based on the choice, initialize the game accordingly
    switch (choice) {
    case 1: {
        cout << "Enter Player 1 name: ";
        cin >> player1Name;
        cout << "Enter Player 2 name: ";
        cin >> player2Name;
        auto player1 = make_shared<HumanPlayer>(player1Name);
        auto player2 = make_shared<HumanPlayer>(player2Name);
        Tournament tournament(player1, player2);
        tournament.playNextRound();
        break;
    }
    case 2: {
        cout << "Enter Player name: ";
        cin >> player1Name;
        auto player1 = make_shared<HumanPlayer>(player1Name);
        auto computerPlayer = make_shared<ComputerPlayer>("AI");
        Tournament tournament(player1, computerPlayer);
        tournament.playNextRound();
        break;
    }
    case 3: {
        auto computerPlayer1 = make_shared<ComputerPlayer>("AI 1");
        auto computerPlayer2 = make_shared<ComputerPlayer>("AI 2");
        Tournament tournament(computerPlayer1, computerPlayer2);
        tournament.playNextRound();
        break;
    }
    case 4: {
        cout << "Select a serial file to load:\n";
        cout << "1. Serial 1\n";
        cout << "2. Serial 2\n";
        cout << "3. Serial 3\n";
        cout << "4. Serial 4\n";
        cout << "5. Serial 5\n";
        // Add more cases as necessary
        cout << "Enter your choice: ";
        int fileChoice;
        cin >> fileChoice;

        string filename;
        switch (fileChoice) {
        case 1:
            filename = "C:/Users/Owner/Downloads/serialization_case1.txt";
            break;
        case 2:
            filename = "/Users/kchic/Desktop/linesofActionNew/Serial2.txt"; 
            break;
        case 3:
            filename = "/Users/kchic/Desktop/linesofActionNew/Serial3.txt"; 
            break;
        case 4:
            filename = "/Users/kchic/Desktop/linesofActionNew/Serial6.txt";
            break;
        case 5:
            filename = "/Users/kchic/Desktop/linesofActionNew/Serial5.txt"; 
            break;
        default:
            cout << "Invalid option. Exiting." << endl;
            return 0;
        }

        auto loadedRound = Serialization::loadGameState(filename);
        if (loadedRound) {
            cout << "Game loaded successfully from " << filename << endl;
            Tournament tournament(loadedRound->getPlayer1(), loadedRound->getPlayer2());
            tournament.resumeTournament(move(loadedRound));
        }
        else {
            cout << "Failed to load the game from " << filename << endl;
        }
        break;
    }

          return 0;
    }
}
