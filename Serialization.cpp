#include "Serialization.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Rules.h"
#include <fstream>
#include <iostream>
#include <sstream>
/**
 * Function Name: saveGameState
 * Purpose: Saves the current state of the game to a file.
 * Parameters:
 *     round, a constant reference to a Round object representing the current game round.
 * Return Value: None
 * Algorithm:
 *     1. Open a file for writing the game state.
 *     2. Write the board state to the file.
 *     3. Write details for both players (human and computer) including rounds won and scores.
 *     4. Determine and write which player and what color is next to play.
 *     5. Close the file and inform the user that the game state was successfully saved.
 * Reference: None
 */
void Serialization::saveGameState(const Round& round) {
    //attempt to open file out output
    ofstream outFile("gameState.txt");
    //conditional for error when opening file
    if (!outFile) {
        cerr << "Error opening file for writing.\n";
        return;
    }
    //will mimic serialization file format
    outFile << "Board:\n";
    //iterate over the baord in reverse to match game perspective
    for (int row = 7; row >= 0; --row) { 
        for (int col = 0; col < 8; ++col) {
            //output the piece at the current position
            outFile << round.getGameBoard().getPieceAt(row, col) << (col < 7 ? " " : "");
        }
        outFile << "\n";
    }

    //write player details to file
    auto player1 = round.getPlayer1();
    auto player2 = round.getPlayer2();
    //saving human attributes
    outFile << "\nHuman:\n";
    outFile << "Rounds won: " << player1->getRoundsWon() << "\n";
    outFile << "Score: " << player1->getScore() << "\n";
    //saving computer attributes
    outFile << "\nComputer:\n";
    outFile << "Rounds won: " << player2->getRoundsWon() << "\n";
    outFile << "Score: " << player2->getScore() << "\n";

    // Determine and save next player and color information
    auto currentPlayer = round.getCurrentPlayer();
    string playerType = dynamic_pointer_cast<HumanPlayer>(currentPlayer) ? "Human" : "Computer";
    outFile << "\nNext player: " << playerType << "\n";
    outFile << "Color: " << currentPlayer->getPieceType() << "\n";
    //close file and indicate success
    outFile.close();
    cout << "Game state saved successfully.\n";
}

/**
 * Function Name: loadGameState
 * Purpose: Loads a game state from a specified file and constructs a Round object from it.
 * Parameters:
 *     filename, a string representing the name of the file to load the game state from.
 * Return Value: A unique pointer to a Round object constructed from the loaded game state.
 * Algorithm:
 *     1. Open the specified file for reading.
 *     2. Initialize a new Board object and clear its state.
 *     3. Read the board state from the file and set it on the Board object.
 *     4. Read player details from the file and create HumanPlayer and ComputerPlayer objects with these details.
 *     5. Determine the starting player and their piece type based on the file contents.
 *     6. Construct a new Round object with the loaded state and return it.
 * Reference: None
 */
unique_ptr<Round> Serialization::loadGameState(const string& filename) {
    //attempt to open file
    ifstream inFile(filename);
    //conditional for when opening file fails
    if (!inFile) {
        cerr << "Error opening file for reading: " << filename << endl;
        return nullptr;
    }
    //creating a new board object
    Board board;
    //emptying board due to the nature of constructor
    board.clearBoard(); 
    //variables to be used for iteration and extracting important values
    string line, nextPlayerType, pieceColor;
    getline(inFile, line); 

    // Load the board state
    for (int row = 7; row >= 0; --row) {
        getline(inFile, line);
        istringstream rowStream(line);
        for (int col = 0; col < 8; ++col) {
            char piece;
            rowStream >> piece;
            //due to the nature of the game, convert character(piece) to upper case
            piece = toupper(piece);
            board.setPieceAt(row, col, (piece == 'X' || piece == '.') ? '.' : piece);
        }
    }
    //make new player objects
    auto humanPlayer = make_shared<HumanPlayer>("Human");
    auto computerPlayer = make_shared<ComputerPlayer>("AI");

    // Load player details
    while (getline(inFile, line)) {
        if (line.find("Human:") != string::npos) {
            // Extract and set rounds won and score for the human player
            getline(inFile, line); 
            humanPlayer->setRoundsWon(stoi(line.substr(line.find_last_of(' ') + 1)));
            
            getline(inFile, line); 
            humanPlayer->setScore(stoi(line.substr(line.find_last_of(' ') + 1)));
        }
        else if (line.find("Computer:") != string::npos) {
            // Extract and set rounds won and score for the computer player
            getline(inFile, line); 
            computerPlayer->setRoundsWon(stoi(line.substr(line.find_last_of(' ') + 1)));
            getline(inFile, line); 
            computerPlayer->setScore(stoi(line.substr(line.find_last_of(' ') + 1)));
        }
        else if (line.find("Next player:") != string::npos) {
            //identify next players 
            nextPlayerType = line.substr(line.find(":") + 2);
        }
        //identify next player piece color
        else if (line.find("Color:") != string::npos) {
            pieceColor = line.substr(line.find(":") + 2);
        }
    }
    //used to record piece type based on color
    char humanPieceType, computerPieceType;
    // if statements to handle the different possibilites for next player and pieceType
    if (pieceColor == "Black") {
        if (nextPlayerType == "Human") {
             
            humanPieceType = 'B'; 
            computerPieceType = 'W'; 
        }
        else {
            humanPieceType = 'W'; 
            computerPieceType = 'B'; 
        }
    }
    else { // pieceColor is "White"
        if (nextPlayerType == "Human") {
            humanPieceType = 'W'; 
            computerPieceType = 'B'; 
        }
        else {
            humanPieceType = 'B'; 
            computerPieceType = 'W';
        }
    }

    cout << "The selected piece for the computer!" << computerPieceType << endl;
    //actually setting piece type based on previous logic
    humanPlayer->setPieceType(humanPieceType);
    computerPlayer->setPieceType(computerPieceType);

    // Determine the starting player and set it
    shared_ptr<Player> startingPlayer = (nextPlayerType == "Human") ? static_pointer_cast<Player>(humanPlayer) : static_pointer_cast<Player>(computerPlayer);
    //construct new round object
    auto round = make_unique<Round>(humanPlayer, computerPlayer);
    round->setBoardState(board);
    round->setStartingPlayer(startingPlayer);
    //display results 
    cout << "Next Player: " << nextPlayerType << ", Piece Color: " << pieceColor << endl;
    cout << "Human Rounds Won: " << humanPlayer->getRoundsWon() << ", Score: " << humanPlayer->getScore() << endl;
    cout << "Computer Rounds Won: " << computerPlayer->getRoundsWon() << ", Score: " << computerPlayer->getScore() << endl;
    //close file
    inFile.close();
    return round;
}




