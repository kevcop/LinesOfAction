#include "Serialization.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Rules.h"
#include <fstream>
#include <iostream>
#include <sstream>
// Include other necessary headers

//void Serialization::saveGameState(const Board& board, const Player& player1, const Player& player2, bool isPlayer1Turn, int player1Score, int player2Score) {
//    std::ofstream outFile("gameState.txt");
//    if (!outFile) {
//        std::cerr << "Error opening file for writing.\n";
//        return;
//    }
//
//    // Save board state
//    for (int row = 0; row < 8; ++row) {
//        for (int col = 0; col < 8; ++col) {
//            outFile << board.getPieceAt(row, col) << (col < 8 - 1 ? "," : "");
//        }
//        outFile << "\n";
//    }
//
//    // Save player details: piece type, scores
//    outFile << player1.getPieceType() << "," << player1Score << "\n";
//    outFile << player2.getPieceType() << "," << player2Score << "\n";
//
//    // Save current round number and who's turn it is
//    outFile << isPlayer1Turn << "\n";
//
//    outFile.close();
//}

//void saveGameState(const Board& board, const Player& humanPlayer, const Player& computerPlayer, const std::string& nextPlayer, char nextPlayerColor) {
//    std::ofstream outFile("gameState.txt");
//    if (!outFile) {
//        std::cerr << "Error opening file for writing.\n";
//        return;
//    }
//
//    // Save board state
//    outFile << "Board:\n";
//    for (int row = 0; row < 8; ++row) {
//        for (int col = 0; col < 8; ++col) {
//            outFile << board.getPieceAt(row, col) << (col < 7 ? " " : "");
//        }
//        outFile << "\n";
//    }
//
//    // Save human player details
//    outFile << "\nHuman:\n";
//    outFile << "Rounds won: " << humanPlayer.getRoundsWon() << "\n";
//    outFile << "Score: " << humanPlayer.getScore() << "\n";
//
//    // Save computer player details
//    outFile << "\nComputer:\n";
//    outFile << "Rounds won: " << computerPlayer.getRoundsWon() << "\n";
//    outFile << "Score: " << computerPlayer.getScore() << "\n";
//
//    // Save next player and color information
//    outFile << "\nNext player: " << nextPlayer << "\n";
//    outFile << "Color: " << nextPlayerColor << "\n";
//
//    outFile.close();
//}

void Serialization::saveGameState(const Round& round) {
    std::ofstream outFile("gameState.txt");
    if (!outFile) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    // Save board state
    /*outFile << "Board:\n";
    const Board& board = round.getGameBoard();
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            outFile << board.getPieceAt(row, col) << (col < 7 ? " " : "");
        }
        outFile << "\n";
    }*/
    outFile << "Board:\n";
    for (int row = 7; row >= 0; --row) { // Start from the last row and move towards the first
        for (int col = 0; col < 8; ++col) {
            outFile << round.getGameBoard().getPieceAt(row, col) << (col < 7 ? " " : "");
        }
        outFile << "\n";
    }

    // Save details for player1 and player2
    auto player1 = round.getPlayer1();
    auto player2 = round.getPlayer2();

    outFile << "\nHuman:\n";
    outFile << "Rounds won: " << player1->getRoundsWon() << "\n";
    outFile << "Score: " << player1->getScore() << "\n";

    outFile << "\nComputer:\n";
    outFile << "Rounds won: " << player2->getRoundsWon() << "\n";
    outFile << "Score: " << player2->getScore() << "\n";

    // Determine and save next player and color information
    auto currentPlayer = round.getCurrentPlayer();
    std::string playerType = std::dynamic_pointer_cast<HumanPlayer>(currentPlayer) ? "Human" : "Computer";
    outFile << "\nNext player: " << playerType << "\n";
    outFile << "Color: " << currentPlayer->getPieceType() << "\n";

    outFile.close();
    std::cout << "Game state saved successfully.\n";
}


