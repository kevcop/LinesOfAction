//#include "Game.h"
//#include "Player.h"
//#include "HumanPlayer.h"
//#include "ComputerPlayer.h"
//#include "board.h"
//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//#include <utility>
//#include <map>
//#include <vector>
//using namespace std;
////used to keep track of moves
//vector<string> moveLog;
////translate cols
//map<char, int> colToIndex = {
//{'A', 0}, {'B', 1}, {'C', 2}, {'D', 3},
//{'E', 4}, {'F', 5}, {'G', 6}, {'H', 7}
//};
////cosntructor for setting board and players
//Game::Game(Player* p1, Player* p2) : player1(p1), player2(p2), currentPlayer(nullptr), isPlayer1Turn(true) {
//srand(static_cast<unsigned int>(time(nullptr))); // seed
//gameBoard.resetBoard(); // Initialize the board
//}
////decide who goes first
//void Game::coinToss() {
//cout << "Enter 1 for heads or 2 for tails.\n";
//int userChoice;
//cin >> userChoice;
//int toss = rand() % 2 + 1; // get rand num
//// assign first move
//if (userChoice == toss) {
//currentPlayer = player1;
//cout << "Player " << player1->getName() << " wins the coin toss and will go first.\n";
//player1->setPieceType('B');
//player2->setPieceType('W');
//}
//else {
//currentPlayer = player2;
//cout << "Player " << player2->getName() << " wins the coin toss and will go first.\n";
//player2->setPieceType('B');
//player1->setPieceType('W');
//}
//}
//// change turns
//void Game::switchTurn() {
//if (currentPlayer == player1) {
//currentPlayer = player2;
//}
//else {
//currentPlayer = player1;
//}
//cout << "It's now " << currentPlayer->getName() << "'s turn.\n";
//}
//// logic for movement
//void Game::playerMove() {
//promptMove();
//promptDestination();
//cout << "Player " << currentPlayer->getName() << " moves piece from "
//<< currentPlayer->properNotation(currentPlayer->getSelectedPiece())
//<< " to " << currentPlayer->properNotation(currentPlayer->getDestination()) << endl;
//switchTurn();
//}
////ask for move
//void Game::promptMove() {
//string from, to;
//cout << currentPlayer->getName() << ", it's your turn." << endl;
//cout << "Enter your move from (e.g., A6): ";
//cin >> from;
//cout << "Enter move to (e.g., B6): ";
//cin >> to;
//
//// Convert inputs using the map
//int fromCol = colToIndex[toupper(from[0])];
//int fromRow = from[1] - '1';
//int toCol = colToIndex[toupper(to[0])];
//int toRow = to[1] - '1';
//
//if (gameBoard.movePiece(fromRow, fromCol, toRow, toCol, currentPlayer->getPieceType())) {
//logMove(from, to);
//}
//else {
//cout << "Invalid move. Please try again." << endl;
//}
//}
////ask for destination
//void Game::promptDestination() {
//char colLetter;
//int row;
//cout << currentPlayer->getName() << ", select a destination for the piece." << endl;
//cout << "Column (A-H): ";
//cin >> colLetter;
//cout << "Row (1-8): ";
//cin >> row;
//
////convert column letter to index
//int col = toupper(colLetter) - 'A';
//if (col >= 0 && col < 8 && row >= 1 && row <= 8) {
//currentPlayer->setDestination(row - 1, col); // 0 based indexing adjustment
//}
//else {
//cout << "Invalid input. Please try again." << endl;
//}
//}
//// handles the move logic and validates
//void Game::playerTurn() {
//cout << currentPlayer->getName() << ", it's your turn." << endl;
//
//char fromColLetter, toColLetter;
//int fromRow, toRow;
//
//// Prompt for current location of the piece
//cout << "Select a piece to move." << endl;
//cout << "Column (A-H): ";
//cin >> fromColLetter;
//cout << "Row (1-8): ";
//cin >> fromRow;
//
//int fromCol = toupper(fromColLetter) - 'A';
//fromRow -= 1;
//
////ask for location
//cout << "Select a destination for the piece." << endl;
//cout << "Column (A-H): ";
//cin >> toColLetter;
//cout << "Row (1-8): ";
//cin >> toRow;
//
//
//int toCol = toupper(toColLetter) - 'A';
//toRow -= 1;
//vector<pair<int, int>> capturePositions;
//
//// validation checks
//if (rules.isValidMove(gameBoard, *currentPlayer, fromRow, fromCol, toRow, toCol) &&
//rules.isPathClear(gameBoard, fromRow, fromCol, toRow, toCol, currentPlayer->getPieceType(),capturePositions) &&
//rules.isValidEndingPosition(gameBoard, toRow, toCol, currentPlayer->getPieceType())) {
//
//// execute the move
//gameBoard.movePiece(fromRow, fromCol, toRow, toCol, currentPlayer->getPieceType());
//
//// record move
//string fromPosition = fromColLetter + to_string(fromRow + 1);
//string toPosition = toColLetter + to_string(toRow + 1);
//logMove(fromPosition, toPosition);
//displayMoveLog();
//
//cout << "Move successful." << endl;
//
//gameBoard.showBoard();
//}
//else {
//cout << "Invalid move. Please try again." << endl;
//return; // dont want to switch turns if invalid move
//}
//
//switchTurn(); //next player's turn
//}
//
//// record recent move
//void Game::logMove(const string& from, const string& to) {
//
//string moveSummary = currentPlayer->getName() + " moves from " + from + " to " + to;
//moveLog.push_back(moveSummary);
//}
//
//// record all moves
//void Game::displayMoveLog() const {
//cout << "Move Log:" << endl;
//for (const auto& move : moveLog) {
//cout << move << endl;
//}
//}
//
//// ask fo location index
//void Game::promptPieceLocation(string& locationDescription) {
//char column;
//int row;
//cout << "Enter column (A-H): ";
//cin >> column;
//cout << "Enter row (1-8): ";
//cin >> row;
//
//int colIndex = translateColumn(toupper(column));
//locationDescription = to_string(colIndex) + to_string(row - 1);
//}
//
////translate column 
//int Game::translateColumn(char columnLetter) {
//if (colToIndex.find(columnLetter) != colToIndex.end()) {
//return colToIndex[columnLetter];
//}
//return -1; // not a valid input
//}
//
//void Game::startGame() {
//    // Initial setup, such as deciding who goes first
//    coinToss(); // Assume this method decides who starts and sets `currentPlayer` accordingly
//
//    // Main game loop
//    bool gameOver = false;
//    while (!gameOver) {
//        gameBoard.showBoard(); // Display the board at the start of each turn
//        playerTurn(); // Conduct the current player's turn
//
//        // Check for game-ending conditions, such as one player winning
//        // gameOver = checkWinCondition(gameBoard, *currentPlayer);
//        // if (gameOver) {
//        //     std::cout << currentPlayer->getName() << " wins!" << std::endl;
//        //     break;
//        // }
//
//        //switchTurn(); // Switch to the other player's turn
//    }
//
//    // Game has ended, display final board state and any concluding messages
//    gameBoard.showBoard();
//    std::cout << "Game over!" << std::endl;
//}
//