//bool Serialization::loadGameState(Board& board, HumanPlayer& humanPlayer, ComputerPlayer& computerPlayer, bool& isPlayer1Turn) {
//    std::ifstream inFile("gameState.txt");
//    if (!inFile) {
//        std::cerr << "Error opening file for reading.\n";
//        return false;
//    }
//
//    std::string line;
//    // Skip the "Board:" line
//    std::getline(inFile, line);
//
//    // Load board state
//    for (int row = 0; row < 8 && std::getline(inFile, line); ++row) {
//        for (int col = 0, pos = 0; col < 8 && pos < line.length(); ++col, pos += 2) { // Assume 2 characters per cell including space
//            char pieceType = line[pos];
//            board.setPieceAt(row, col, pieceType); // Set the piece on the board
//        }
//    }
//
//    // Skipping to "Human:" section
//    while (std::getline(inFile, line) && line != "Human:") {}
//    // Read human player details
//    std::getline(inFile, line); // "Rounds won: X"
//    humanPlayer.setRoundsWon(extractValue(line)); // Assuming a method to set rounds won
//    std::getline(inFile, line); // "Score: Y"
//    humanPlayer.setScore(extractValue(line)); // Assuming a method to set score
//
//    // Skipping to "Computer:" section
//    while (std::getline(inFile, line) && line != "Computer:") {}
//    // Read computer player details
//    std::getline(inFile, line); // "Rounds won: X"
//    computerPlayer.setRoundsWon(extractValue(line));
//    std::getline(inFile, line); // "Score: Y"
//    computerPlayer.setScore(extractValue(line));
//
//    // Read next player and color
//    std::getline(inFile, line); // "Next player: PlayerName"
//    std::string nextPlayer = line.substr(line.find(':') + 2);
//    std::getline(inFile, line); // "Color: Color"
//    char color = line.substr(line.find(':') + 2)[0];
//
//    // Determine whose turn it is based on the next player and color
//    isPlayer1Turn = (nextPlayer == "Human" && humanPlayer.getPieceType() == color) || (nextPlayer == "Computer" && computerPlayer.getPieceType() == color);
//
//    inFile.close();
//    return true;
//}

//bool Serialization::loadGameState(const std::string& filePath, Round& round) {
//    std::ifstream inFile(filePath);
//    if (!inFile) {
//        std::cerr << "Error opening file for reading: " << filePath << std::endl;
//        return false;
//    }
//
//    std::string line;
//    std::getline(inFile, line); // Skip the "Board:" line
//
//    // Load board state in reverse order to match the saved state
//    for (int row = 7; row >= 0 && std::getline(inFile, line); --row) {
//        std::istringstream stream(line);
//        for (int col = 0; col < 8; ++col) {
//            char pieceType;
//            stream >> pieceType;
//            round.getGameBoard().setPieceAt(row, col, pieceType);
//        }
//    }
//
//    // Process player sections
//    while (std::getline(inFile, line)) {
//        if (line == "Human:") {
//            // Process human player data
//            processPlayerData(inFile, round.getPlayer1());
//        }
//        else if (line == "Computer:") {
//            // Process computer player data
//            processPlayerData(inFile, round.getPlayer2());
//        }
//        else if (line.find("Next player:") != std::string::npos) {
//            auto nextPlayerType = line.substr(line.find(':') + 2);
//            std::getline(inFile, line);
//            char color = line.substr(line.find(':') + 2)[0];
//            round.determineCurrentPlayer(nextPlayerType, color);
//            break; // Assuming this is the last section
//        }
//    }
//
//    inFile.close();
//    std::cout << "Game loaded successfully from " << filePath << std::endl;
//    return true;
//}

//WORKS BUT INCORRECTLY GENERATES BOARD
//std::unique_ptr<Round> Serialization::loadGameState() {
//    std::ifstream inFile("gameState.txt");
//    if (!inFile) {
//        std::cerr << "Error opening file for reading.\n";
//        return nullptr;
//    }
//
//    std::string line;
//    std::getline(inFile, line); // Skip the "Board:" line
//
//    Board board;
//    int row = 7; // Start from the last row based on how the board was saved
//    while (std::getline(inFile, line) && !line.empty()) {
//        std::istringstream lineStream(line);
//        char piece;
//        int col = 0;
//        while (lineStream >> piece && col < 8) {
//            // Assuming 'x' represents an empty space, 'B' represents a black piece, and 'W' represents a white piece.
//            // Adjust this logic if your representation is different.
//            if (piece != '.') { // Check if the spot is not empty
//                board.setPieceAt(row, col, piece);
//            }
//            col++;
//        }
//        row--;
//        if (row < 0) break; // Stop if we've filled the entire board
//    }
//
//    // Load player details...
//    auto humanPlayer = std::make_shared<HumanPlayer>("HumanName");
//    auto computerPlayer = std::make_shared<ComputerPlayer>("AI");
//    // Assume extractValue and other necessary details are correctly implemented...
//
//    std::getline(inFile, line); // Skip to "Next player: PlayerName"
//    std::string nextPlayerType;
//    char color;
//
//    // Directly extracting next player type and color from the file
//    if (std::getline(inFile, line)) {
//        nextPlayerType = line.substr(line.find(": ") + 2);
//    }
//    if (std::getline(inFile, line)) {
//        color = line.substr(line.find(": ") + 2)[0];
//    }
//
//    std::shared_ptr<Player> startingPlayer = (nextPlayerType == "Human") ? std::static_pointer_cast<Player>(humanPlayer) : std::static_pointer_cast<Player>(computerPlayer);
//
//    // Assuming a Round constructor that accepts players and a board.
//    auto round = std::make_unique<Round>(humanPlayer, computerPlayer);
//    round->setStartingPlayer(startingPlayer);
//
//    inFile.close();
//    board.showBoard();
//    return round;
//}



// Example of a helper function to process player data
void Serialization::processPlayerData(std::ifstream& inFile, std::shared_ptr<Player> player) {
    std::string line;
    std::getline(inFile, line); // "Rounds won: X"
    player->setRoundsWon(extractValue(line));
    std::getline(inFile, line); // "Score: Y"
    player->setScore(extractValue(line));
}

// Helper function to extract integer values from strings
int Serialization::extractValue(const std::string& line) {
    size_t pos = line.find_last_of(' ');
    if (pos != std::string::npos) {
        return std::stoi(line.substr(pos + 1));
    }
    return 0; // Default case
}

//std::unique_ptr<Round> Serialization::loadGameState(const std::string& filename) {
//    std::ifstream inFile(filename);
//    if (!inFile) {
//        std::cerr << "Error opening file for reading: " << filename << std::endl;
//        return nullptr;
//    }
//
//    Board board;
//    board.clearBoard();
//    std::string line;
//    std::getline(inFile, line); // Skip "Board:" marker
//
//    // Load the board state
//    for (int row = 7; row >= 0; --row) {
//        if (!std::getline(inFile, line)) break; // If there's no more lines, break out of the loop
//        std::istringstream rowStream(line);
//        for (int col = 0; col < 8; ++col) {
//            char piece;
//            rowStream >> piece;
//            // Assuming '.' represents an empty spot, adjust if your representation is different
//            if (piece == 'x') {
//                board.setPieceAt(row, col, '.');
//            }
//            else {
//                board.setPieceAt(row, col, piece);
//            }
//        }
//    }
//
//    // Skipping lines until "Human:" section
//    while (std::getline(inFile, line) && line != "Human:") {}
//    auto humanPlayer = std::make_shared<HumanPlayer>("Human");
//    // Load human player details...
//
//    // Skipping lines until "Computer:" section
//    while (std::getline(inFile, line) && line != "Computer:") {}
//    auto computerPlayer = std::make_shared<ComputerPlayer>("AI");
//    // Load computer player details...
//
//    std::string nextPlayerType;
//    char nextPlayerColor;
//
//    // Find "Next player" section and extract its value
//    while (std::getline(inFile, line)) {
//        if (line.find("Next player:") != std::string::npos) {
//            nextPlayerType = line.substr(line.find(": ") + 2);
//        }
//        if (line.find("Color:") != std::string::npos) {
//            nextPlayerColor = line.substr(line.find(": ") + 2)[0];
//            break; // Assuming this is the last needed piece of information
//        }
//    }
//
//    //std::shared_ptr<Player> startingPlayer = (nextPlayerType == "Human") ? humanPlayer : computerPlayer;
//    std::shared_ptr<Player> startingPlayer = (nextPlayerType == "Human") ? std::static_pointer_cast<Player>(humanPlayer) : std::static_pointer_cast<Player>(computerPlayer);
//
//    auto round = std::make_unique<Round>(humanPlayer, computerPlayer);
//    round->setBoardState(board);
//    round->setStartingPlayer(startingPlayer);
//
//    //round->setStartingPlayer(startingPlayer);
//
//    inFile.close();
//    return round;
//}

//std::unique_ptr<Round> Serialization::loadGameState(const std::string& filename) {
//    std::ifstream inFile(filename);
//    if (!inFile) {
//        std::cerr << "Error opening file for reading: " << filename << std::endl;
//        return nullptr;
//    }
//
//    Board board;
//    board.clearBoard(); // Assuming this method exists to clear or initialize the board
//    std::string line, nextPlayerType;
//    char nextPlayerColor;
//    std::getline(inFile, line); // Skip "Board:" marker
//
//    // Load the board state
//    for (int row = 7; row >= 0; --row) {
//        if (!std::getline(inFile, line)) break;
//        std::istringstream rowStream(line);
//        for (int col = 0; col < 8; ++col) {
//            char piece;
//            rowStream >> piece;
//            if (piece == 'x' || piece == '.') {
//                board.setPieceAt(row, col, '.'); // Assuming '.' represents an empty space
//            }
//            else {
//                board.setPieceAt(row, col, piece);
//            }
//        }
//    }
//
//    auto humanPlayer = std::make_shared<HumanPlayer>("Human");
//    auto computerPlayer = std::make_shared<ComputerPlayer>("AI");
//
//    // Load player details
//    while (std::getline(inFile, line)) {
//        if (line == "Human:") {
//            std::getline(inFile, line); // "Rounds won: X"
//            humanPlayer->setRoundsWon(std::stoi(line.substr(line.find(":") + 2)));
//            std::getline(inFile, line); // "Score: Y"
//            humanPlayer->setScore(std::stoi(line.substr(line.find(":") + 2)));
//        }
//        else if (line == "Computer:") {
//            std::getline(inFile, line); // "Rounds won: X"
//            computerPlayer->setRoundsWon(std::stoi(line.substr(line.find(":") + 2)));
//            std::getline(inFile, line); // "Score: Y"
//            computerPlayer->setScore(std::stoi(line.substr(line.find(":") + 2)));
//        }
//        else if (line.find("Next player:") != std::string::npos) {
//            nextPlayerType = line.substr(line.find(":") + 2);
//        }
//        else if (line.find("Color:") != std::string::npos) {
//            nextPlayerColor = line[line.find(":") + 2];
//        }
//    }
//
//    string pieceColor;
//    while (std::getline(inFile, line)) {
//        if (line == "Human:") {
//            std::getline(inFile, line); // "Rounds won: X"
//            humanPlayer->setRoundsWon(std::stoi(line.substr(line.find(":") + 2)));
//            std::getline(inFile, line); // "Score: Y"
//            humanPlayer->setScore(std::stoi(line.substr(line.find(":") + 2)));
//        }
//        else if (line == "Computer:") {
//            std::getline(inFile, line); // "Rounds won: X"
//            computerPlayer->setRoundsWon(std::stoi(line.substr(line.find(":") + 2)));
//            std::getline(inFile, line); // "Score: Y"
//            computerPlayer->setScore(std::stoi(line.substr(line.find(":") + 2)));
//        }
//        else if (line.find("Next player:") != std::string::npos) {
//            nextPlayerType = line.substr(line.find(":") + 2);
//        }
//        else if (line.find("Color:") != std::string::npos) {
//            pieceColor = line.substr(line.find(":") + 2);
//        }
//    }
//    cout << "Piece color: " << pieceColor;
//
//    std::shared_ptr<Player> startingPlayer = (nextPlayerType == "Human") ? std::static_pointer_cast<Player>(humanPlayer) : std::static_pointer_cast<Player>(computerPlayer);
//    //humanPlayer->setPieceType(humanPieceType);
//    //computerPlayer->setPieceType(computerPieceType);
//    auto round = std::make_unique<Round>(humanPlayer, computerPlayer);
//    round->setBoardState(board);
//    round->setStartingPlayer(startingPlayer);
//    cout << "Next Player: " << nextPlayerType << ", Piece Color: " << pieceColor << endl;
//    inFile.close();
//    return round;
//}

//std::unique_ptr<Round> Serialization::loadGameState(const std::string& filename) {
//    std::ifstream inFile(filename);
//    if (!inFile) {
//        std::cerr << "Error opening file for reading: " << filename << std::endl;
//        return nullptr;
//    }
//
//    Board board;
//    board.clearBoard(); // Assuming this method exists to clear or initialize the board
//    std::string line, nextPlayerType, pieceColor;
//    std::getline(inFile, line); // Skip "Board:" marker
//
//    // Load the board state
//    for (int row = 7; row >= 0; --row) {
//        std::getline(inFile, line);
//        std::istringstream rowStream(line);
//        for (int col = 0; col < 8; ++col) {
//            char piece;
//            rowStream >> piece;
//            piece = toupper(piece);
//            board.setPieceAt(row, col, (piece == 'X' || piece == '.') ? '.' : piece);
//        }
//    }
//
//    auto humanPlayer = std::make_shared<HumanPlayer>("Human");
//    auto computerPlayer = std::make_shared<ComputerPlayer>("AI");
//
//    // Load player details
//    while (std::getline(inFile, line)) {
//        if (line.find("Human:") != std::string::npos) {
//            // Extract and set rounds won and score for the human player
//            std::getline(inFile, line); // Assumes "Rounds won:" line is next
//            humanPlayer->setRoundsWon(std::stoi(line.substr(line.find_last_of(' ') + 1)));
//            std::getline(inFile, line); // Assumes "Score:" line is next
//            humanPlayer->setScore(std::stoi(line.substr(line.find_last_of(' ') + 1)));
//        }
//        else if (line.find("Computer:") != std::string::npos) {
//            // Extract and set rounds won and score for the computer player
//            std::getline(inFile, line); // Assumes "Rounds won:" line is next
//            computerPlayer->setRoundsWon(std::stoi(line.substr(line.find_last_of(' ') + 1)));
//            std::getline(inFile, line); // Assumes "Score:" line is next
//            computerPlayer->setScore(std::stoi(line.substr(line.find_last_of(' ') + 1)));
//        }
//        else if (line.find("Next player:") != std::string::npos) {
//            nextPlayerType = line.substr(line.find(":") + 2);
//        }
//        else if (line.find("Color:") != std::string::npos) {
//            pieceColor = line.substr(line.find(":") + 2);
//        }
//    }
//
//    // Convert "Black" or "White" to 'B' or 'W' and set the piece type accordingly
//    char humanPieceType = (pieceColor == "Black") ? 'B' : 'W';
//    char computerPieceType = (pieceColor == "Black") ? 'W' : 'B';
//    humanPlayer->setPieceType(humanPieceType);
//    computerPlayer->setPieceType(computerPieceType);
//
//    // Determine the starting player and set it
//    //std::shared_ptr<Player> startingPlayer = (nextPlayerType == "Human") ? humanPlayer : computerPlayer;
//    std::shared_ptr<Player> startingPlayer = (nextPlayerType == "Human") ? std::static_pointer_cast<Player>(humanPlayer) : std::static_pointer_cast<Player>(computerPlayer);
//
//    auto round = std::make_unique<Round>(humanPlayer, computerPlayer);
//    round->setBoardState(board);
//    round->setStartingPlayer(startingPlayer);
//
//    cout << "Next Player: " << nextPlayerType << ", Piece Color: " << pieceColor << endl;
//    cout << "Human Rounds Won: " << humanPlayer->getRoundsWon() << ", Score: " << humanPlayer->getScore() << endl;
//    cout << "Computer Rounds Won: " << computerPlayer->getRoundsWon() << ", Score: " << computerPlayer->getScore() << endl;
//
//    inFile.close();
//    return round;
//}

std::unique_ptr<Round> Serialization::loadGameState(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return nullptr;
    }

    Board board;
    board.clearBoard(); // Assuming this method exists to clear or initialize the board
    std::string line, nextPlayerType, pieceColor;
    std::getline(inFile, line); // Skip "Board:" marker

    // Load the board state
    for (int row = 7; row >= 0; --row) {
        std::getline(inFile, line);
        std::istringstream rowStream(line);
        for (int col = 0; col < 8; ++col) {
            char piece;
            rowStream >> piece;
            piece = toupper(piece);
            board.setPieceAt(row, col, (piece == 'X' || piece == '.') ? '.' : piece);
        }
    }

    auto humanPlayer = std::make_shared<HumanPlayer>("Human");
    auto computerPlayer = std::make_shared<ComputerPlayer>("AI");

    // Load player details
    while (std::getline(inFile, line)) {
        if (line.find("Human:") != std::string::npos) {
            // Extract and set rounds won and score for the human player
            std::getline(inFile, line); // Assumes "Rounds won:" line is next
            humanPlayer->setRoundsWon(std::stoi(line.substr(line.find_last_of(' ') + 1)));
            std::getline(inFile, line); // Assumes "Score:" line is next
            humanPlayer->setScore(std::stoi(line.substr(line.find_last_of(' ') + 1)));
        }
        else if (line.find("Computer:") != std::string::npos) {
            // Extract and set rounds won and score for the computer player
            std::getline(inFile, line); // Assumes "Rounds won:" line is next
            computerPlayer->setRoundsWon(std::stoi(line.substr(line.find_last_of(' ') + 1)));
            std::getline(inFile, line); // Assumes "Score:" line is next
            computerPlayer->setScore(std::stoi(line.substr(line.find_last_of(' ') + 1)));
        }
        else if (line.find("Next player:") != std::string::npos) {
            nextPlayerType = line.substr(line.find(":") + 2);
        }
        else if (line.find("Color:") != std::string::npos) {
            pieceColor = line.substr(line.find(":") + 2);
        }
    }

    // Convert "Black" or "White" to 'B' or 'W' and set the piece type accordingly
    /*char humanPieceType = (pieceColor == "Black") ? 'B' : 'W';
    char computerPieceType = (pieceColor == "Black") ? 'B' : 'W';*/
    char humanPieceType, computerPieceType;

    if (pieceColor == "Black") {
        if (nextPlayerType == "Human") {
            humanPieceType = 'B'; // Human plays Black if they are the next to move
            computerPieceType = 'W'; // Computer plays White
        }
        else {
            humanPieceType = 'W'; // Human plays White if Computer is the next to move
            computerPieceType = 'B'; // Computer plays Black
        }
    }
    else { // pieceColor is "White"
        if (nextPlayerType == "Human") {
            humanPieceType = 'W'; // Human plays White if they are the next to move
            computerPieceType = 'B'; // Computer plays Black
        }
        else {
            humanPieceType = 'B'; // Human plays Black if Computer is the next to move
            computerPieceType = 'W'; // Computer plays White
        }
    }

    cout << "The selected piece for the computer!" << computerPieceType << endl;
    humanPlayer->setPieceType(humanPieceType);
    computerPlayer->setPieceType(computerPieceType);

    // Determine the starting player and set it
    //std::shared_ptr<Player> startingPlayer = (nextPlayerType == "Human") ? humanPlayer : computerPlayer;
    std::shared_ptr<Player> startingPlayer = (nextPlayerType == "Human") ? std::static_pointer_cast<Player>(humanPlayer) : std::static_pointer_cast<Player>(computerPlayer);

    auto round = std::make_unique<Round>(humanPlayer, computerPlayer);
    round->setBoardState(board);
    round->setStartingPlayer(startingPlayer);

    cout << "Next Player: " << nextPlayerType << ", Piece Color: " << pieceColor << endl;
    cout << "Human Rounds Won: " << humanPlayer->getRoundsWon() << ", Score: " << humanPlayer->getScore() << endl;
    cout << "Computer Rounds Won: " << computerPlayer->getRoundsWon() << ", Score: " << computerPlayer->getScore() << endl;

    inFile.close();
    return round;
}




